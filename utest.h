#pragma once
#include "core/except.h"
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <exception>
#include <iomanip>

using ostream = std::ostream;

template <class T>
ostream & operator << (ostream & out, const std::set<T> s);

template<typename T>
ostream& operator << (ostream& out, const std::vector<T>& vec);

template <class K, class V>
ostream & operator << (ostream & out, const std::map<K, V> m);

template <class T, class U>
void Assert(const T & t, const U & u, const char* lable);

template <class T>
ostream & operator << (ostream & out, const std::set<T> s)
{
	out << "{ ";
	bool first = true;
	for (const auto & x : s)
	{
		if (!first)
		{
			out << ", ";
		}
		first = false;
		out << x;
	}
	return out << " }";
}

template<typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vec)
{
	bool isFirst = true;
	out << "{ ";
	for (const T& elem : vec)
	{
		if (!isFirst)
			out << ", ";

		out << elem;
	}
	return out << " }";
}

template <class K, class V>
ostream & operator << (ostream & out, const std::map<K, V> m)
{
	out << "{ ";
	bool first = true;
	for (const auto &[key, value] : m)
	{
		if (!first)
		{
			out << ", ";
		}
		first = false;
		out << key << ": " << value;
	}
	return out << " }";
}

void AssertBool(bool flag, const char* tested, const char* lable);

template<typename ExceptType, class Func, typename... Args>
void AssertException(const char* tested, const char* lable, const char* expected_except_msg, Func f, Args... args);

template<typename ExceptType, class Func, typename... Args>
void AssertException(const char* tested, const char* lable, const char* expected_except_msg, Func f, Args... args)
{
	bool flag = false;
	try
	{
		f(args...);
	}
	catch (const ExceptType& ex)
	{
		if (ex.when() == expected_except_msg)
		{
			flag = true;
		}
	}

	if (!flag)
	{
		std::ostringstream ss;
		ss << tested << ", exception expected when " << lable;
		throw Exception::CORE::logic_error(ss.str().c_str());
	}
}

template <class T, class U>
void Assert(const T & t, const U & u, const char* lable)
{
	if (t != u)
	{
		std::ostringstream out;
		out << lable << std::endl << "\t\t" << t << " != " << u;
		throw Exception::CORE::logic_error(out.str().c_str());
	}
}

class UTEST
{
public:
	~UTEST();
	template <class Func>
	void run(Func f, const char* test_name);
private:
	unsigned int count = 0;
	unsigned int success = 0;
};


template <class Func>
void UTEST::run(Func f, const char* tested_lable)
{
	count++;
	try
	{
		f();
		success++;
	}
	catch (const Exception::base& except)
	{
		std::cerr << std::endl;
		std::cerr << "\t while: " << tested_lable << std::endl;
		std::cerr << "\t what : " << except.what() << std::endl;
		// TODO: add stacktrace
		//std::cerr << "\t where: " << except.where() << std::endl; 
		std::cerr << "\t when : " << except.when() << std::endl;
	}
	catch (const std::exception & stdex)
	{
		std::cerr << std::endl;
		std::cerr << "\t while: " << tested_lable << std::endl;
		std::cerr << "\t what : " << stdex.what() << std::endl;
		//std::cerr << "\t where: unknown" << std::endl;
		std::cerr << "\t when : unknown" << std::endl;
	}
	catch (...)
	{
		std::cerr << std::endl;
		std::cerr << "\t while: " << tested_lable << std::endl;
		std::cerr << "\t what : unknown" << std::endl;
		//std::cerr << "\t where: unknown" << std::endl;
		std::cerr << "\t when : unknown" << std::endl;
	}
}
