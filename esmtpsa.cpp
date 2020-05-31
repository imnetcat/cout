#include "esmtpsa.h"


ESMTPSA::ESMTPSA(MAIL m) : ESMTP(m) { }

void ESMTPSA::SetServerAuth(string login, string pass)
{
	credentials.login = login;
	credentials.password = pass;
}

RETCODE ESMTPSA::Auth()
{
	if (IsCommandSupported(RecvBuf, "AUTH"))
	{
		if (!credentials.login.size())
			return FAIL(UNDEF_LOGIN);

		if (!credentials.password.size())
			return FAIL(UNDEF_PASSWORD);

		if (IsCommandSupported(RecvBuf, "LOGIN") == true)
		{
			if (Command(AUTHLOGIN))
				return FAIL(SMTP_COMM);
		}
		else if (IsCommandSupported(RecvBuf, "PLAIN") == true)
		{
			if (Command(AUTHPLAIN))
				return FAIL(SMTP_COMM);
		}
		else if (IsCommandSupported(RecvBuf, "CRAM-MD5") == true)
		{
			if (Command(AUTHCRAMMD5))
				return FAIL(SMTP_COMM);
		}
		else if (IsCommandSupported(RecvBuf, "DIGEST-MD5") == true)
		{
			if (Command(AUTHDIGESTMD5))
				return FAIL(SMTP_COMM);
		}
		else
		{
			DEBUG_LOG(1, "�� ���� �� �������������� ���������� ����������� �� �������������� ��������");
			return FAIL(AUTH_NOT_SUPPORTED);
		}
	}
	else
	{
		DEBUG_LOG(1, "A��������� �� �������������� ��������");
		return FAIL(AUTH_NOT_SUPPORTED);
	}

	return SUCCESS;
}

RETCODE ESMTPSA::AuthPlain()
{
	DEBUG_LOG(1, "������������ AUTH PLAIN");

	SendBuf = "AUTH PLAIN " + Auth::Plain(credentials.login, credentials.password) + "\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(235))
		return FAIL(AUTH_PLAIN_FAILED);

	return SUCCESS;
}

RETCODE ESMTPSA::AuthLogin()
{
	DEBUG_LOG(1, "������������ AUTH LOGIN");
	SendBuf = "AUTH LOGIN\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(334))
		return FAIL(AUTH_LOGIN_FAILED);

	DEBUG_LOG(1, "�������� ������");
	string encoded_login = Auth::Login(credentials.login);
	SendBuf = encoded_login + "\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(334))
		return FAIL(UNDEF_XYZ_RESPONSE);

	DEBUG_LOG(1, "�������� ������");
	string encoded_password = Auth::Login(credentials.password);
	SendBuf = encoded_password + "\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(235))
	{
		DEBUG_LOG(1, "�������� ������/����� ��� �������� ������ �� ������������ ����������");
		return FAIL(BAD_LOGIN_PASS);
	}

	return SUCCESS;
}

RETCODE ESMTPSA::CramMD5()
{
	DEBUG_LOG(1, "������������ AUTH CRAM-MD5");
	SendBuf = "AUTH CRAM-MD5\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(334))
		return FAIL(AUTH_CRAMMD5_FAILED);

	DEBUG_LOG(1, "��������� ������");

	string encoded_challenge = Auth::CramMD5(RecvBuf.substr(4), credentials.login, credentials.password);

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(1, "������� ������ " + encoded_challenge);

	Send();
	Receive();

	if (!isRetCodeValid(334))
		return FAIL(AUTH_CRAMMD5_FAILED);

	return SUCCESS;
}

RETCODE ESMTPSA::DigestMD5()
{
	DEBUG_LOG(1, "������������ AUTH DIGEST-MD5");
	SendBuf = "AUTH DIGEST-MD5\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(335))
		return FAIL(DIGESTMD5_FAILED);

	DEBUG_LOG(1, "��������� ������");

	const string charset = RecvBuf.find("charset") != std::string::npos ?
		"charset=utf-8," : "";
	const string addr = server.name + ":" + UTILS::to_string(server.port);

	string encoded_challenge = Auth::DigestMD5(RecvBuf.substr(4), charset, addr, credentials.login, credentials.password);

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(1, "������� ������ " + encoded_challenge);

	Send();
	Receive();

	if (!isRetCodeValid(335))
		return FAIL(DIGESTMD5_FAILED);

	// only completion carraige needed for end digest md5 auth
	SendBuf = "\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(335))
		return FAIL(DIGESTMD5_FAILED);

	return SUCCESS;
}


RETCODE ESMTPSA::Command(COMMAND command)
{
	ERR	error;

	switch (command)
	{
	case AUTHPLAIN:
		if (AuthPlain())
			return FAIL(AUTH_PLAIN_FAILED);
		break;
	case AUTHLOGIN:
		if (AuthLogin())
			return FAIL(AUTH_LOGIN_FAILED);
		break;
	case AUTHCRAMMD5:
		if (CramMD5())
			return FAIL(AUTH_CRAMMD5_FAILED);
		break;
	case AUTHDIGESTMD5:
		if (DigestMD5())
			return FAIL(AUTH_DIGESTMD5_FAILED);
		break;
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

RETCODE ESMTPSA::Starttls()
{
	DEBUG_LOG(1, "��������� � ������ ���������� � �������������� tls");
	SendBuf = "STARTTLS\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(220))
		return FAIL(STARTTLS_FAILED);

	return SUCCESS;
}

void ESMTPSA::Connect()
{
	ESMTP::Connect();
}

void ESMTPSA::Disconnect()
{
	ESMTP::Disconnect();
}

void ESMTPSA::Send()
{
	DEBUG_LOG(2, "���������� ������ � �������������� ����������");
	OpenSSL::SendData();
	DEBUG_LOG(2, "������ �� ������ ���������");
}

void ESMTPSA::Receive()
{
	DEBUG_LOG(2, "��������� ����� � �������������� ����������");
	RecvBuf = OpenSSL::ReceiveData();
	DEBUG_LOG(2, "����� ������� ������");
}

RETCODE ESMTPSA::SetUpSSL()
{
	DEBUG_LOG(1, "��������� ssl ������ smpt");
	OpenSSLConnect();
	DEBUG_LOG(1, "������� ����������� ���������� �� ��������� smtps � �������������� ssl");
	DEBUG_LOG(1, "����� �������� ������ �� ��������� smtps");
	return SUCCESS;
}

RETCODE ESMTPSA::SetUpTLS()
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
