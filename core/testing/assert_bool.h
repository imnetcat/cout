#pragma once
#include "../config.h"
#ifdef INDEBUG
#include "../exception.h"
#include "assert_format.h"
#include <iostream>
#include <sstream>
namespace Core
{
	namespace Testing
	{

	}
}

#define ASSERT_BOOL(x)														\
{																			\
  if(!(x))														\
  {																			\
	throw Exceptions::Core::logic_error(ASSERT_FORMAT(#x, "true", "false"), WHERE);		\
  }																			\
}
#endif