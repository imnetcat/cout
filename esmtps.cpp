#include "esmtps.h"
using namespace std;

ESMTPS::ESMTPS() : SSL_() { }

void ESMTPS::SetSecuriry(SMTP_SECURITY_TYPE type)
{
	sec = type;
}

RETCODE ESMTPS::SetUpSSL()
{
	DEBUG_LOG(1, "Установка ssl поверх smpt");
	SSL_::Connect();
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

	SSL_::Connect();

	DEBUG_LOG(1, "Успешно установлено соеденение по протоколу smtps с использованием tsl");
	DEBUG_LOG(1, "Далее передача данных по протоколу smtps");

	if (Command(EHLO))
		return FAIL(SMTP_COMM);

	return SUCCESS;
}

void ESMTPS::Disconnect()
{
	ESMTP::Disconnect();
}

void ESMTPS::Send()
{
	DEBUG_LOG(2, "Отправляем запрос с использованием шифрования");
	SSL_::Send();
	DEBUG_LOG(2, "Запрос на сервер отправлен");
}

void ESMTPS::Receive()
{
	DEBUG_LOG(2, "Принимаем ответ с использованием шифрования");
	SSL_::Receive();
	DEBUG_LOG(2, "Ответ сервера принят");
}

RETCODE ESMTPS::Command(COMMAND command)
{
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
	Send();
	Receive();

	if (!isRetCodeValid(220))
		return FAIL(STARTTLS_FAILED);

	return SUCCESS;
}

void ESMTPS::Connect()
{
	Raw::Connect();

	if (sec == USE_SSL)
	{
		SetUpSSL();
	}

	Handshake();

	if (sec == USE_TLS)
	{
		SetUpTLS();
	}
}