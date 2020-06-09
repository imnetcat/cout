#include "utest.h"
using namespace std;

UTEST::~UTEST()
{
	if (fail > 0)
	{
		cerr << "\t=============== " << fail << "/" << success << " === Tests failed. Termanating. ===" << endl;
		exit(1);
	}
}
