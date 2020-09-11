#include "debug_logger.h"
#include "debug_error.h"
#include "debug_info.h"
#include "debug_warn.h"
#ifdef INDEBUG
Cout::Core::Logging::ILogger* Cout::Core::Logging::DebugLogger::_logger = new Cout::Core::Logging::ILogger(
	[](const std::string& text) {
	std::cout << text << std::endl; 
}, new DebugInfo, new DebugWarn, new DebugError);

void Cout::Core::Logging::DebugLogger::Info(const std::string& log)
{
	_logger->Info(log);
}

void Cout::Core::Logging::DebugLogger::Warning(const Cout::Exceptions::base& ex)
{
	_logger->Warning(ex);
}

void Cout::Core::Logging::DebugLogger::Error(const Cout::Exceptions::base& ex)
{
	_logger->Error(ex);
}
#endif