#include "logger.h"
#include "warn.h"
#include "info.h"
#include "error.h"
using namespace std;
using namespace Core;

Logging::Logger::Logger(function<void(const std::string&)> c) : 
		ILogger(c, new Logging::Info, new Logging::Warn, new Logging::Error) {}

