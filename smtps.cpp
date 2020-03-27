#include "smtps.h"

SMTPS::SMTPS()
{
	m_ctx = NULL;
	m_ssl = NULL;
}

SMTPS::~SMTPS()
{
	CleanupOpenSSL();
}

RETCODE SMTPS::send(MAIL m)
{
	mail = m;
	if (Connect())
		return FAIL(STMP_CONNECT);

	if(InitSecurity())
		return FAIL(SMTP_INIT_SECURITY);

	if (InitHandshake())
		return FAIL(SMTP_INIT_HANDSHAKE);

	if (server.security == USE_TLS)
	{
		if(StartTls())
			return FAIL(SMTP_HANDSHAKE_TLS);
	}

	if (Handshake())
		return FAIL(SMTP_HANDSHAKE);

	if (WrappedSend())
		return FAIL(SMTP_WRAPPED_SEND);

	return SUCCESS;
}

RETCODE SMTPS::InitSecurity()
{
	if (server.security == USE_TLS || server.security == USE_SSL)
	{
		InitOpenSSL();
		if (server.security == USE_SSL)
		{
			OpenSSLConnect();
		}
	}
	return SUCCESS;
}

RETCODE SMTPS::StartTls()
{
	if (IsCommandSupported(RecvBuf, "STARTTLS") == false)
	{
		return FAIL(STARTTLS_NOT_SUPPORTED);
	}

	if (Command(command_STARTTLS))
		return FAIL(SMTP_COMM);

	OpenSSLConnect();

	if (Command(command_STARTTLS))
		return FAIL(SMTP_COMM);

	return SUCCESS;
}

RETCODE SMTPS::ReceiveData_SSL(SSL* ssl, int recv_timeout)
{
	int res = 0;
	int offset = 0;
	fd_set fdread;
	fd_set fdwrite;
	timeval time;

	int read_blocked_on_write = 0;

	time.tv_sec = recv_timeout;
	time.tv_usec = 0;

	bool bFinish = false;

	while (!bFinish)
	{
		FD_ZERO(&fdread);
		FD_ZERO(&fdwrite);

		FD_SET(hSocket, &fdread);

		if (read_blocked_on_write)
		{
			FD_SET(hSocket, &fdwrite);
		}

		if ((res = select(hSocket + 1, &fdread, &fdwrite, NULL, &time)) == SOCKET_ERROR)
		{
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			return FAIL(WSA_SELECT);
		}

		if (!res)
		{
			//timeout
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			return FAIL(SERVER_NOT_RESPONDING);
		}

		if (FD_ISSET(hSocket, &fdread) || (read_blocked_on_write && FD_ISSET(hSocket, &fdwrite)))
		{
			while (1)
			{
				read_blocked_on_write = 0;

				const int buff_len = 1024;
				char buff[buff_len];

				res = SSL_read(ssl, buff, buff_len);

				int ssl_err = SSL_get_error(ssl, res);
				if (ssl_err == SSL_ERROR_NONE)
				{
					if (offset + res > BUFFER_SIZE - 1)
					{
						FD_ZERO(&fdread);
						FD_ZERO(&fdwrite);
						return FAIL(LACK_OF_MEMORY);
					}
					RecvBuf += buff;
					offset += res;
					if (SSL_pending(ssl))
					{
						continue;
					}
					else
					{
						bFinish = true;
						break;
					}
				}
				else if (ssl_err == SSL_ERROR_ZERO_RETURN)
				{
					bFinish = true;
					break;
				}
				else if (ssl_err == SSL_ERROR_WANT_READ)
				{
					break;
				}
				else if (ssl_err == SSL_ERROR_WANT_WRITE)
				{
					/* We get a WANT_WRITE if we're
					trying to rehandshake and we block on
					a write during that rehandshake.

					We need to wait on the socket to be
					writeable but reinitiate the read
					when it is */
					read_blocked_on_write = 1;
					break;
				}
				else
				{
					FD_ZERO(&fdread);
					FD_ZERO(&fdwrite);
					return FAIL(SSL_PROBLEM);
				}
			}
		}
	}

	FD_ZERO(&fdread);
	FD_ZERO(&fdwrite);
	RecvBuf[offset] = 0;
	if (offset == 0)
	{
		return FAIL(CONNECTION_CLOSED);
	}

	return SUCCESS;
}

