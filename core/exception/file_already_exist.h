#pragma once
#include "base.h"
namespace Exceptions
{
	namespace Core
	{
		class file_already_exist : public base
		{
		public:
			file_already_exist(const std::string whre, const std::string when)
				: base(whre, when) {};
			const std::string what() const noexcept override
			{
				return "File already exist";
			}
		};
	}
}