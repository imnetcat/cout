#include "error.h"
#include <sstream>
using namespace std;
using namespace Core;

Logging::Error::Error() : Log("ERROR") { }

const std::string Logging::Error::log(const string& text)
{
	return Log::log("\n" + text);
}