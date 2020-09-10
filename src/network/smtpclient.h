#pragma once
#include "protocol/smtp/mail/mail.h"
#include "protocol/smtp/esmtpsa.h"
#include "../core/pattern/facade.h"
#include <string>
namespace Cout
{
	namespace Network
	{
		class SMTPClient : private Core::Pattern::Facade<Protocol::SMTP::ESMTPSA>
		{
		public:
			SMTPClient();
			void SetServer(Protocol::SMTP::Server::ID id);
			void SetLogin(const std::string& login);
			void SetPassword(const std::string& pass);
			const std::string& GetLogin() const noexcept;
			const std::string& GetPassword() const noexcept;
			void Send(Protocol::SMTP::MAIL* mail);

			static const std::map<const Protocol::SMTP::Server::ID, const Protocol::SMTP::Server> supported;
		};
	}
}