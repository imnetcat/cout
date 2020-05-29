#include "esmtps.h"

RETCODE ESMTPS::Command(COMMAND command)
{
	ERR	error;

	switch (command)
	{
	case STARTTLS:
		if (Starttls())
			return FAIL(STARTTLS_FAILED);
		break;
	default:
		return ESMTP::Command(command);
		break;
	}

	return SUCCESS;
}

RETCODE ESMTPS::Starttls()
{
	DEBUG_LOG(1, "Обьявляем о начале соеденения с использованием tls");
	SendBuf = "STARTTLS\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);
	if (!isRetCodeValid(220))
		return FAIL(STARTTLS_FAILED);

	return SUCCESS;
}

RETCODE ESMTPS::SendData(int timeout)
{
	DEBUG_LOG(2, "Отправляем запрос с использованием шифрования");
	if (SendData_SSL(timeout))
		return FAIL(SMTP_SEND_DATA_SEC);

	DEBUG_LOG(2, "Запрос на сервер отправлен");
	return SUCCESS;
}

RETCODE ESMTPS::ReceiveData(int timeout)
{
	DEBUG_LOG(2, "Принимаем ответ с использованием шифрования");
	if (ReceiveData_SSL(timeout))
		return FAIL(SMTP_RECV_DATA_SEC);

	DEBUG_LOG(2, "Ответ сервера принят");
	return SUCCESS;
}

RETCODE ESMTPS::SetUpSSL()
{
	DEBUG_LOG(1, "Установка ssl поверх smpt");
	OpenSSLConnect();
	DEBUG_LOG(1, "Успешно установлено соеденение по протоколу smtps с использованием ssl");
	DEBUG_LOG(1, "Далее передача данных по протоколу smtps");
	return SUCCESS;
}

RETCODE ESMTPS::SetUpTLS()
{
	DEBUG_LOG(1, "Устанавливаем tsl поверх smpt");
	if (IsCommandSupported(RecvBuf, "STARTTLS") == false)
	{
		DEBUG_LOG(1, "tsl протокол не поддерживается сервером");
		return FAIL(STARTTLS_NOT_SUPPORTED);
	}

	if (Command(STARTTLS))
		return FAIL(SMTP_COMM);

	OpenSSLConnect();

	DEBUG_LOG(1, "Успешно установлено соеденение по протоколу smtps с использованием tsl");
	DEBUG_LOG(1, "Далее передача данных по протоколу smtps");

	if (Command(EHLO))
		return FAIL(SMTP_COMM);

	return SUCCESS;
}

RETCODE ESMTPS::Send(MAIL m, SMTP_SECURITY_TYPE sec)
{
	mail = m;
	if (Connect())
		return FAIL(STMP_CONNECT);
	
	if (sec == USE_SSL)
	{
		SetUpSSL();
	}

	Handshake();
	
	if (sec == USE_TLS)
	{
		SetUpTLS();
	}
	
	DEBUG_LOG(1, "Отправка письма");

	if (SendMail())
		return FAIL(SMTP_SEND_MAIL);

	return SUCCESS;
}

ESMTPS::ESMTPS()
{

}

ESMTPS::~ESMTPS()
{
	CleanupOpenSSL();
}

RETCODE ESMTPS::OpenSSLConnect()
{
	if (ctx == NULL)
		return FAIL(SSL_PROBLEM);
	ssl = SSL_new(ctx);
	if (ssl == NULL)
		return FAIL(SSL_PROBLEM);
	SSL_set_fd(ssl, (int)hSocket);
	SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

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
		res = SSL_connect(ssl);
		switch (SSL_get_error(ssl, res))
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

void ESMTPS::CleanupOpenSSL()
{
	if (ssl != NULL)
	{
		SSL_shutdown(ssl);  /* send SSL/TLS close_notify */
		SSL_free(ssl);
		ssl = NULL;
	}
	if (ctx != NULL)
	{
		SSL_CTX_free(ctx);
		ctx = NULL;
		ERR_remove_state(0);
		ERR_free_strings();
		EVP_cleanup();
		CRYPTO_cleanup_all_ex_data();
	}
}