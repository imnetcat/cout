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

Cout::Core::Testing::Tester::~Tester()
{
	if (success != count)
	{
		std::cerr << std::endl;
		std::cerr << std::setw(25) << std::setfill(' ') << " " << success << "/" << count << " "
			<< std::setw(16) << std::setfill(' ') << " Terminating." << std::endl;

		exit(1);
	}
	else
	{
		std::cerr << std::setw(30) << std::setfill(' ') << "Tests success. Good job!" << std::endl;
	}
}

void Cout::Core::Testing::Tester::run(const ITest& test)
{
	test.run(*_logger, count, success);
}

#endif