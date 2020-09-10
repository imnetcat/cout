#pragma once
#include <string>
#include <sstream>
#include <algorithm>
namespace Cout
{
	namespace Core
	{
		namespace Utils
		{
			// Стирает \0 в конце введёной строки, если есть
			static void rtrim_null(std::string& str);

			static void replace(std::string & str, const std::string & substring, const std::string & rstr);

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

		void Utils::rtrim_null(std::string& str) {
			str.erase(std::find_if(str.rbegin(), str.rend(), [](int character) {
				return '\0' != character;
			}).base(), str.end());
		}

		void Utils::replace(std::string & str, const std::string & substring, const std::string & rstr)
		{
			size_t pos = 0;
			while ((pos = str.find(substring, pos + rstr.size())) != std::string::npos)
			{
				str.replace(pos, rstr.size(), rstr);
			}
		}

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
}