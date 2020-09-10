#include "info.h"
using namespace std;
using namespace Core;

Logging::Info::Info(const std::string&pre_lable) : Log(pre_lable + "[INFO]") { }
Logging::Info::Info() : Log("[INFO]") { }
