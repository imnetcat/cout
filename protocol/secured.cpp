#include "secured.h"
#include "exception.h"
#include "../core/exception.h"
#include "../encryption/exception.h"
using namespace Protocol;

Secured::Secured() : isSecured(false) {};

void Secured::Receive()
{
	if (!isSecured)
	{
		Raw::Receive();
		return;
	}

	int res = 0;
	int offset = 0;
	fd_set fdread;
	fd_set fdwrite;
	timeval time;

	int read_blocked_on_write = 0;

	time.tv_sec = TIMEOUT;
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

		if ((res = select(static_cast<int>(hSocket) + 1, &fdread, &fdwrite, NULL, &time)) == SOCKET_ERROR)
		{
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::wsa::select("ssl receiving select");
		}

		if (!res)
		{
			//timeout
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::wsa::server_not_responding("ssl receiving select");
		}

		if (FD_ISSET(hSocket, &fdread) || (read_blocked_on_write && FD_ISSET(hSocket, &fdwrite)))
		{
			while (true)
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
						isConnected = false;
						throw Exceptions::Core::lack_of_memory("ssl receiving");
					}
					RecvBuf = buff;
					offset += res;
					RecvBuf[offset] = '\0';
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
					/*
						We get a WANT_WRITE if we're
						trying to rehandshake and we block on
						a write during that rehandshake.

						We need to wait on the socket to be
						writeable but reinitiate the read
						when it is
					*/
					read_blocked_on_write = 1;
					break;
				}
				else
				{
					FD_ZERO(&fdread);
					FD_ZERO(&fdwrite);
					isConnected = false;
					throw Exceptions::Encryption::openssl_problem("ssl receiving");
				}
			}
		}
	}

	FD_ZERO(&fdread);
	FD_ZERO(&fdwrite);
	if (offset == 0)
	{
		isConnected = false;
		throw Exceptions::wsa::connection_closed("ssl receiving");
	}
}

void Secured::Send()
{
	if (!isSecured)
	{
		Raw::Send();
		return;
	}
	size_t res;
	fd_set fdwrite;
	fd_set fdread;
	timeval time;

	int write_blocked_on_read = 0;

	time.tv_sec = TIMEOUT;
	time.tv_usec = 0;
	
	FD_ZERO(&fdwrite);
	FD_ZERO(&fdread);

	FD_SET(hSocket, &fdwrite);

	if (write_blocked_on_read)
	{
		FD_SET(hSocket, &fdread);
	}

	if ((res = select(static_cast<int>(hSocket) + 1, &fdread, &fdwrite, NULL, &time)) == SOCKET_ERROR)
	{
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdread);
		isConnected = false;
		throw Exceptions::wsa::select("ssl send select");
	}

	if (!res)
	{
		//timeout
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdread);
		isConnected = false;
		throw Exceptions::wsa::server_not_responding("ssl send select");
	}

	if (FD_ISSET(hSocket, &fdwrite) || (write_blocked_on_read && FD_ISSET(hSocket, &fdread)))
	{
		write_blocked_on_read = 0;

		// Try to write
		res = SSL_write(ssl, SendBuf.c_str(), static_cast<int>(SendBuf.size()));
		SendBuf.clear();

		int code = SSL_get_error(ssl, static_cast<int>(res));
		switch (code)
		{
			// We wrote something
		case SSL_ERROR_NONE:
			break;

			// We would have blocked 
		case SSL_ERROR_WANT_WRITE:
			break;

			/*
			   We get a WANT_READ if we're
			   trying to rehandshake and we block on
			   write during the current connection.

			   We need to wait on the socket to be readable
			   but reinitiate our write when it is
			*/
		case SSL_ERROR_WANT_READ:
			write_blocked_on_read = 1;
			break;
		case SSL_ERROR_ZERO_RETURN:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_zero_return("ssl send");
			break;
		case SSL_ERROR_WANT_CONNECT:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_zero_return("ssl send");
			break;
		case SSL_ERROR_WANT_ACCEPT:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_want_accept("ssl send");
			break;
		case SSL_ERROR_WANT_X509_LOOKUP:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_want_lookup("ssl send");
			break;
		case SSL_ERROR_WANT_ASYNC:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_want_async("ssl send");
			break;
		case SSL_ERROR_SYSCALL:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_syscall("ssl send");
			break;
		default:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_problem("ssl send");
		}
	}

	FD_ZERO(&fdwrite);
	FD_ZERO(&fdread);
}

void Secured::Connect(const std::string& host, unsigned short port)
{
	if (!isConnected)
		Raw::Connect(host, port);
}
void Secured::SetUpSSL()
{
	if (ctx == NULL)
		throw Exceptions::Encryption::openssl_problem("ssl invalid context");
	ssl = SSL_new(ctx);
	if (ssl == NULL)
		throw Exceptions::Encryption::openssl_problem("ssl new failed");
	SSL_set_fd(ssl, (int)hSocket);
	SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

	int res = 0;
	fd_set fdwrite;
	fd_set fdread;
	int write_blocked = 0;
	int read_blocked = 0;

	timeval time;
	time.tv_sec = TIMEOUT;
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
			if ((res = select(static_cast<int>(hSocket) + 1, &fdread, &fdwrite, NULL, &time)) == SOCKET_ERROR)
			{
				FD_ZERO(&fdwrite);
				FD_ZERO(&fdread);
				isConnected = false;
				throw Exceptions::wsa::select("ssl connect select");
			}
			if (!res)
			{
				//timeout
				FD_ZERO(&fdwrite);
				FD_ZERO(&fdread);
				isConnected = false;
				throw Exceptions::wsa::server_not_responding("ssl connect select");
			}
		}
		res = SSL_connect(ssl);
		switch (SSL_get_error(ssl, res))
		{
		case SSL_ERROR_NONE:
			FD_ZERO(&fdwrite);
			FD_ZERO(&fdread);
			isSecured = true;
			return;
			break;

		case SSL_ERROR_WANT_WRITE:
			write_blocked = 1;
			break;

		case SSL_ERROR_WANT_READ:
			read_blocked = 1;
			break;

		case SSL_ERROR_ZERO_RETURN:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_zero_return("ssl connect");
			break;
		case SSL_ERROR_WANT_CONNECT:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_zero_return("ssl connect");
			break;
		case SSL_ERROR_WANT_ACCEPT:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_want_accept("ssl connect");
			break;
		case SSL_ERROR_WANT_X509_LOOKUP:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_want_lookup("ssl connect");
			break;
		case SSL_ERROR_WANT_ASYNC:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_want_async("ssl connect");
			break;
		case SSL_ERROR_SYSCALL:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_syscall("ssl connect");
			break;
		default:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			isConnected = false;
			throw Exceptions::Encryption::openssl_problem("ssl connect");
		}
	}
}

void Secured::Disconnect()
{
	Raw::Disconnect();
	isSecured = false;
}