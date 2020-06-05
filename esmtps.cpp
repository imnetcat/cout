#include "esmtps.h"
using namespace std;

ESMTPS::ESMTPS() : SSL_() { }

void ESMTPS::SetSecuriry(SMTP_SECURITY_TYPE type)
{
	sec = type;
}

void ESMTPS::SetUpSSL()
{
	DEBUG_LOG(1, "��������� ssl ������ smpt");
	SSL_::Connect();
	DEBUG_LOG(1, "������� ����������� ���������� �� ��������� smtps � �������������� ssl");
	DEBUG_LOG(1, "����� �������� ������ �� ��������� smtps");
}

void ESMTPS::SetUpTLS()
{
	DEBUG_LOG(1, "������������� tsl ������ smpt");
	if (IsCommandSupported(RecvBuf, "STARTTLS") == false)
	{
		DEBUG_LOG(1, "tsl �������� �� �������������� ��������");
		throw STARTTLS_NOT_SUPPORTED;
	}

	Command(STARTTLS);

	SSL_::Connect();

	DEBUG_LOG(1, "������� ����������� ���������� �� ��������� smtps � �������������� tsl");
	DEBUG_LOG(1, "����� �������� ������ �� ��������� smtps");

	Command(EHLO);
}

void ESMTPS::Disconnect()
{
	ESMTP::Disconnect();
}

void ESMTPS::Send()
{
	DEBUG_LOG(2, "���������� ������ � �������������� ����������");
	SSL_::Send();
	DEBUG_LOG(2, "������ �� ������ ���������");
}

void ESMTPS::Receive()
{
	DEBUG_LOG(2, "��������� ����� � �������������� ����������");
	SSL_::Receive();
	DEBUG_LOG(2, "����� ������� ������");
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
	DEBUG_LOG(1, "��������� � ������ ���������� � �������������� tls");
	SendBuf = "STARTTLS\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(220))
		throw STARTTLS_FAILED;
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