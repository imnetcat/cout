#pragma once
#include "base.h"
namespace Core
{
	namespace Exception
	{
		class out_of_range : public base
		{
		public:
			out_of_range(const std::string when) : base(when) { };
			out_of_range(const std::string when, const std::string where)
				: base(when, where) {};
			const char* what() const noexcept override
			{
				return "Out of range";
			}
		};
	}
}