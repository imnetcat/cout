#pragma once
#include "base.h"
namespace Exceptions
{
	namespace Core
	{
		class access_denied : public base
		{
		public:
			access_denied(const std::string when) : base(when) { };
			access_denied(const std::string when, const std::string where) 
				: base(when, where) {};
			const char* what() const noexcept override
			{
				return "access denied or file is busy";
			}
		};
	}
}