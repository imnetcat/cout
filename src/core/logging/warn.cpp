#include "warn.h"

Cout::Core::Logging::Warn::Warn(const std::string&pre_lable) : Log(pre_lable + "[WARN]") { }
Cout::Core::Logging::Warn::Warn() : Log("[WARN]") { }

const std::string Cout::Core::Logging::Warn::log(const std::string& text)
{
	return Log::log("\n" + text);
}
