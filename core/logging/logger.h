#pragma once
#include <string>
#include <functional>

#include "../config.h"
#include "../utils.h"
#include "../exception/base.h"

#include "info.h"
#include "warn.h"
#include "error.h"

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
		public:
			Logger(std::function<void(const std::string&)> c);

			void Info(const std::string& log);

			void Warning(const std::exception& ex);
			void Warning(const Exceptions::base&);

			void Error(const std::string& what, const std::string& where);
			void Error(const Exceptions::base&);
			void Error(const Exceptions::base&, const std::string& what, const std::string& where);
		private:
			const std::function<void(const std::string&)> callback;
		};
	}
}