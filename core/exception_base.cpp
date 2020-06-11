#include "exception_base.h"
using namespace std;

CORE::Exception::base::base(const char* w) : msg_when(w) { };
CORE::Exception::base::base(const string& w) : msg_when(w) { };

const string& CORE::Exception::base::when() const noexcept
{
	return msg_when;
}
