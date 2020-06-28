#pragma once
#include "base.h"
namespace Core
{
	namespace Exception
	{
		class non_readable : public base
		{
		public:
			non_readable(const std::string when) : base(when) { };
			non_readable(const std::string when, const std::string where)
				: base(when, where) {};
			const char* what() const noexcept override
			{
				return "Could not readable";
			}
		};
	}
}