#pragma once
#include "log.h"
#include <string>
#include <functional>
namespace Core
{
	namespace Logging
	{
		class Error : private Log
		{
		public:
			Error();
			const std::string log(const std::string& text);
		};
	}
}