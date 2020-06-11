#include "utest.h"
using namespace std;

UTEST::~UTEST()
{
	if (success != count)
	{
		cerr << endl;
		cerr << setw(25) << setfill('=') << " " << success << "/" << count << " "
			<< setw(18) << setfill('=') << " Termanating." << setw(20) << setfill('=') << ' ' << endl;
		exit(1);
	}
}

void AssertBool(bool flag, const char* tested, const char* lable)
{
	if (!flag)
	{
		ostringstream ss;
		ss << tested << " must be true when " << lable;
		throw CORE::Exception::logic_error(ss.str().c_str());
	}
}

void AssertException(const char* tested, const char* lable)
{
	ostringstream ss;
	ss << tested << ": exception expected when " << lable;
	throw CORE::Exception::logic_error(ss.str().c_str());
}
