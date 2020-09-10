#include "error.h"
#include <sstream>
using namespace std;
using namespace Core;

Logging::Error::Error(const std::string&pre_lable) : Log(pre_lable + "[ERROR]") { }
Logging::Error::Error() : Log("[ERROR]") { }

const std::string Logging::Error::log(const string& text)
{
	return Log::log("\n" + text);
}