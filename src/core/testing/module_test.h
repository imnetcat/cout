#pragma once
#include "../config.h"
#ifdef INDEBUG
#include "../logging/ilogger.h"
#include "test.h"
#include <memory>
namespace Cout
{
	namespace Core
	{
		namespace Testing
		{
			struct ModuleTest : public ITest
			{
			public:
				ModuleTest(const std::vector<ITest*> ts);

				void run(Logging::ILogger& logger, size_t& count, size_t& success) const override;
			private:
				std::vector<ITest*> _tests;
			};
		}
	}
}
#endif