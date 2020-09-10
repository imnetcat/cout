#pragma once
#include "../config.h"
#ifdef INDEBUG
#include <string>
#include <sstream>
#include "set_ostream.h"
#include "map_ostream.h"
#include "vec_ostream.h"
namespace Cout
{
	namespace Core
	{
		namespace Testing
		{
			template<class T, class U>
			std::string ASSERT_FORMAT(const std::string& where, const T& gotit, const U& expected)
			{
				std::ostringstream out;
				out << where << std::endl << "\texpctd: " << std::endl << "\t\t" << expected << std::endl << "\tgotit  : " << std::endl << "\t\t" << gotit << std::endl;
				return out.str();
			}
		}
	}
}
#endif