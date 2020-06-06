#include "esmtp.h"

using namespace std;

ESMTP::ESMTP() : SMTP() { }
ESMTP::~ESMTP() { }

void ESMTP::Ehlo() 
{
	DEBUG_LOG(1 , "Отправка EHLO комманды");
	SendBuf = "EHLO ";
	SendBuf += m_sLocalHostName.empty() ? "localhost" : m_sLocalHostName;
	SendBuf += "\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(250))
		throw CORE::EHLO_FAILED;
}

void ESMTP::Command(COMMAND command)
{
	switch (command)
	{
	case ESMTP::EHLO:
		Ehlo();
		break;
	default:
		return SMTP::Command(command);
		break;
	}
}

void ESMTP::Handshake()
{
	DEBUG_LOG(1, "Рукопожатие с сервером по протоколу ESMTP");
	Command(INIT);
	Command(EHLO);
}

void ESMTP::Connect()
{
	Raw::Connect();
	Handshake();
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