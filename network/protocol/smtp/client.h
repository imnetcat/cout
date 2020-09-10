#pragma once
#include "mail/mail.h"
#include "esmtpsa.h"
#include "../../../core/pattern/facade.h"
#include <string>
namespace Protocol
{
	namespace SMTP
	{
		class Client : private Core::Pattern::Facade<ESMTPSA>
		{
		public:
			Client();
			void SetServer(Server::ID id);
			void SetLogin(const std::string& login);
			void SetPassword(const std::string& pass);
			const std::string& GetLogin() const noexcept;
			const std::string& GetPassword() const noexcept;
			void Send(MAIL* mail);

			static const std::map<const Server::ID, const Server> supported;
		};
	}
}