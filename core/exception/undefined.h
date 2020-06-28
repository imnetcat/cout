#pragma once
#include "base.h"
namespace Core
{
	namespace Exception
	{
		class undefined : public base
		{
		public:
			undefined(const std::exception& ex) : base(ex) { };
			undefined(const std::string when) : base(when) { };
			undefined(const std::string when, const std::string where)
				: base(when, where) {};
			const char* what() const noexcept override
			{
				return "Undefined error";
			}
		};
	}
}