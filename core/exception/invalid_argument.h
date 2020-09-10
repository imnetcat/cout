#pragma once
#include "base.h"
namespace Exceptions
{
	namespace Core
	{
		class invalid_argument : public base
		{
		public:
			invalid_argument(const std::string whre, const std::string when)
				: base(whre, when) {};
			const std::string what() const noexcept override
			{
				return "Invalid argument or variable not specified";
			}
		};
	}
}