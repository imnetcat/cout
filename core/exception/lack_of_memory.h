#pragma once
#include "base.h"
namespace Exceptions
{
	namespace Core
	{
		class lack_of_memory : public base
		{
		public:
			lack_of_memory(const std::string when) : base(when) { };
			lack_of_memory(const std::string when, const std::string where)
				: base(when, where) {};
			const char* what() const noexcept override
			{
				return "Lack of memory";
			}
		};
	}
}