#include "esmtpa.h"

RETCODE ESMTPA::Send(MAIL m)
{
	mail = m;
	if (Connect())
		return FAIL(STMP_CONNECT);

	Handshake();

	Auth();

	if (SendMail())
		return FAIL(SMTP_SEND_MAIL);

	return SUCCESS;
}

void ESMTPA::SetServerAuth(string login, string pass)
{
	credentials.login = login;
	credentials.password = pass;
}

RETCODE ESMTPA::Auth()
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
			DEBUG_LOG(1, "Не один из поддерживаемых протоколов аутификации не поддерживается сервером");
			return FAIL(AUTH_NOT_SUPPORTED);
		}
	}
	else
	{
		DEBUG_LOG(1, "Aутификаця не поддерживается сервером");
		return FAIL(AUTH_NOT_SUPPORTED);
	}

	return SUCCESS;
}

RETCODE ESMTPA::AuthPlain()
{
	DEBUG_LOG(1, "Аунтификация AUTH PLAIN");

	SendBuf = "AUTH PLAIN " + Auth::Plain(credentials.login, credentials.password) + "\r\n";

	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (Receive(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(235))
		return FAIL(AUTH_PLAIN_FAILED);

	return SUCCESS;
}

RETCODE ESMTPA::AuthLogin()
{
	DEBUG_LOG(1, "Аунтификация AUTH LOGIN");
	SendBuf = "AUTH LOGIN\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (Receive(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(334))
		return FAIL(AUTH_LOGIN_FAILED);

	DEBUG_LOG(1, "Отправка логина");
	string encoded_login = Auth::Login(credentials.login);
	SendBuf = encoded_login + "\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (Receive(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(334))
		return FAIL(UNDEF_XYZ_RESPONSE);

	DEBUG_LOG(1, "Отправка пароля");
	string encoded_password = Auth::Login(credentials.password);
	SendBuf = encoded_password + "\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (Receive(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(235))
	{
		DEBUG_LOG(1, "Неверный пароль/логин или запрещён доступ из небезопасных приложений");
		return FAIL(BAD_LOGIN_PASS);
	}

	return SUCCESS;
}

RETCODE ESMTPA::CramMD5()
{
	DEBUG_LOG(1, "Аунтификация AUTH CRAM-MD5");
	SendBuf = "AUTH CRAM-MD5\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (Receive(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(334))
		return FAIL(AUTH_CRAMMD5_FAILED);

	DEBUG_LOG(1, "Генерация токена");

	string encoded_challenge = Auth::CramMD5(RecvBuf.substr(4), credentials.login, credentials.password);

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(1, "Оправка токена " + encoded_challenge);

	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (Receive(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(334))
		return FAIL(AUTH_CRAMMD5_FAILED);

	return SUCCESS;
}

RETCODE ESMTPA::DigestMD5()
{
	DEBUG_LOG(1, "Аунтификация AUTH DIGEST-MD5");
	SendBuf = "AUTH DIGEST-MD5\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (Receive(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(335))
		return FAIL(DIGESTMD5_FAILED);

	DEBUG_LOG(1, "Генерация токена");

	const string charset = RecvBuf.find("charset") != std::string::npos ? 
		"charset=utf-8," : "";
	const string addr = server.name + ":" + UTILS::to_string(server.port);

	string encoded_challenge = Auth::DigestMD5(RecvBuf.substr(4), charset, addr, credentials.login, credentials.password);
	
	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(1, "Оправка токена " + encoded_challenge);

	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (Receive(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(335))
		return FAIL(DIGESTMD5_FAILED);

	// only completion carraige needed for end digest md5 auth
	SendBuf = "\r\n";

	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (Receive(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(335))
		return FAIL(DIGESTMD5_FAILED);

	return SUCCESS;
}

RETCODE ESMTPA::Command(COMMAND command)
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
	default:
		return ESMTP::Command(command);
		break;
	}

	return SUCCESS;
}
