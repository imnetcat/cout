#include "debug_logger.h"
#ifdef INDEBUG
using namespace std;
using namespace Core;

Logging::Logger* Logging::DebugLogger::_logger = new  Logging::Logger([](const string& text) {cout << text << endl; });

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