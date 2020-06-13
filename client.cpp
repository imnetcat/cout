#include "client.h"
using namespace std;

EMAIL::Client::Client() : smtp_server(SERVER_ID::UNDEFINED), reqSecure(ESMTPS::NO_SECURITY) { }

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

void EMAIL::Client::SetServer(SERVER_ID id) noexcept
{
	smtp_server = id;
	reqExt = supported_servers.at(id).reqExt;
	reqSecure = supported_servers.at(id).sec != ESMTPS::NO_SECURITY;
	reqAuth = supported_servers.at(id).isAuth;
	security = supported_servers.at(id).sec;
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
		throw CORE::Exception::invalid_argument("smtp server not specified");
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
		throw CORE::Exception::invalid_argument("empty sender mail");
	if (!mail.GetRecipientCount())
		throw CORE::Exception::invalid_argument("empty receiver mail");

	if (smtp_server == SERVER_ID::UNDEFINED)
		throw CORE::Exception::invalid_argument("smtp server not specified");

	if (IsEncrypRequired() && security == ESMTPSA::NO_SECURITY)
		throw CORE::Exception::invalid_argument("the set security value does not match the required server");
	if (IsAuthRequired() && !senderLogin.size())
		throw CORE::Exception::invalid_argument("the set auth value does not match the required server");

	const SUPPORTED_SERVER server = supported_servers.at(smtp_server);

	shared_ptr<SMTP> mailer = getOptimalProtocol();

	mailer->SetSMTPServer(server.port, server.address);

	mailer->Connect();
	
	mailer->SendMail(mail);

	mailer->Disconnect();
}
