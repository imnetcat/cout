#include "tester_logger.h"
#include "tester_info.h"
#include "tester_warn.h"
#include "tester_error.h"
#ifdef INDEBUG
using namespace std;
using namespace Core;

Logging::TesterLogger::TesterLogger() 
	: ILogger([](const string& text) { cerr << text << endl; }, 
		new TesterInfo, new TesterWarn, new TesterError) {};

#endif