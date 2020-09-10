#pragma once
#include "../config.h"
#ifdef INDEBUG
#include <iostream>
#include <map>
template <class K, class V>
std::ostream & operator << (std::ostream & out, const std::map<K, V> m)
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
#endif