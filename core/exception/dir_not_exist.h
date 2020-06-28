#pragma once
#include "base.h"
namespace Exceptions
{
	namespace Core
	{
		class dir_not_exist : public base
		{
		public:
			dir_not_exist(const std::string when) : base(when) { };
			dir_not_exist(const std::string when, const std::string where)
				: base(when, where) {};
			const char* what() const noexcept override
			{
				return "Directory not exist";
			}
		};
	}
}