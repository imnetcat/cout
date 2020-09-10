#pragma once
#include "base.h"
namespace Exceptions
{
	namespace Core
	{
		class undefined : public base
		{
		public:
			undefined(const std::exception& ex) : base(ex) { };
			undefined(const std::string whre, const std::string when)
				: base(whre, when) {};
			const std::string what() const noexcept override
			{
				return "Undefined error";
			}
		};
	}
}