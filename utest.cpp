#include "utest.h"
using namespace std;

UTEST::~UTEST()
{
	if (success != count)
	{
		cerr << setw(25) << setfill('=') << " " << success << "/" << count << " "
			<< setw(18) << setfill('=') << " Termanating." << setw(20) << setfill('=') << ' ' << endl;
		exit(1);
	}
}

void AssertBool(bool flag, const std::string & when_goes_wrong)
{
	if (!flag)
	{
		throw CORE::Exception::logic_error(when_goes_wrong + ": must be true");
	}
}

void AssertException(const std::string & when_goes_wrong)
{
	throw CORE::Exception::logic_error(when_goes_wrong + ": exception expected");
}