#include "tester_logger.h"
#ifdef INDEBUG
using namespace std;
using namespace Core;

Logging::TesterLogger::TesterLogger() : Logger([](const string& text) { cerr << text << endl; }) {};

#endif