RETCODE SMTPS::SendData_SSL(SSL* ssl, int send_timeout)
{
	int offset = 0, res, nLeft = SendBuf.size();
	fd_set fdwrite;
	fd_set fdread;
	timeval time;

	int write_blocked_on_read = 0;

	time.tv_sec = send_timeout;
	time.tv_usec = 0;

	if (SendBuf.empty())
		return FAIL(SENDBUF_IS_EMPTY);

	const char * tempBuf = SendBuf.c_str();

	while (nLeft > 0)
	{
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdread);

		FD_SET(hSocket, &fdwrite);

		if (write_blocked_on_read)
		{
			FD_SET(hSocket, &fdread);
		}

		if ((res = select(hSocket + 1, &fdread, &fdwrite, NULL, &time)) == SOCKET_ERROR)
		{
			FD_ZERO(&fdwrite);
			FD_ZERO(&fdread);
			return FAIL(WSA_SELECT);
		}

		if (!res)
		{
			//timeout
			FD_ZERO(&fdwrite);
			FD_ZERO(&fdread);
			return FAIL(SERVER_NOT_RESPONDING);
		}

		if (FD_ISSET(hSocket, &fdwrite) || (write_blocked_on_read && FD_ISSET(hSocket, &fdread)))
		{
			write_blocked_on_read = 0;

			/* Try to write */
			res = SSL_write(ssl, tempBuf + offset, nLeft);

			switch (SSL_get_error(ssl, res))
			{
				/* We wrote something*/
			case SSL_ERROR_NONE:
				nLeft -= res;
				offset += res;
				break;

				/* We would have blocked */
			case SSL_ERROR_WANT_WRITE:
				break;

				/* We get a WANT_READ if we're
				   trying to rehandshake and we block on
				   write during the current connection.

				   We need to wait on the socket to be readable
				   but reinitiate our write when it is */
			case SSL_ERROR_WANT_READ:
				write_blocked_on_read = 1;
				break;

				/* Some other error */
			default:
				FD_ZERO(&fdread);
				FD_ZERO(&fdwrite);
				return FAIL(SSL_PROBLEM);
			}

		}
	}

	FD_ZERO(&fdwrite);
	FD_ZERO(&fdread);

	return SUCCESS;
}

RETCODE SMTPS::InitOpenSSL()
{
	SSL_library_init();
	SSL_load_error_strings();
	m_ctx = SSL_CTX_new(SSLv23_client_method());
	if (m_ctx == NULL)
		return FAIL(SSL_PROBLEM);

	return SUCCESS;
}

RETCODE SMTPS::OpenSSLConnect()
{
	if (m_ctx == NULL)
		return FAIL(SSL_PROBLEM);
	m_ssl = SSL_new(m_ctx);
	if (m_ssl == NULL)
		return FAIL(SSL_PROBLEM);
	SSL_set_fd(m_ssl, (int)hSocket);
	SSL_set_mode(m_ssl, SSL_MODE_AUTO_RETRY);

	int res = 0;
	fd_set fdwrite;
	fd_set fdread;
	int write_blocked = 0;
	int read_blocked = 0;

	timeval time;
	time.tv_sec = TIME_IN_SEC;
	time.tv_usec = 0;

	while (1)
	{
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdread);

		if (write_blocked)
			FD_SET(hSocket, &fdwrite);
		if (read_blocked)
			FD_SET(hSocket, &fdread);

		if (write_blocked || read_blocked)
		{
			write_blocked = 0;
			read_blocked = 0;
			if ((res = select(hSocket + 1, &fdread, &fdwrite, NULL, &time)) == SOCKET_ERROR)
			{
				FD_ZERO(&fdwrite);
				FD_ZERO(&fdread);
				return FAIL(WSA_SELECT);
			}
			if (!res)
			{
				//timeout
				FD_ZERO(&fdwrite);
				FD_ZERO(&fdread);
				return FAIL(SERVER_NOT_RESPONDING);
			}
		}
		res = SSL_connect(m_ssl);
		switch (SSL_get_error(m_ssl, res))
		{
		case SSL_ERROR_NONE:
			FD_ZERO(&fdwrite);
			FD_ZERO(&fdread);
			return SUCCESS;
			break;

		case SSL_ERROR_WANT_WRITE:
			write_blocked = 1;
			break;

		case SSL_ERROR_WANT_READ:
			read_blocked = 1;
			break;

		default:
			FD_ZERO(&fdwrite);
			FD_ZERO(&fdread);
			return FAIL(SSL_PROBLEM);
		}
	}
	return SUCCESS;
}

void SMTPS::CleanupOpenSSL()
{
	if (m_ssl != NULL)
	{
		SSL_shutdown(m_ssl);  /* send SSL/TLS close_notify */
		SSL_free(m_ssl);
		m_ssl = NULL;
	}
	if (m_ctx != NULL)
	{
		SSL_CTX_free(m_ctx);
		m_ctx = NULL;
		ERR_remove_state(0);
		ERR_free_strings();
		EVP_cleanup();
		CRYPTO_cleanup_all_ex_data();
	}
}