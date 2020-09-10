#pragma once
#include "../config.h"
#ifdef INDEBUG
#include "../exception.h"
#include "assert_format.h"
#include <iostream>
#include <sstream>
#define ASSERT_BOOL(x)														\
{																			\
  if(!(x))														\
  {																			\
	throw Cout::Exceptions::Core::logic_error(ASSERT_FORMAT(#x, "true", "false"), WHERE);		\
  }																			\
}
#endif