#pragma once
#include "../config.h"
#ifdef INDEBUG
#include "../exception.h"
#include "assert_format.h"
#include <iostream>
#include <sstream>
namespace Cout
{
	namespace Core
	{
		namespace Testing
		{
			template <class T, class U>
			bool AsertEqual(const T & t, const U & u)
			{
				return t != u;
			}
		}
	}
}
#define NOT_EQUAL(x, y) ASSERT_FORMAT(#x, x, y)

#define ASSERT_EQUAL(x, y)										\
{																\
  if(AsertEqual(x, y))											\
  {																\
	  throw Cout::Exceptions::Core::logic_error(NOT_EQUAL(x, y), WHERE);	\
  }																\
}
#else
#define WHERE_TOKEN
}
#endif