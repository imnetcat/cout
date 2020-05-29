#include "utils.h"

unsigned char* UTILS::StringToUnsignedChar(string strIn)
{
	int length = strIn.size();
	unsigned char * temp = new unsigned char[length];

	for (int i = 0; i < length; ++i)
	{
		temp[i] = static_cast<unsigned char>(strIn[i]);
	}

	return temp;
}

std::string UTILS::to_string(int x)
{
	return std::to_string(x);
}
std::string UTILS::to_string(unsigned int x)
{
	return std::to_string(x);
}
std::string UTILS::to_string(long x)
{
	return std::to_string(x);
}
std::string UTILS::to_string(unsigned long x)
{
	return std::to_string(x);
}
std::string UTILS::to_string(long long x)
{
	return std::to_string(x);
}
std::string UTILS::to_string(unsigned long long x)
{
	return std::to_string(x);
}
std::string UTILS::to_string(float x)
{
	return std::to_string(x);
}
std::string UTILS::to_string(double x)
{
	return std::to_string(x);
}
std::string UTILS::to_string(long double x)
{
	return std::to_string(x);
}
std::string UTILS::to_string(const char *x)
{
	return std::string(x);
}
std::string UTILS::to_string(const std::string &x)
{
	return x;
}

template<typename T> std::string UTILS::to_string(const T &t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}
