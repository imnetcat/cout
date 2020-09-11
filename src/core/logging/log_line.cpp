#include "log_line.h"
#include "../utils.h"

Cout::Core::Logging::log_line::log_line(const char* l) :
	lable(l) { }

Cout::Core::Logging::log_line::log_line(const std::string& l) :
	lable(l) { }

const std::string Cout::Core::Logging::log_line::Formating(const std::string& data)
{
	return Utils::to_string(lable) + " " + data;
}