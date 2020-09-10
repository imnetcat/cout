#include "debug_logger.h"
#include "debug_error.h"
#include "debug_info.h"
#include "debug_warn.h"
#ifdef INDEBUG
using namespace std;
using namespace Core;

Logging::ILogger* Logging::DebugLogger::_logger = new Logging::ILogger([](const string& text) {cout << text << endl; }, new DebugInfo, new DebugWarn, new DebugError);

void Logging::DebugLogger::Info(const std::string& log)
{
	_logger->Info(log);
}

void Logging::DebugLogger::Warning(const Exceptions::base& ex)
{
	_logger->Warning(ex);
}

void Logging::DebugLogger::Error(const Exceptions::base& ex)
{
	_logger->Error(ex);
}
#endif