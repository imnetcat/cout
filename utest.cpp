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
