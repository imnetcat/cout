#pragma once
#ifndef _CLIENT_H_
#define _CLIENT_H_
#include "esmtpsa.h"
#include "../../core/patterns/facade.h"
#include <string>
namespace Protocol
{
	namespace SMTP
	{
		class Client : private CORE::PATTERN::Facade<ESMTPSA>
		{
		public:
			Client();
			void SetServer(Server::ID id);
			void SetLogin(const std::string& login);
			void SetPassword(const std::string& pass);
			void Send(MAIL* mail);

			static const std::map<const Server::ID, const Server> supported;
		};
	}
}
#endif