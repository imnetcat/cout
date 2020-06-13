#include "requires.h"
using namespace std;

const std::map<EMAIL::Server::ID, EMAIL::Server> EMAIL::Requires::supported = {
	{
		GMAIL_TLS,
		{
			"Gmail",	ESMTPS::SMTP_SECURITY_TYPE::USE_TLS,	"smtp.gmail.com",			587,	true, true
		}
	},
	{
		GMAIL_SSL,
		{
			"Gmail",	ESMTPS::SMTP_SECURITY_TYPE::USE_SSL,	"smtp.gmail.com",			465,	true, true
		}
	},
	{
		HOTMAIL_TSL,
		{
			"HotMail",	ESMTPS::SMTP_SECURITY_TYPE::USE_TLS,	"smtp.live.com",			25,		true, true
		}
	},
	{
		AOL_TLS,
		{
			"Aol",		ESMTPS::SMTP_SECURITY_TYPE::USE_TLS,	"smtp.aol.com",				587,	true, true
		}
	},
	{
		YAHOO_SSL,
		{
			"Yahoo",	ESMTPS::SMTP_SECURITY_TYPE::USE_SSL,	"plus.smtp.mail.yahoo.com",	465,	true, true
		}
	}
};

bool EMAIL::Requires::Auth() const noexcept
{
	return isAuth;
}
bool EMAIL::Requires::Extentions() const noexcept
{
	return reqExt;
}
bool EMAIL::Requires::Security() const noexcept
{
	return sec != ESMTPS::NO_SECURITY;
}

const map<EMAIL::Server::ID, EMAIL::Server>& EMAIL::Requires::GetSupported() noexcept
{
	return supported;
}
