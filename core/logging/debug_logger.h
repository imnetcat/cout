#pragma once
#include "logger.h"
#include "../config.h"
#ifdef INDEBUG
#include <iostream>
namespace Core
{
	namespace Logging
	{
		class DebugLogger
		{
		private:
			static ILogger* _logger;

		public:
			static void Info(const std::string& log);

			static void Warning(const Exceptions::base&);

			static void Error(const Exceptions::base&);
		};
	}
}
#define DEBUG_LOG(log_level, log) if(log_level <= LOG_LEVEL) Core::Logging::DebugLogger::Info(log);
#define DEBUG_ERR(ex) Core::Logging::DebugLogger::Error(ex);
#else
#define DEBUG_LOG(log_level, log)
#define DEBUG_ERR(while_msg, what, when)
#endif
