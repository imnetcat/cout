#pragma once
#include "base.h"
namespace Exceptions
{
	namespace Core
	{
		class access_denied : public base
		{
		public:
			access_denied(const std::string whre, const std::string when)
				: base(whre, when) {};
			const std::string what() const noexcept override
			{
				return "access denied or file is busy";
			}
		};
	}
}