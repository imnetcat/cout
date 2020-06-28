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
	Warning(Core::Exception::undefined(ex.what()));
}
void Logging::Logger::Warning(const Core::Exception::base& ex)
{
	callback(_warn->log(ex.log()));
}

void Logging::Logger::Error(const std::string& what, const std::string& where)
{
	Error(Core::Exception::undefined(what, where));
}
void Logging::Logger::Error(const Core::Exception::base& ex)
{
	callback(_err->log(ex.log()));
}
void Logging::Logger::Error(const Core::Exception::base& ex, const std::string& what, const std::string& where)
{
	callback(_err->log(ex.log(what, where)));
}

void Logging::Logger::Info(const string& log)
{
	callback(_info->log(log));
}
