#pragma once
#include "base.h"
namespace Core
{
	namespace Exception
	{
		class non_writable : public base
		{
		public:
			non_writable(const std::string when) : base(when) { };
			non_writable(const std::string when, const std::string where)
				: base(when, where) {};
			const char* what() const noexcept override
			{
				return "Could not writable";
			}
		};
	}
}