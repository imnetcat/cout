#include "../config.h"
#ifdef INDEBUG
#include "profiler.h"

Cout::Core::Testing::Profiler::Profiler(Cout::Core::Logging::ILogger& logger, const std::string& msg) :
	message(msg),
	_logger(logger),
	_timer(new Timer(std::chrono::steady_clock::now())) {}

Cout::Core::Testing::Profiler::~Profiler() {
	std::string duration = std::to_string(_timer->end()) + " ms";
	_logger.Info(message + ": " + duration);
}

void Cout::Core::Testing::Timer::start()
{
	_start = std::chrono::steady_clock::now();
}

long long Cout::Core::Testing::Timer::end()
{
	auto finish = std::chrono::steady_clock::now();
	auto dur = finish - _start;

	return std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
}
#endif