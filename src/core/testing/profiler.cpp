#include "../config.h"
#ifdef INDEBUG
#include "profiler.h"
#include <iostream>
using namespace std;
using namespace std::chrono;
using namespace Cout::Core::Testing;

Profiler::Profiler(Cout::Core::Logging::ILogger& logger, const string& msg) :
	message(msg),
	_logger(logger),
	_timer(new Timer(steady_clock::now())) {}

Profiler::~Profiler() {
	string duration = std::to_string(_timer->end()) + " ms";
	_logger.Info(message + ": " + duration);
}

void Timer::start()
{
	_start = steady_clock::now();
}

long long Timer::end()
{
	auto finish = steady_clock::now();
	auto dur = finish - _start;

	return duration_cast<milliseconds>(dur).count();
}
#endif