#pragma once
#include <string>
namespace Core
{
	namespace Logging
	{
		struct log_line
		{
			log_line(const char* lable);
			const std::string Formating(const std::string&);
			const char* lable;
			const char* separator_left;
			const char* separator_right;
		};
	}
}