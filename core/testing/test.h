#pragma once
#include "../config.h"
#ifdef INDEBUG
#include "../logging/logger.h"
#include "assert.h"
#include <functional>
#include <utility>
namespace Core
{
	namespace Testing
	{
		struct ITest
		{
			virtual void run(const std::string& label, Logging::Logger& logger, size_t& count, size_t& success) const = 0;
		};
		
		struct unit_equal : ITest
		{
			unit_equal(const char* l, std::function<std::pair<bool, std::string>()> f) : _func(f), _label(l) {}
			void run(const std::string& label, Logging::Logger& logger, size_t& count, size_t& success) const override
			{
				count++;
				std::pair<bool, std::string> result(true, "");
				try
				{
					result = _func();
				}
				catch (const Core::Exception::base& except)
				{
					logger.Error(except, _label, label);
					return;
				}
				catch (const std::exception & stdex)
				{
					logger.Error(_label + "\n\t\t" + std::string(stdex.what()), label);
					return;
				}

				try
				{
					if (!result.first)
					{
						throw Core::Exception::logic_error(_label + "\n\t\t" + result.second, label);
					}
					success++;
				}
				catch (const Core::Exception::base& except)
				{
					logger.Error(except);
				}
				catch (const std::exception & stdex)
				{
					logger.Error(_label + "\n\t\t" + std::string(stdex.what()), label);
				}
			}
			const std::function<std::pair<bool, const std::string>()> _func;
			const std::string _label;
		};

		struct unit_bool : ITest
		{
			unit_bool(const char* l, std::function<bool()> f) : _func(f), _label(l) {}
			void run(const std::string& label, Logging::Logger& logger, size_t& count, size_t& success) const override
			{
				count++;
				bool result = true;
				try
				{
					bool result = _func();
				}
				catch (const Core::Exception::base& except)
				{
					logger.Error(except, _label, label);
					return;
				}
				catch (const std::exception & stdex)
				{
					logger.Error(_label + "\n\t\t" + std::string(stdex.what()), label);
					return;
				}

				try
				{
					if (!result)
					{
						throw Core::Exception::logic_error(_label, label);
					}
					success++;
				}
				catch (const Core::Exception::base& except)
				{
					logger.Error(except);
				}
				catch (const std::exception & stdex)
				{
					logger.Error(_label + "\n\t\t" + std::string(stdex.what()), label);
				}
			}
			const std::function<bool()> _func;
			const std::string _label;
		};

		template<typename T>
		struct unit_exception : ITest
		{
			unit_exception(const char* l, T e, std::function<void()> f) : expected(e), _func(f), _label(l) {}
			void run(const std::string& label, Logging::Logger& logger, size_t& count, size_t& success) const override
			{
				count++;
				bool result = true;
				try
				{
					result = AssertException(expected, _func);
				}
				catch (const Core::Exception::base& except)
				{
					logger.Error(except, _label, label);
					return;
				}
				catch (const std::exception & stdex)
				{
					logger.Error(_label + "\n\t\t" + std::string(stdex.what()), label);
					return;
				}

				try
				{
					if (!result)
					{
						throw Core::Exception::logic_error(_label  + " must throwing an exception", label);
					}
					success++;
				}
				catch (const Core::Exception::base& except)
				{
					logger.Error(except);
				}
				catch (const std::exception & stdex)
				{
					logger.Error(_label + "\n\t\t" + std::string(stdex.what()), label);
				}
			}
			T expected;
			const std::function<void()> _func;
			const std::string _label;
		};
	}
}
#endif