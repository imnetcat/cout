#pragma once
#include "base.h"
namespace Exceptions
{
	namespace Core
	{
		class out_of_range : public base
		{
		public:
			out_of_range(const std::string whre, const std::string when)
				: base(whre, when) {};
			const std::string what() const noexcept override
			{
				return "Out of range";
			}
		};
	}
}