#include "esmtps.h"
using namespace std;

ESMTPS::ESMTPS() : SSL_() { }

void ESMTPS::SetSecuriry(SMTP_SECURITY_TYPE type)
{
	sec = type;
}

RETCODE ESMTPS::SetUpSSL()
{
	DEBUG_LOG(1, "��������� ssl ������ smpt");
	SSL_::Connect();
	DEBUG_LOG(1, "������� ����������� ���������� �� ��������� smtps � �������������� ssl");
	DEBUG_LOG(1, "����� �������� ������ �� ��������� smtps");
	return SUCCESS;
}

RETCODE ESMTPS::SetUpTLS()
{
	DEBUG_LOG(1, "������������� tsl ������ smpt");
	if (IsCommandSupported(RecvBuf, "STARTTLS") == false)
	{
		DEBUG_LOG(1, "tsl �������� �� �������������� ��������");
		return FAIL(STARTTLS_NOT_SUPPORTED);
	}

	if (Command(STARTTLS))
		return FAIL(SMTP_COMM);

	SSL_::Connect();

	DEBUG_LOG(1, "������� ����������� ���������� �� ��������� smtps � �������������� tsl");
	DEBUG_LOG(1, "����� �������� ������ �� ��������� smtps");

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
	DEBUG_LOG(1, "��������� � ������ ���������� � �������������� tls");
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