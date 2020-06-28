#pragma once
#include <string>
#include <sstream>
namespace Core
{
	namespace Utils
	{
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
		template<typename T>
		std::string to_string(const T &t);
		
		// correct only for ASCII symbols
		static unsigned char* StringToUnsignedChar(const std::string& strIn);
	};

	unsigned char* Utils::StringToUnsignedChar(const std::string& strIn)
	{
		size_t length = strIn.size();
		unsigned char * temp = new unsigned char[length];

		for (int i = 0; i < length; ++i)
		{
			temp[i] = static_cast<unsigned char>(strIn[i]);
		}

		return temp;
	}

	template<typename T>
	std::string Utils::to_string(const T &t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}

	std::string Utils::to_string(int x)
	{
		return std::to_string(x);
	}
	std::string Utils::to_string(unsigned int x)
	{
		return std::to_string(x);
	}
	std::string Utils::to_string(long x)
	{
		return std::to_string(x);
	}
	std::string Utils::to_string(unsigned long x)
	{
		return std::to_string(x);
	}
	std::string Utils::to_string(long long x)
	{
		return std::to_string(x);
	}
	std::string Utils::to_string(unsigned long long x)
	{
		return std::to_string(x);
	}
	std::string Utils::to_string(float x)
	{
		return std::to_string(x);
	}
	std::string Utils::to_string(double x)
	{
		return std::to_string(x);
	}
	std::string Utils::to_string(long double x)
	{
		return std::to_string(x);
	}
	std::string Utils::to_string(const char *x)
	{
		return std::string(x);
	}
	std::string Utils::to_string(const std::string& x)
	{
		return x;
	}

}