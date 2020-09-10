#include "module_test.h"
#ifdef INDEBUG
using namespace std;
using namespace Cout::Core::Testing;

ModuleTest::ModuleTest(const vector<ITest*> ts) : _tests(ts) {}

void ModuleTest::run(Cout::Core::Logging::ILogger& logger, size_t& count, size_t& success) const
{
	for (const auto& test : _tests)
	{
		test->run(logger, count, success);
	}
}
#endif