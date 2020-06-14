#include "esmtp.h"

using namespace std;
using namespace EMAIL;

ESMTP::ESMTP() : SMTP() { }
ESMTP::~ESMTP() { }

void ESMTP::Ehlo() 
{
	DEBUG_LOG(3 , "Sending EHLO command");
	SendBuf = "EHLO ";
	SendBuf += m_sLocalHostName.empty() ? "localhost" : m_sLocalHostName;
	SendBuf += "\r\n";

	ESMTP::Send();
	ESMTP::Receive();

	if (!isRetCodeValid(250))
		throw Exception::EHLO_FAILED("server return error after EHLO command");
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
	DEBUG_LOG(2, "ESMTP handshake");
	ESMTP::Command(INIT);
	ESMTP::Command(EHLO);
}

void ESMTP::Connect(const std::string& host, unsigned short port)
{
	DEBUG_LOG(2, "ESMTP connecting");
	Socket::Connect(host, port);
	ESMTP::Handshake();
}
