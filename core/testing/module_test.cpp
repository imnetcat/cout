#include "module_test.h"
#ifdef INDEBUG
using namespace std;
using namespace Core::Testing;

ModuleTest::ModuleTest(const char* m,
	const vector<ITest*> ts) :
	_label(m), _tests(ts) {}


void ModuleTest::run(const string& lable, Core::Logging::ILogger& logger, size_t& count, size_t& success) const
{
	for (const auto& test : _tests)
	{
		test->run(lable + "::" + _label, logger, count, success);
	}
}
#endif