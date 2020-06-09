#include "utest.h"
using namespace std;

UTEST::~UTEST()
{
	if (fail_count > 0)
	{
		cerr << fail_count << " Tests failed. Termanated." << endl;
		exit(1);
	}
}

void Assert(bool t, const std::string & hint)
{
	if (!t)
	{
		std::ostringstream out;
		std::cerr << " Assertion failed: " << hint << std::endl;
		throw std::runtime_error(out.str());
	}
}