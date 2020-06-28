#include "log.h"
using namespace std;
using namespace Core;

Logging::Log::Log(const char* lable)
	: log_line(lable) {}

const std::string Logging::Log::log(const std::string& data)
{
	return Formating(data);
}
