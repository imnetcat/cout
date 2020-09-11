#include "smtpclient.h"
#include "../core/logging/debug_logger.h"
#include "../core/exception/invalid_argument.h"

Cout::Network::SMTPClient::SMTPClient()
{
	DEBUG_LOG(3, "Initializing SMTP Client");
}

void Cout::Network::SMTPClient::Send(Cout::Network::Protocol::SMTP::MAIL* mail)
{
	if (mail->GetSenderMail().empty())
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "sender not specified");
	if (!mail->GetRecipientCount())
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "receiver not specified");

	mail->SetXPriority(Cout::Network::Protocol::SMTP::MAIL::PRIORITY::NORMAL);
	mail->SetXMailer("My email client");
	_component->Connect(_component->host, _component->port);
	_component->Send(mail);
	_component->Disconnect();
}

void Cout::Network::SMTPClient::SetLogin(const std::string& login)
{
	_component->SetLogin(login);
}

void Cout::Network::SMTPClient::SetPassword(const std::string& pass)
{
	_component->SetPassword(pass);
}

const std::string& Cout::Network::SMTPClient::GetLogin() const noexcept
{
	return _component->GetLogin();
}

const std::string& Cout::Network::SMTPClient::GetPassword() const noexcept
{
	return _component->GetPassword();
}

void Cout::Network::SMTPClient::SetServer(Cout::Network::Protocol::SMTP::Server::ID id)
{
	_component->host = supported.at(id).host;
	_component->port = supported.at(id).port;
	_component->sec = supported.at(id).sec;
}

const std::map<const Cout::Network::Protocol::SMTP::Server::ID, const Cout::Network::Protocol::SMTP::Server> Cout::Network::SMTPClient::supported = {
	{
		Cout::Network::Protocol::SMTP::Server::GMAIL_TLS,
		{
			Cout::Network::Protocol::Secured::Type::TLS,	"smtp.gmail.com",			587
		}
	},
	{
		Cout::Network::Protocol::SMTP::Server::GMAIL_SSL,
		{
			Cout::Network::Protocol::Secured::Type::SSL,	"smtp.gmail.com",			465
		}
	},
	{
		Cout::Network::Protocol::SMTP::Server::HOTMAIL_TSL,
		{
			Cout::Network::Protocol::Secured::Type::TLS,	"smtp.live.com",			25
		}
	},
	{
		Cout::Network::Protocol::SMTP::Server::AOL_TLS,
		{
			Cout::Network::Protocol::Secured::Type::TLS,	"smtp.aol.com",				587
		}
	},
	{
		Cout::Network::Protocol::SMTP::Server::YAHOO_SSL,
		{
			Cout::Network::Protocol::Secured::Type::SSL,	"plus.smtp.mail.yahoo.com",	465
		}
	}
};
