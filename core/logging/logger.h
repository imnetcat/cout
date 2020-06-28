#pragma once
#include <string>
#include <functional>

#include "../config.h"
#include "../utils.h"
#include "../exception/base.h"

#include "info.h"
#include "warn.h"
#include "error.h"

#ifdef INDEBUG
#include <iostream>
#define DEBUG_LOG(log_level, log) if(log_level <= LOG_LEVEL) std::cout << \
		"[DEGUB] " << log << std::endl;
#define DEBUG_ERR(while_msg, what, when) std::cerr << \
		"[ERROR] " << std::endl << \
		"\t while: " << while_msg << std::endl << \
		"\t what : " << what << std::endl << \
		"\t when : " << when << std::endl;
#else
#define DEBUG_LOG(log_level, log)
#define DEBUG_ERR(while_msg, what, when)
#endif

namespace Core
{
	namespace Logging
	{
		class Logger
		{
		private:
			Info* _info;
			Warn* _warn;
			Error* _err;
			const std::function<void(const std::string&)> callback;
		public:
			Logger(std::function<void(const std::string&)> c);

			void Info(const std::string& log);

			void Warning(const std::exception& ex);
			void Warning(const Exceptions::base&);

			void Error(const std::string& what, const std::string& where);
			void Error(const Exceptions::base&);
			void Error(const Exceptions::base&, const std::string& what, const std::string& where);
		};
	}
}