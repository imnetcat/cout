#pragma once
#include "base.h"
namespace Cout
{
	namespace Exceptions
	{
		namespace Core
		{
			class logic_error : public base
			{
			public:
				logic_error(const std::string whre, const std::string when)
					: base(whre, when) {};
				const std::string what() const noexcept override
				{
					return "Logic error";
				}
			};
		}
	}
}