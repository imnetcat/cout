#pragma once
#include "../config.h"
#ifdef INDEBUG
#include <chrono>
#include <string>
#include "../logging/ilogger.h"
#include "../logging/debug_logger.h"
#include "../logging/tester_logger.h"
namespace Cout
{
	namespace Core
	{
		namespace Testing
		{
			class Timer {
			public:
				Timer() {};
				Timer(std::chrono::steady_clock::time_point start) : _start(start) {};
				void start();
				long long end();
			private:
				std::chrono::steady_clock::time_point _start;
			};

			class Profiler {
			public:
				explicit Profiler(Logging::ILogger& logger, const std::string& msg = "");

				~Profiler();
			private:
				Timer* _timer;
				Logging::ILogger& _logger;
				std::string message;
			};
		}
	}
}
#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define DURATION_OF(logger, func) \
{\
	Core::Testing::Profiler UNIQ_ID(__LINE__){logger, #func}; \
	func; \
}
#define TEST_DURATION_OF(func) \
{\
	Core::Logging::TesterLogger ____LoGeerr___;\
	Core::Testing::Profiler UNIQ_ID(__LINE__){ ____LoGeerr___, #func}; \
	func; \
}

#define DURATION(message, logger) \
	Core::Testing::Profiler UNIQ_ID(__LINE__){logger, message};

#define TEST_DURATION(message) \
{\
	Core::Logging::TesterLogger ____LoGeerr___;\
	DURATION(message, ____LoGeerr___);\
}
#endif