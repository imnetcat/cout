#pragma once
#include "base.h"
namespace Core
{
	namespace Exception
	{
		class invalid_argument : public base
		{
		public:
			invalid_argument(const std::string when) : base(when) { };
			invalid_argument(const std::string when, const std::string where)
				: base(when, where) {};
			const char* what() const noexcept override
			{
				return "Invalid argument or variable not specified";
			}
		};
	}
}