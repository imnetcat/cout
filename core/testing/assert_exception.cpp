#include "../config.h"
#ifdef INDEBUG
#include "assert_exception.h"
bool Core::Testing::operator ==(const std::exception& lhs, const std::exception& rhs)
{
	return lhs.what() == rhs.what();
}
bool Core::Testing::operator ==(const Exceptions::base& lhs, const Exceptions::base& rhs)
{
	return lhs.what() == rhs.what() &&
		lhs.when() == rhs.when();
}
#endif