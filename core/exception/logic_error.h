#pragma once
#include "base.h"
namespace Exceptions
{
	namespace Core
	{
		class logic_error : public base
		{
		public:
			logic_error(const std::string when) : base(when) { }
			logic_error(const std::string when, const std::string where)
				: base(when, where) {};
			const char* what() const noexcept override
			{
				return "Logic error";
			}
		};
	}
}