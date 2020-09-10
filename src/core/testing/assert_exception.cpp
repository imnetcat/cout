#include "../config.h"
#ifdef INDEBUG
#include "assert_exception.h"
bool Cout::Core::Testing::operator ==(const std::exception& lhs, const std::exception& rhs)
{
	return lhs.what() == rhs.what();
}
bool Cout::Core::Testing::operator ==(const Cout::Exceptions::base& lhs, const Cout::Exceptions::base& rhs)
{
	return lhs.what() == rhs.what() &&
		lhs.when() == rhs.when();
}
#endif