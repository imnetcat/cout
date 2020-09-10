#include "info.h"
using namespace std;
using namespace Cout::Core;

Logging::Info::Info(const std::string&pre_lable) : Log(pre_lable + "[INFO]") { }
Logging::Info::Info() : Log("[INFO]") { }
