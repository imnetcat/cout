#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifdef _DEBUG
#define INDEBUG
#endif

#ifdef INDEBUG
#define DEBUG_LEVEL_MIN 1
#define DEBUG_LEVEL_DEB 2
#define DEBUG_LEVEL_FULL 3
#define DEBUG_LEVEL DEBUG_LEVEL_FULL
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <windows.h>
#define DEBUG_LOG(log_level, log) if(log_level <= DEBUG_LEVEL) std::cout << "[DEGUB] " << log << std::endl;
#else
#define  DEBUG_LOG(log)
#endif

#endif
