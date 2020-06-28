#pragma once
#include "base.h"
namespace Core
{
	namespace Exception
	{
		class file_already_exist : public base
		{
		public:
			file_already_exist(const std::string when) : base(when) { };
			file_already_exist(const std::string when, const std::string where)
				: base(when, where) {};
			const char* what() const noexcept override
			{
				return "File already exist";
			}
		};
	}
}