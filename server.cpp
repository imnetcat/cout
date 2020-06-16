#include "server.h"

SMTP::Server::Server() : sec(supported.at(UNDEFINED).sec),
	host(supported.at(UNDEFINED).host),
	port(supported.at(UNDEFINED).port), isConnected(false) {};

SMTP::Server::Server(Security::Encryption::Type s, const char* h, unsigned short p) 
	: sec(s), host(h), port(p), isConnected(false) {};

inline const std::string SMTP::Server::GetSecurity() const noexcept
{
	return sec == Security::Encryption::Type::SSL ? "ssl" : "tls";
}

void SMTP::Server::Use(Server::ID id)
{
	host = supported.at(id).host;
	port = supported.at(id).port;
	sec = supported.at(id).sec;
}

const std::map<const SMTP::Server::ID, const SMTP::Server> SMTP::Server::supported = {
	{
		GMAIL_TLS,
		{
			TLS,	"smtp.gmail.com",			587
		}
	},
	{
		GMAIL_SSL,
		{
			SSL,	"smtp.gmail.com",			465
		}
	},
	{
		HOTMAIL_TSL,
		{
			TLS,	"smtp.live.com",			25
		}
	},
	{
		AOL_TLS,
		{
			TLS,	"smtp.aol.com",				587
		}
	},
	{
		YAHOO_SSL,
		{
			SSL,	"plus.smtp.mail.yahoo.com",	465
		}
	}
};
