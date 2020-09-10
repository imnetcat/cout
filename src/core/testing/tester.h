#pragma once
#include "../config.h"
#ifdef INDEBUG
#include "../logging/tester_logger.h"
#include "test.h"
#include "module_test.h"
namespace Cout
{
	namespace Core
	{
		namespace Testing
		{
			struct ITester
			{
			public:
				virtual void run(const ITest&) = 0;
			};

			class Tester : public ITester
			{
			public:
				Tester() : _logger(new Logging::TesterLogger()) {}
				~Tester();
				void run(const ITest& f) override;
			private:
				Logging::TesterLogger* _logger;
				size_t count = 0;
				size_t success = 0;
			};
		}
	}
}
#endif