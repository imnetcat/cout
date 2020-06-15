#include "exception_base.h"
using namespace std;

Exception::base::base(const char* w) : msg_when(w) { };
Exception::base::base(const string& w) : msg_when(w) { };

const string& Exception::base::when() const noexcept
{
	return msg_when;
}
