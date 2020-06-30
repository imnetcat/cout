#include "ilogger.h"
#include "../exception/undefined.h"
using namespace std;
using namespace Core;

Logging::ILogger::ILogger(std::function<void(const std::string&)> c,
	Log* info,
	Log* warn,
	Log* err) :
	_info(info),
	_warn(warn),
	_err(err),
	callback(c) {}

void Logging::ILogger::Warning(const std::exception& ex)
{
	Warning(Exceptions::Core::undefined(ex.what()));
}
void Logging::ILogger::Warning(const Exceptions::base& ex)
{
	callback(_warn->log(ex.log()));
}

void Logging::ILogger::Error(const std::string& what, const std::string& where)
{
	Error(Exceptions::Core::undefined(what, where));
}
void Logging::ILogger::Error(const Exceptions::base& ex)
{
	callback(_err->log(ex.log()));
}
void Logging::ILogger::Error(const Exceptions::base& ex, const std::string& what, const std::string& where)
{
	callback(_err->log(ex.log(what, where)));
}

void Logging::ILogger::Info(const string& log)
{
	callback(_info->log(log));
}
