#pragma once
#include "../../../core/exception/base.h"
namespace Cout
{
	namespace Network
	{
		namespace Protocol
		{
			namespace Exceptions
			{
				namespace Auth
				{
					class bad_credentials : virtual public Cout::Exceptions::base
					{
					public:
						bad_credentials(const std::string& whre, const std::string& when) : base(whre, when) { };
						const std::string what() const noexcept override
						{
							return "Invalid user login or password";
						}
					};
					class bad_digest_response : virtual public Cout::Exceptions::base
					{
					public:
						bad_digest_response(const std::string& whre, const std::string& when) : base(whre, when) { };
						const std::string what() const noexcept override
						{
							return "Server returned a bad digest MD5 response";
						}
					};
				}
			}
		}
	}
}