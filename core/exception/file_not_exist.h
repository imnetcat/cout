#pragma once
#include "base.h"
namespace Core
{
	namespace Exception
	{
		class file_not_exist : public base
		{
		public:
			file_not_exist(const std::string when) : base(when) { };
			file_not_exist(const std::string when, const std::string where)
				: base(when, where) {};
			const char* what() const noexcept override
			{
				return "File not exist";
			}
		};
	}
}