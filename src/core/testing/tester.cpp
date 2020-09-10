#include "tester.h"
#ifdef INDEBUG
#include "../exception/base.h"
#include "../config.h"
#include "../exception.h"
#include "../logging/logger.h"
#include "set_ostream.h"
#include "map_ostream.h"
#include "vec_ostream.h"
#include <iostream>
#include <exception>
#include <iomanip>
using namespace std;
using namespace Core::Testing;

Tester::~Tester()
{
	if (success != count)
	{
		cerr << endl;
		cerr << setw(25) << setfill(' ') << " " << success << "/" << count << " "
			<< setw(16) << setfill(' ') << " Terminating." << endl;

		exit(1);
	}
	else
	{
		cerr << setw(30) << setfill(' ') << "Tests success. Good job!" << endl;
	}
}

void Tester::run(const ITest& test)
{
	test.run(*_logger, count, success);
}

#endif