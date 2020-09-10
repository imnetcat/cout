#pragma once
#include <string>
namespace Core
{
	namespace Logging
	{
		struct log_line
		{
			log_line(const char* lable);
			log_line(const std::string& lable);
			const std::string Formating(const std::string&);
			const std::string lable;
		};
	}
}