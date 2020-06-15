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
			GMAIL_TLS,
			GMAIL_SSL,
			HOTMAIL_TSL,
			AOL_TLS,
			YAHOO_SSL
		};
		inline const std::string GetSecurity() const noexcept
		{
			return sec == Security::Encryption::Type::SSL ? "ssl" : "tls";
		}

		void Use(Server::ID id)
		{
			host = supported.at(id).host;
			port = supported.at(id).port;
			sec = supported.at(id).sec;
		}

		void Use(const std::string& h, unsigned short p)
		{
			host = h;
			port = p;
		}

		void Use(Security::Encryption::Type s)
		{
			sec = s;
		}


	protected:
		bool isConnected;
		Security::Encryption::Type sec;
		std::string host;
		unsigned short port;
		
	private:
		static const std::map<Server::ID, Server> supported;
	};
}
#endif