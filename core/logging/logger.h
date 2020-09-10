#pragma once
#include <string>
#include <functional>

#include "../config.h"
#include "../utils.h"
#include "../exception/base.h"

#include "ilogger.h"
namespace Core
{
	namespace Logging
	{
		class Logger : public ILogger
		{
		public:
			Logger(std::function<void(const std::string&)> c);
		};
	}
}