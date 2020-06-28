#pragma once

#ifdef _DEBUG
#define INDEBUG
#endif

#ifdef INDEBUG
#define LOG_LEVEL_MIN 1
#define LOG_LEVEL_DEB 2
#define LOG_LEVEL_FULL 3
#define LOG_LEVEL LOG_LEVEL_FULL
#include <iostream>
#define DEBUG_LOG(log_level, log) if(log_level <= LOG_LEVEL) std::cout << "[DEGUB] " << log << std::endl;
#else
#define DEBUG_LOG(log_level, log)
#endif
