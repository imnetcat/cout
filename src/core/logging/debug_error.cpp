#include "debug_error.h"
#include <sstream>
using namespace std;
using namespace Cout::Core;

Logging::DebugError::DebugError() : Error("[DEBUG]") { }