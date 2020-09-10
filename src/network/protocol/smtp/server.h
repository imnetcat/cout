#pragma once
#include "../secured.h"
#include <map>
namespace Cout
{
	namespace Network
	{
		namespace Protocol
		{
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
					Server(Secured::Type s, const char* h, unsigned short p);

					inline const std::string GetSecurity() const noexcept;

					const char* host;
					unsigned short port;
					Secured::Type sec;
				};
			}
		}
	}
}