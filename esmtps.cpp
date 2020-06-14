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
	DEBUG_LOG(2, "Setting up SSL over ESMTP");
	SSL::Connect(host, port);
	DEBUG_LOG(2, "Successfuly set up SSL over ESMTP connection");
}

void ESMTPS::SetUpTLS()
{
	DEBUG_LOG(2, "Setting up TLS over ESMTP");
	if (IsCommandSupported(RecvBuf, "STARTTLS") == false)
	{
		throw Exception::STARTTLS_NOT_SUPPORTED("attempt to set up TLS over ESMTP");
	}

	ESMTPS::Command(STARTTLS);

	SSL::Connect(host, port);

	ESMTPS::Command(EHLO);

	DEBUG_LOG(2, "Successfuly set up TLS over ESMTP connection");
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
	DEBUG_LOG(3, "Sending STARTTLS command");
	SendBuf = "STARTTLS\r\n";
	Socket::Send();
	Socket::Receive();

	if (!isRetCodeValid(220))
		throw Exception::STARTTLS_FAILED("attempt to set up tls over SMTP");
}

void ESMTPS::Connect(const std::string& host, unsigned short port)
{
	DEBUG_LOG(1, "ESMTPS Connecting");
	Socket::Connect(host, port);
	
	if (sec == USE_SSL)
	{
		SetUpSSL();
	}

	ESMTP::Handshake();

	if (sec == USE_TLS)
	{
		SetUpTLS();
	}
}