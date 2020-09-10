#pragma once
#include "base.h"
namespace Exceptions
{
	namespace Core
	{
		class lack_of_memory : public base
		{
		public:
			lack_of_memory(const std::string whre, const std::string when)
				: base(whre, when) {};
			const std::string what() const noexcept override
			{
				return "Lack of memory";
			}
		};
	}
}