#include "log_line.h"
#include "../utils.h"
using namespace std;
using namespace Cout::Core;

Logging::log_line::log_line(const char* l) :
	lable(l) { }

Logging::log_line::log_line(const std::string& l) :
	lable(l) { }

const string Logging::log_line::Formating(const std::string& data)
{
	return Utils::to_string(lable) + " " + data;
}