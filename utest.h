#pragma once

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <exception>

using ostream = std::ostream;

template <class T>
ostream & operator << (ostream & out, const std::set<T> s);

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

template <class T, class U>
void Assert(const T & t, const U & u, const std::string & hint)
{
	if (t != u)
	{
		std::ostringstream out;
		std::cerr << " Assertion failed: " << t << " != " << u << std::endl;
		std::cerr << " trace: " << hint << std::endl;
		throw CORE::std::runtime_error(out.str());
	}
}

class UTEST
{
public:
	~UTEST();
	template <class Func>
	void run(Func f, const std::string & test_name);
private:
	int fail_count = 0;
};


template <class Func>
void UTEST::run(Func f, const std::string & test_name)
{
	try
	{
		std::cerr << test_name << std::endl;
		f();
		std::cerr << "OK" << std::endl;
	}
	catch (std::exception & ex)
	{
		std::cerr << ex.what();
		fail_count++;
	}
}
