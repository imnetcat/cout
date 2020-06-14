#pragma once
#ifndef _CLIENT_H_
#define _CLIENT_H_
#include "mail.h"
#include "requires.h"
#include "smtp.h"
#include "esmtp.h"
#include "esmtps.h"
#include "esmtpsa.h"
#include "exceptions.h"
#include <memory>
#include <map>
namespace EMAIL
{
	class Client : public MAIL
	{
	public:
		Client() {};
		void send() const;
		void Use(Server::ID id);
		void Use(Server id);
		void SetAuth(const std::string& login, const std::string& pass);

		const std::string& GetLogin() const noexcept;
		const std::string& GetPassword() const noexcept;

		std::shared_ptr<SMTP> getOptimalProtocol() const noexcept;
	private:
		Requires required;

		std::string senderLogin;
		std::string senderPass;
	};
}
#endif