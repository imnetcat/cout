#include "esmtpsa.h"
using namespace std;
using namespace EMAIL;

ESMTPSA::ESMTPSA() : ESMTPS() { }

void ESMTPSA::SetServerAuth(const string& login, const string& pass)
{
	credentials.login = login;
	credentials.password = pass;
}

void ESMTPSA::Auth()
{
	if (IsCommandSupported(RecvBuf, "AUTH"))
	{
		if (!credentials.login.size())
			throw Exception::UNDEF_LOGIN("SMTP authentication selection");

		if (!credentials.password.size())
			throw Exception::UNDEF_PASSWORD("SMTP authentication selection");

		if (IsCommandSupported(RecvBuf, "LOGIN") == true)
		{
			Command(AUTHLOGIN);
		}
		else if (IsCommandSupported(RecvBuf, "PLAIN") == true)
		{
			Command(AUTHPLAIN);
		}
		else if (IsCommandSupported(RecvBuf, "CRAM-MD5") == true)
		{
			Command(AUTHCRAMMD5);
		}
		else if (IsCommandSupported(RecvBuf, "DIGEST-MD5") == true)
		{
			Command(AUTHDIGESTMD5);
		}
		else
		{
			DEBUG_LOG(1, "Не один из поддерживаемых протоколов аутификации не поддерживается сервером");
			throw Exception::AUTH_NOT_SUPPORTED("SMTP authentication selection");
		}
	}
	else
	{
		DEBUG_LOG(1, "Aутификаця не поддерживается сервером");
		throw Exception::AUTH_NOT_SUPPORTED("SMTP authentication selection");
	}
}

void ESMTPSA::AuthPlain()
{
	DEBUG_LOG(1, "Аунтификация AUTH PLAIN");

	SendBuf = "AUTH PLAIN " + Auth::Plain(credentials.login, credentials.password) + "\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(235))
		throw Exception::AUTH_PLAIN_FAILED("SMTP Plain authentication");
}

void ESMTPSA::AuthLogin()
{
	DEBUG_LOG(1, "Аунтификация AUTH LOGIN");
	SendBuf = "AUTH LOGIN\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(334))
		throw Exception::AUTH_LOGIN_FAILED("SMTP LOGIN authentication");

	DEBUG_LOG(1, "Отправка логина");
	string encoded_login = Auth::Login(credentials.login);
	SendBuf = encoded_login + "\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(334))
		throw Exception::UNDEF_XYZ_RESPONSE("SMTP LOGIN authentication");

	DEBUG_LOG(1, "Отправка пароля");
	string encoded_password = Auth::Login(credentials.password);
	SendBuf = encoded_password + "\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(235))
	{
		DEBUG_LOG(1, "Неверный пароль/логин или запрещён доступ из небезопасных приложений");
		throw Exception::BAD_LOGIN_PASS("SMTP LOGIN authentication");
	}
}

void ESMTPSA::CramMD5()
{
	DEBUG_LOG(1, "Аунтификация AUTH CRAM-MD5");
	SendBuf = "AUTH CRAM-MD5\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(334))
		throw Exception::AUTH_CRAMMD5_FAILED("SMTP CRAM-MD5 authentication");

	DEBUG_LOG(1, "Генерация токена");

	string encoded_challenge = Auth::CramMD5(RecvBuf.substr(4), credentials.login, credentials.password);

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(1, "Оправка токена " + encoded_challenge);

	Send();
	Receive();

	if (!isRetCodeValid(334))
		throw Exception::AUTH_CRAMMD5_FAILED("SMTP CRAM-MD5 authentication");
}

void ESMTPSA::DigestMD5()
{
	DEBUG_LOG(1, "Аунтификация AUTH DIGEST-MD5");
	SendBuf = "AUTH DIGEST-MD5\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(335))
		throw Exception::DIGESTMD5_FAILED("SMTP DIGEST-MD5 authentication");

	DEBUG_LOG(1, "Генерация токена");

	const string charset = RecvBuf.find("charset") != std::string::npos ?
		"charset=utf-8," : "";
	const string addr = server.name + ":" + CORE::UTILS::to_string(server.port);

	string encoded_challenge = Auth::DigestMD5(RecvBuf.substr(4), charset, addr, credentials.login, credentials.password);

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(1, "Оправка токена " + encoded_challenge);

	Send();
	Receive();

	if (!isRetCodeValid(335))
		throw Exception::DIGESTMD5_FAILED("SMTP DIGEST-MD5 authentication");

	// only completion carraige needed for end digest md5 auth
	SendBuf = "\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(335))
		throw Exception::DIGESTMD5_FAILED("SMTP DIGEST-MD5 authentication");
}


void ESMTPSA::Command(COMMAND command)
{
	switch (command)
	{
	case AUTHPLAIN:
		AuthPlain();
		break;
	case AUTHLOGIN:
		AuthLogin();
		break;
	case AUTHCRAMMD5:
		CramMD5();
		break;
	case AUTHDIGESTMD5:
		DigestMD5();
		break;
	default:
		return ESMTP::Command(command);
		break;
	}
}

void ESMTPSA::Connect()
{
	ESMTPS::Connect();
	
	Auth();
}

void ESMTPSA::Disconnect()
{
	ESMTPS::Disconnect();
}

void ESMTPSA::Send()
{
	DEBUG_LOG(2, "Отправляем запрос с использованием шифрования");
	ESMTPS::Send();
	DEBUG_LOG(2, "Запрос на сервер отправлен");
}

void ESMTPSA::Receive()
{
	DEBUG_LOG(2, "Принимаем ответ с использованием шифрования");
	ESMTPS::Receive();
	DEBUG_LOG(2, "Ответ сервера принят");
}
