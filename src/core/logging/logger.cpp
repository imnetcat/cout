#include "logger.h"
#include "warn.h"
#include "info.h"
#include "error.h"

Cout::Core::Logging::Logger::Logger(std::function<void(const std::string&)> c) :
		ILogger(c, new Logging::Info, new Logging::Warn, new Logging::Error) {}

