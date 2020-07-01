#pragma once
#include "../../core/exception/base.h"
namespace Exceptions
{
	namespace Auth
	{
		class bad_credentials : virtual public base
		{
		public:
			bad_credentials(const char* when) : base(when) { };
			bad_credentials(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "Invalid user login or password";
			}
		};
		class bad_digest_response : virtual public base
		{
		public:
			bad_digest_response(const char* when) : base(when) { };
			bad_digest_response(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "Server returned a bad digest MD5 response";
			}
		};
	}
}
