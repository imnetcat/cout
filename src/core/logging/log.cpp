#include "log.h"
using namespace std;
using namespace Cout::Core;

Logging::Log::Log(const std::string& lable)
	: log_line(lable) {}

const std::string Logging::Log::log(const std::string& data)
{
	return Formating(data);
}
