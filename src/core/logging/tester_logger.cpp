#include "tester_logger.h"
#include "tester_info.h"
#include "tester_warn.h"
#include "tester_error.h"
#ifdef INDEBUG
Cout::Core::Logging::TesterLogger::TesterLogger()
	: ILogger([](const std::string& text) { std::cerr << text << std::endl; }, 
		new TesterInfo, new TesterWarn, new TesterError) {};

#endif