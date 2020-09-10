#include "warn.h"
#include <sstream>
using namespace std;
using namespace Cout::Core;

Logging::Warn::Warn(const std::string&pre_lable) : Log(pre_lable + "[WARN]") { }
Logging::Warn::Warn() : Log("[WARN]") { }

const std::string Logging::Warn::log(const string& text)
{
	return Log::log("\n" + text);
}
