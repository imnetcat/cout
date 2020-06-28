#pragma once
#include "../config.h"
#ifdef INDEBUG
#include "../logging/logger.h"
#include "test.h"
#include <memory>
namespace Core
{
	namespace Testing
	{
		struct ModuleTest : public ITest
		{
		public:
			ModuleTest(const char* m,
				const std::vector<ITest*> ts);

			void run(const std::string& label, Logging::Logger& logger, size_t& count, size_t& success) const override;
		private:
			const std::string _label;
			std::vector<ITest*> _tests;
		};
	}
}
#endif