﻿#include "src/core/testing/tester.h"
#include "test/all.h"
using namespace std;

int main()
{
#ifdef INDEBUG	
	{
		Core::Testing::Tester tester;
		tester.run(UnitTests);
	}
#endif

	return 0;
}
