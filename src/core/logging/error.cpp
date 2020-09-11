#include "error.h"
Cout::Core::Logging::Error::Error(const std::string&pre_lable) : Log(pre_lable + "[ERROR]") { }
Cout::Core::Logging::Error::Error() : Log("[ERROR]") { }

const std::string Cout::Core::Logging::Error::log(const std::string& text)
{
	return Log::log("\n" + text);
}