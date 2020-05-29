#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_
#include <string>
#include "base64.h"
#include "md5.h"

class UTILS
{
public:
	static unsigned char* StringToUnsignedChar(std::string strIn);

	static string to_string(int x);
	static string to_string(unsigned int x);
	static string to_string(long x);
	static string to_string(unsigned long x);
	static string to_string(long long x);
	static string to_string(unsigned long long x);
	static string to_string(float x);
	static string to_string(double x);
	static string to_string(long double x);
	static string to_string(const char *x);
	static string to_string(const string &x);
	template<typename T> static string to_string(const T &t);
};

template<typename T> string UTILS::to_string(const T &t)
{
	stringstream ss;
	ss << t;
	return ss.str();
}
#endif
