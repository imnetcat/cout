#include "log_line.h"
#include "../utils.h"
using namespace std;
using namespace Core;

Logging::log_line::log_line(const char* l) :
	lable(l),
	separator_left("["),
	separator_right("] ") { }

const string Logging::log_line::Formating(const std::string& data)
{
	return Utils::to_string(separator_left) 
		+ Utils::to_string(lable)
		+ Utils::to_string(separator_right)
		+ data;
}