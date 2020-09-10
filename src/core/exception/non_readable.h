#pragma once
#include "base.h"
namespace Cout
{
	namespace Exceptions
	{
		namespace Core
		{
			class non_readable : public base
			{
			public:
				non_readable(const std::string whre, const std::string when)
					: base(whre, when) {};
				const std::string what() const noexcept override
				{
					return "Could not readable";
				}
			};
		}
	}
}