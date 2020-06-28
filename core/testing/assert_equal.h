#pragma once
#include "../config.h"
#ifdef INDEBUG
#include "../exception.h"
#include "set_ostream.h"
#include "map_ostream.h"
#include "vec_ostream.h"
#include <iostream>
#include <utility>
namespace Core
{
	namespace Testing
	{
		template <class T, class U>
		std::pair<bool, std::string> AssertEqual(const T & t, const U & u)
		{
			std::pair<bool, std::string> pair(true, "");
			if (t != u)
			{
				std::ostringstream out;
				out << '"' << t << "\" != \"" << u << '"';
				pair = make_pair(false, out.str());
			}
			return pair;
		}
	}
}
#endif