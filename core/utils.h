#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_
#include <string>
#include <sstream>
#include "base64.h"
#include "md5.h"
namespace CORE
{
	class UTILS
	{
	public:
		static unsigned char* StringToUnsignedChar(const std::string& strIn);

		static std::string to_string(int x);
		static std::string to_string(unsigned int x);
		static std::string to_string(long x);
		static std::string to_string(unsigned long x);
		static std::string to_string(long long x);
		static std::string to_string(unsigned long long x);
		static std::string to_string(float x);
		static std::string to_string(double x);
		static std::string to_string(long double x);
		static std::string to_string(const char *x);
		static std::string to_string(const std::string &x);
		template<typename T> static std::string to_string(const T &t);
	};

	template<typename T> std::string UTILS::to_string(const T &t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}
}
#endif
