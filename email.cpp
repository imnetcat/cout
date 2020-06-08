#include "email.h"
using namespace std;

EMAIL::Client::Client() : smtp_server(SERVER_ID::UNDEFINED){ }

const string& EMAIL::Client::GetLogin() const noexcept
{
	return senderLogin;
}
const string& EMAIL::Client::GetPassword() const noexcept
{
	return senderPass;
}

const std::map<EMAIL::Client::SERVER_ID, EMAIL::Client::SUPPORTED_SERVER> EMAIL::Client::supported_servers = {
			{
				GMAIL_TLS,
				{
					"Gmail",	ESMTPSA::SMTP_SECURITY_TYPE::USE_TLS,	"smtp.gmail.com",			587,	true, true
				}
			},
			{
				GMAIL_SSL,
				{
					"Gmail",	ESMTPSA::SMTP_SECURITY_TYPE::USE_SSL,	"smtp.gmail.com",			465,	true, true
				}
			},
			{
				HOTMAIL_TSL,
				{
					"HotMail",	ESMTPSA::SMTP_SECURITY_TYPE::USE_TLS,	"smtp.live.com",			25,		true, true
				}
			},
			{
				AOL_TLS,
				{
					"Aol",		ESMTPSA::SMTP_SECURITY_TYPE::USE_TLS,	"smtp.aol.com",				587,	true, true
				}
			},
			{
				YAHOO_SSL,
				{
					"Yahoo",	ESMTPSA::SMTP_SECURITY_TYPE::USE_SSL,	"plus.smtp.mail.yahoo.com",	465,	true, true
				}
			}
};

void EMAIL::Client::SetSecurity(ESMTPSA::SMTP_SECURITY_TYPE type) noexcept
{
	security = type;
}

void EMAIL::Client::SetServer(SERVER_ID id) noexcept
{
	smtp_server = id;
	reqExt = supported_servers.at(id).reqExt;
	reqSecure = supported_servers.at(id).sec != ESMTPS::NO_SECURITY;
	reqAuth = supported_servers.at(id).isAuth;
	SetSecurity(supported_servers.at(id).sec);
}

EMAIL::Client::SERVER_ID EMAIL::Client::GetServer() const noexcept
{
	return smtp_server;
}

bool EMAIL::Client::IsAuthRequired() const noexcept
{
	return reqAuth;
}
bool EMAIL::Client::IsExtRequired() const noexcept
{
	return reqExt;
}
bool EMAIL::Client::IsEncrypRequired() const noexcept
{
	return reqSecure;
}

const map<EMAIL::Client::SERVER_ID, EMAIL::Client::SUPPORTED_SERVER>& EMAIL::Client::GetSupportedServers() noexcept
{
	return supported_servers;
}

void EMAIL::Client::SetAuth(const string& login, const string& pass)
{
	if (smtp_server == SERVER_ID::UNDEFINED)
		throw 0; // add errror "set up server first"
	if (security == ESMTPS::SMTP_SECURITY_TYPE::NO_SECURITY)
		throw 0; // add errror "server not reqv security"
	senderLogin = login;
	senderPass = pass;
}

shared_ptr<EMAIL::SMTP> EMAIL::Client::getOptimalProtocol() const noexcept
{
	if (!reqExt)
	{
		return make_shared<SMTP>();
	}

	if (!reqAuth && reqSecure)
	{
		return make_shared<EMAIL::ESMTPS>();
	}
	else if (reqAuth && reqSecure)
	{
		return make_shared<EMAIL::ESMTPSA>();
	}

	return make_shared<ESMTP>();

}

void EMAIL::Client::send(MAIL mail) const
{
	if (mail.GetMailFrom().empty())
		throw CORE::EMAIL_UNDEF_SENDER;
	if (mail.GetRecipientCount())
		throw CORE::EMAIL_UNDEF_RECEIVER;

	if (reqSecure && security == ESMTPSA::NO_SECURITY)
		throw CORE::SMTP_CREATE_HEADER; // TODO: another error name
	if (reqAuth && !senderLogin.size())
		throw CORE::SMTP_CREATE_HEADER; // TODO: another error name

	const SUPPORTED_SERVER server = supported_servers.at(smtp_server);

	shared_ptr<SMTP> mailer = getOptimalProtocol();

	mailer->SetSMTPServer(server.port, server.address);

	mailer->Connect();
	
	mailer->SendMail(mail);

	mailer->Disconnect();
}
