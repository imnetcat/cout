#pragma once
#ifndef _EMAIL_H_
#define _EMAIL_H_
#include "mail.h"
#include "smtp.h"
#include "esmtp.h"
#include "esmtps.h"
#include "esmtpsa.h"
#include "exceptions.h"
#include <memory>
#include <map>
namespace EMAIL
{
	class Client
	{
	public:
		Client();
		void send(MAIL mail) const;
		void SetAuth(const std::string& login, const std::string& pass);
		const std::string& GetLogin() const noexcept;
		const std::string& GetPassword() const noexcept;

		bool IsAuthRequired() const noexcept;
		bool IsExtRequired() const noexcept;
		bool IsEncrypRequired() const noexcept;

		enum SERVER_ID {
			UNDEFINED = 0,
			GMAIL_TLS = 1,
			GMAIL_SSL,
			HOTMAIL_TSL,
			AOL_TLS,
			YAHOO_SSL
		};
		struct SUPPORTED_SERVER
		{
			const std::string name;
			ESMTPS::SMTP_SECURITY_TYPE sec;
			inline const std::string GetSecurity() const noexcept
			{
				return sec == ESMTPS::NO_SECURITY ? "no security"
					: sec == ESMTPS::USE_SSL ? "ssl" : "tls";
			}
			const std::string address;
			const unsigned short port;
			const bool isAuth;
			bool reqExt;
		};
		static const std::map<SERVER_ID, SUPPORTED_SERVER>& GetSupportedServers() noexcept;
		void SetServer(SERVER_ID id) noexcept;
		SERVER_ID GetServer() const noexcept;

		std::shared_ptr<SMTP> getOptimalProtocol() const noexcept;

		static const std::map<SERVER_ID, SUPPORTED_SERVER> supported_servers;

		bool reqAuth;
		bool reqSecure;
		bool reqExt;

		std::string senderLogin;
		std::string senderPass;

		ESMTPSA::SMTP_SECURITY_TYPE security = ESMTPSA::SMTP_SECURITY_TYPE::NO_SECURITY;

		SERVER_ID smtp_server;
	};
}
#endif