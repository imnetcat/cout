#pragma once
#include "log_line.h"
#include <string>
#include <functional>
namespace Core
{
	namespace Logging
	{
		class Log : private log_line
		{
		public:
			Log(const char* lable);
			const std::string log(const std::string& data);
		};
	}
}