#pragma once
#include "../config.h"
#ifdef INDEBUG
#include "../logging/logger.h"
#include "test.h"
#include "module_test.h"
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
			Tester(Core::Logging::Logger& l) : logger(l) {}
			~Tester();
			void run(const ITest& f) override;
		private:
			Core::Logging::Logger& logger;
			size_t count = 0;
			size_t success = 0;
		};
	}
}
#endif