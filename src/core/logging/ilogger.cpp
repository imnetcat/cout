#include "ilogger.h"
#include "../exception/undefined.h"

Cout::Core::Logging::ILogger::ILogger(std::function<void(const std::string&)> c,
	Log* info,
	Log* warn,
	Log* err) :
	_info(info),
	_warn(warn),
	_err(err),
	callback(c) {}

void Cout::Core::Logging::ILogger::Warning(const std::exception& ex)
{
	callback(_warn->log(Exceptions::Core::undefined(ex).log()));
}
void Cout::Core::Logging::ILogger::Warning(const Cout::Exceptions::base& ex)
{
	callback(_warn->log(ex.log()));
}

void Cout::Core::Logging::ILogger::Error(const std::string& what, const std::string& where)
{
	Error(Exceptions::Core::undefined(what, where));
}
void Cout::Core::Logging::ILogger::Error(const Cout::Exceptions::base& ex)
{
	callback(_err->log(ex.log()));
}
void Cout::Core::Logging::ILogger::Error(const std::exception& ex)
{
	callback(_err->log(Exceptions::Core::undefined(ex).log()));
}
void Cout::Core::Logging::ILogger::Error(const Cout::Exceptions::base& ex, const std::string& what, const std::string& where)
{
	callback(_err->log(ex.log(what, where)));
}

void Cout::Core::Logging::ILogger::Info(const std::string& log)
{
	callback(_info->log(log));
}
