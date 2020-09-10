#pragma once
#include "base.h"
namespace Exceptions
{
	namespace Core
	{
		class non_writable : public base
		{
		public:
			non_writable(const std::string whre, const std::string when)
				: base(whre, when) {};
			const std::string what() const noexcept override
			{
				return "Could not writable";
			}
		};
	}
}