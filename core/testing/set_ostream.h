#pragma once
#include "../config.h"
#ifdef INDEBUG
#include <iostream>
#include <set>
namespace Core
{
	namespace Testing
	{
		template <class T>
		std::ostream & operator << (std::ostream & out, const std::set<T> s)
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
	}
}
#endif