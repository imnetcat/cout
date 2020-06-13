#pragma once
#ifndef _SERVER_H_
#define _SERVER_H_
#include "esmtps.h"
#include <map>
namespace EMAIL
{
	struct Server
	{
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
			return sec == ESMTPS::NO_SECURITY ? "no security"
				: sec == ESMTPS::USE_SSL ? "ssl" : "tls";
		}
		const std::string name;
		ESMTPS::SMTP_SECURITY_TYPE sec;
		const std::string address;
		const unsigned short port;
		const bool isAuth;
		const bool reqExt;
	};
}
#endif