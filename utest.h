#pragma once

#include "core.h"

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
void Assert(const T & t, const U & u, const std::string & hint);

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

void AssertBool(bool flag, const std::string & why_goes_wrong);

void AssertException(const std::string & why_goes_wrong);

template <class T, class U>
void Assert(const T & t, const U & u, const std::string & when_goes_wrong)
{
	if (t != u)
	{
		std::ostringstream out;
		out << "\t when : " << when_goes_wrong << std::endl;
		out << "\t trace: " << t << " != " << u;
		throw CORE::Exception::logic_error(out.str());
	}
}

class UTEST
{
public:
	~UTEST();
	template <class Func>
	void run(Func f, const std::string & test_name);
private:
	unsigned int count = 0;
	unsigned int success = 0;
};


template <class Func>
void UTEST::run(Func f, const std::string & what_goes_wrong)
{
	count++;
	try
	{
		try
		{
			f();
			success++;
		}
		catch (std::exception & ex)
		{
			throw CORE::Exception::undefined(ex.what());
		}
		catch (...)
		{
			throw CORE::Exception::undefined("unknown");
		}
	}
	catch (const CORE::Exception::base& except)
	{
		std::cerr << "\t\t Assertion failed: " << std::endl;
		std::cerr << "\t what : " << what_goes_wrong << std::endl;
		std::cerr << "\t what : " << except.what() << std::endl;
		std::cerr << "\t when : " << except.when() << std::endl;
	}
}
