#pragma once
#ifndef _SERVER_H_
#define _SERVER_H_
#include "security.h"
#include <map>
namespace SMTP
{
	struct Server
	{
	public:

		enum ID
		{
			UNDEFINED,
			GMAIL_TLS,
			GMAIL_SSL,
			HOTMAIL_TSL,
			AOL_TLS,
			YAHOO_SSL
		};

		Server();
		Server(Security::Encryption::Type s, const char* h, unsigned short p);

		inline const std::string GetSecurity() const noexcept;

		void Use(Server::ID id);
		
	protected:
		Security::Encryption::Type sec;
		const char* host;
		unsigned short port;
		bool isConnected;
		
	private:
		static const std::map<const Server::ID, const Server> supported;
	};
}
#endif