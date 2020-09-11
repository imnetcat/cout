#include "log.h"
Cout::Core::Logging::Log::Log(const std::string& lable)
	: log_line(lable) {}

const std::string Cout::Core::Logging::Log::log(const std::string& data)
{
	return Formating(data);
}
