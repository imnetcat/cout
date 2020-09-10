#pragma once
#include <string>
#include <functional>

#include "../config.h"
#include "../utils.h"
#include "../exception/base.h"

#include "log.h"

namespace Cout
{
	namespace Core
	{
		namespace Logging
		{
			class ILogger
			{
			private:
				Log* _info;
				Log* _warn;
				Log* _err;
			public:
				ILogger(std::function<void(const std::string&)> c,
					Log* info_label,
					Log* warn_label,
					Log* err_label);

				void Info(const std::string& log);

				void Warning(const std::exception& ex);
				void Warning(const Cout::Exceptions::base&);

				void Error(const std::string& what, const std::string& where);
				void Error(const Cout::Exceptions::base&);
				void Error(const std::exception&);
				void Error(const Cout::Exceptions::base&, const std::string& what, const std::string& where);
			private:
				const std::function<void(const std::string&)> callback;
			};
		}
	}
}