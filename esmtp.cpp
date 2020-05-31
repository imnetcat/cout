#include "esmtp.h"

using namespace std;

ESMTP::ESMTP(MAIL m) : SMTP(m) { }
ESMTP::~ESMTP() { }

RETCODE ESMTP::Ehlo() 
{
	DEBUG_LOG(1 , "Отправка EHLO комманды");
	SendBuf = "EHLO ";
	SendBuf += m_sLocalHostName.empty() ? "localhost" : m_sLocalHostName;
	SendBuf += "\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(250))
		return FAIL(EHLO_FAILED);

	return SUCCESS;
}

RETCODE ESMTP::Command(COMMAND command)
{
	ERR	error;

	switch (command)
	{
	case ESMTP::EHLO:
		if (Ehlo())
			return FAIL(EHLO_FAILED);
		break;
	default:
		return SMTP::Command(command);
		break;
	}

	return SUCCESS;
}

RETCODE ESMTP::Handshake()
{
	DEBUG_LOG(1, "Рукопожатие с сервером по протоколу ESMTP");
	if (Command(INIT))
		return FAIL(SMTP_COMM);
	if (Command(EHLO))
		return FAIL(SMTP_COMM);

	return SUCCESS;
}

void ESMTP::Connect()
{
	SMTP::Connect();
}

void ESMTP::Disconnect()
{
	SMTP::Disconnect();
}

void ESMTP::Send()
{
	SMTP::Send();
}

void ESMTP::Receive()
{
	SMTP::Receive();
}