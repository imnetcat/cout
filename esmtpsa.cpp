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
	DEBUG_LOG(3, "Choosing authentication");
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
			throw Exception::AUTH_NOT_SUPPORTED("SMTP authentication selection");
		}
	}
	else
	{
		throw Exception::AUTH_NOT_SUPPORTED("SMTP authentication selection");
	}
}

void ESMTPSA::AuthPlain()
{
	DEBUG_LOG(2, "Authentication AUTH PLAIN");

	SendBuf = "AUTH PLAIN " + Auth::Plain(credentials.login, credentials.password) + "\r\n";

	ESMTPSA::Send();
	ESMTPSA::Receive();

	if (!isRetCodeValid(235))
		throw Exception::AUTH_PLAIN_FAILED("SMTP Plain authentication");
}

void ESMTPSA::AuthLogin()
{
	DEBUG_LOG(2, "Authentication AUTH LOGIN");
	SendBuf = "AUTH LOGIN\r\n";
	ESMTPSA::Send();
	ESMTPSA::Receive();

	if (!isRetCodeValid(334))
		throw Exception::AUTH_LOGIN_FAILED("SMTP LOGIN authentication");

	DEBUG_LOG(3, "Sending login");
	string encoded_login = Auth::Login(credentials.login);
	SendBuf = encoded_login + "\r\n";
	ESMTPSA::Send();
	ESMTPSA::Receive();

	if (!isRetCodeValid(334))
		throw Exception::UNDEF_XYZ_RESPONSE("SMTP LOGIN authentication");

	DEBUG_LOG(3, "Sending password");
	string encoded_password = Auth::Login(credentials.password);
	SendBuf = encoded_password + "\r\n";
	ESMTPSA::Send();
	ESMTPSA::Receive();

	if (!isRetCodeValid(235))
	{
		throw Exception::BAD_LOGIN_PASS("SMTP LOGIN authentication");
	}
}

void ESMTPSA::CramMD5()
{
	DEBUG_LOG(2, "Authentication AUTH CRAM-MD5");
	SendBuf = "AUTH CRAM-MD5\r\n";
	ESMTPSA::Send();
	ESMTPSA::Receive();

	if (!isRetCodeValid(334))
		throw Exception::AUTH_CRAMMD5_FAILED("SMTP CRAM-MD5 authentication");

	DEBUG_LOG(3, "Token generation");

	string encoded_challenge = Auth::CramMD5(RecvBuf.substr(4), credentials.login, credentials.password);

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(1, "Token sending " + encoded_challenge);

	ESMTPSA::Send();
	ESMTPSA::Receive();

	if (!isRetCodeValid(334))
		throw Exception::AUTH_CRAMMD5_FAILED("SMTP CRAM-MD5 authentication");
}

void ESMTPSA::DigestMD5()
{
	DEBUG_LOG(2, "Authentication AUTH DIGEST-MD5");
	SendBuf = "AUTH DIGEST-MD5\r\n";
	ESMTPSA::Send();
	ESMTPSA::Receive();

	if (!isRetCodeValid(335))
		throw Exception::DIGESTMD5_FAILED("SMTP DIGEST-MD5 authentication");

	DEBUG_LOG(3, "Token generation");

	const string charset = RecvBuf.find("charset") != std::string::npos ?
		"charset=utf-8," : "";
	const string addr = host + ":" + CORE::UTILS::to_string(port);

	string encoded_challenge = Auth::DigestMD5(RecvBuf.substr(4), charset, addr, credentials.login, credentials.password);

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(3, "Token sending " + encoded_challenge);

	ESMTPSA::Send();
	ESMTPSA::Receive();

	if (!isRetCodeValid(335))
		throw Exception::DIGESTMD5_FAILED("SMTP DIGEST-MD5 authentication");

	// only completion carraige needed for end digest md5 auth
	SendBuf = "\r\n";

	ESMTPSA::Send();
	ESMTPSA::Receive();

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

void ESMTPSA::Connect(const std::string& host, unsigned short port)
{
	DEBUG_LOG(3, "EMSTPSA Connecting");
	ESMTPS::Connect(host, port);
	
	Auth();
}
