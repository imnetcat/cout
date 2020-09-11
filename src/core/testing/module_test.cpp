#include "module_test.h"
#ifdef INDEBUG

Cout::Core::Testing::ModuleTest::ModuleTest(const std::vector<ITest*> ts) : _tests(ts) {}

void Cout::Core::Testing::ModuleTest::run(Cout::Core::Logging::ILogger& logger, size_t& count, size_t& success) const
{
	for (const auto& test : _tests)
	{
		test->run(logger, count, success);
	}
}
#endif