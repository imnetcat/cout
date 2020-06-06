#include "esmtps.h"
using namespace std;
using namespace EMAIL;

ESMTPS::ESMTPS() : Security::SSL<ESMTP>() { }

void ESMTPS::SetSecuriry(SMTP_SECURITY_TYPE type)
{
	sec = type;
}

void ESMTPS::SetUpSSL()
{
	DEBUG_LOG(1, "Установка ssl поверх smpt");
	SSL::Connect();
	DEBUG_LOG(1, "Успешно установлено соеденение по протоколу smtps с использованием ssl");
	DEBUG_LOG(1, "Далее передача данных по протоколу smtps");
}

void ESMTPS::SetUpTLS()
{
	DEBUG_LOG(1, "Устанавливаем tsl поверх smpt");
	if (IsCommandSupported(RecvBuf, "STARTTLS") == false)
	{
		DEBUG_LOG(1, "tsl протокол не поддерживается сервером");
		throw CORE::STARTTLS_NOT_SUPPORTED;
	}

	Command(STARTTLS);

	SSL::Connect();

	DEBUG_LOG(1, "Успешно установлено соеденение по протоколу smtps с использованием tsl");
	DEBUG_LOG(1, "Далее передача данных по протоколу smtps");

	Command(EHLO);
}

void ESMTPS::Disconnect()
{
	ESMTP::Disconnect();
}

void ESMTPS::Send()
{
	DEBUG_LOG(2, "Отправляем запрос с использованием шифрования");
	SSL::Send();
	DEBUG_LOG(2, "Запрос на сервер отправлен");
}

void ESMTPS::Receive()
{
	DEBUG_LOG(2, "Принимаем ответ с использованием шифрования");
	SSL::Receive();
	DEBUG_LOG(2, "Ответ сервера принят");
}

void ESMTPS::Command(COMMAND command)
{
	switch (command)
	{
	case STARTTLS:
		Starttls();
		break;
	default:
		return ESMTP::Command(command);
		break;
	}
}

void ESMTPS::Starttls()
{
	DEBUG_LOG(1, "Обьявляем о начале соеденения с использованием tls");
	SendBuf = "STARTTLS\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(220))
		throw CORE::STARTTLS_FAILED;
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