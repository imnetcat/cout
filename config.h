#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifdef _DEBUG
#define INDEBUG
#endif

#ifdef INDEBUG
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <windows.h>
#define DEBUG_LOG(log) cout << "[DEGUB] " << log << endl;
#else
#define  DEBUG_LOG(log)
#endif

#define USE_GMAIL 1
#define EMAIL_TYPE USE_GMAIL
#define EMAIL_SENDER_USERNAME ""
#define EMAIL_SENDER_PASSWORD ""
#define EMAIL_RECEIVER_USERNAME ""
#define EMAIL_SENDER_USERNAME "hey.vasap@gmail.com"
#define EMAIL_SENDER_PASSWORD "6275924Y"
#define EMAIL_RECEIVER_USERNAME "crazyhero019@gmail.com"

#endif
