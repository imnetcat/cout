#pragma once
#include "../config.h"
#ifdef INDEBUG
#include "../logging/ilogger.h"
#include "assert.h"
#include "profiler.h"
#include "../exception/logic_error.h"
#include <functional>
#include <utility>
namespace Core
{
	namespace Testing
	{
		struct ITest
		{
			virtual void run(Logging::ILogger& logger, size_t& count, size_t& success) const = 0;
		};
		
		struct UnitTest : ITest
		{
			UnitTest(std::function<void()> f) : _func(f) {}
			void run(Logging::ILogger& logger, size_t& count, size_t& success) const override
			{
				count++;
				try
				{
					_func();
					success++;
				}
				catch (const Exceptions::base& except)
				{
					logger.Error(except);
					return;
				}
				catch (const std::exception & stdex)
				{
					logger.Error(stdex);
					return;
				}
			}
			const std::function<void()> _func;
		};

		struct TimeTest : ITest
		{
			TimeTest(std::function<void(Logging::ILogger& logger)> f) : _func(f) {}
			void run(Logging::ILogger& logger, size_t& count, size_t& success) const override
			{
				count++;
				try
				{
					_func(logger);
					success++;
				}
				catch (const Exceptions::base& except)
				{
					logger.Error(except);
					return;
				}
				/*catch (std::exception & stdex)
				{
					logger.Error(stdex);
					return;
				}
				*/
			}
			const std::function<void(Logging::ILogger& logger)> _func;
		};
	}
}
#endif