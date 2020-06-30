#include "logger.h"
#include "../exception/undefined.h"
using namespace std;
using namespace Core;

Logging::Logger::Logger(function<void(const std::string&)> c) : 
	callback(c),
	_info(new Logging::Info),
	_warn(new Logging::Warn),
	_err(new Logging::Error) {}

void Logging::Logger::Warning(const std::exception& ex)
{
	Warning(Exceptions::Core::undefined(ex.what()));
}
void Logging::Logger::Warning(const Exceptions::base& ex)
{
	callback(_warn->log(ex.log()));
}

void Logging::Logger::Error(const std::string& what, const std::string& where)
{
	Error(Exceptions::Core::undefined(what, where));
}
void Logging::Logger::Error(const Exceptions::base& ex)
{
	callback(_err->log(ex.log()));
}
void Logging::Logger::Error(const Exceptions::base& ex, const std::string& what, const std::string& where)
{
	callback(_err->log(ex.log(what, where)));
}

void Logging::Logger::Info(const string& log)
{
	callback(_info->log(log));
}
