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
	DEBUG_LOG(1, "��������� � ������ ���������� � �������������� tls");
	SendBuf = "STARTTLS\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (Receive(5 * 60))
		return FAIL(SMTP_RECV_DATA);
	if (!isRetCodeValid(220))
		return FAIL(STARTTLS_FAILED);

	return SUCCESS;
}

RETCODE ESMTPS::SendData(int timeout) 
{
	DEBUG_LOG(2, "���������� ������ � �������������� ����������");
	if (OpenSSL::SendData(SendBuf, timeout))
		return FAIL(SMTP_SEND_DATA_SEC);

	DEBUG_LOG(2, "������ �� ������ ���������");
	return SUCCESS;
}

RETCODE ESMTPS::Receive(int timeout)
{
	DEBUG_LOG(2, "��������� ����� � �������������� ����������");
	RecvBuf = OpenSSL::ReceiveData(timeout);
	//return FAIL(SMTP_RECV_DATA_SEC);

	DEBUG_LOG(2, "����� ������� ������");
	return SUCCESS;
}

RETCODE ESMTPS::SetUpSSL()
{
	DEBUG_LOG(1, "��������� ssl ������ smpt");
	OpenSSLConnect();
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

	OpenSSLConnect();

	DEBUG_LOG(1, "������� ����������� ���������� �� ��������� smtps � �������������� tsl");
	DEBUG_LOG(1, "����� �������� ������ �� ��������� smtps");

	if (Command(EHLO))
		return FAIL(SMTP_COMM);

	return SUCCESS;
}

RETCODE ESMTPS::Send(MAIL m)
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
	
	DEBUG_LOG(1, "�������� ������");

	if (SendMail())
		return FAIL(SMTP_SEND_MAIL);

	return SUCCESS;
}

ESMTPS::ESMTPS()
{

}

ESMTPS::~ESMTPS()
{

}
