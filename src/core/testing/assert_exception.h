#pragma once
#include "../config.h"
#ifdef INDEBUG
#include "../exception.h"
#include "assert_format.h"
#include <iostream>
#include <sstream>
#include <exception>
#include <functional>
namespace Core
{
	namespace Testing
	{
		bool operator ==(const std::exception& lhs, const std::exception& rhs);
		bool operator ==(const Exceptions::base& lhs, const Exceptions::base& rhs);

		template<typename ExceptType, class Func, typename... Args>
		bool AssertException(ExceptType expected, Func f, Args... args)
		{
			bool flag = false;
			try
			{
				f(args...);
			}
			catch (const ExceptType except)
			{
				if (except == expected)
					flag = true;
			}
			catch(...) { }

			return flag;
		}

		template<typename ExceptType>
		bool AssertException(ExceptType expected_except, std::function<void()> f)
		{
			bool flag = false;
			try
			{
				f();
			}
			catch (const ExceptType except)
			{
				if(except == expected_except)
					flag = true;
			}
			catch (...) {}

			return flag;
		}
	}
}
#define EXCPT_EXP(except) except " exception must have been throwed"
#define ASSERT_EXCEPTION(expected_except, func)										\
{																					\
	{																				\
		bool flag = false;															\
		try																			\
		{																			\
			func;																	\
		}																			\
		catch (const expected_except&)								\
		{																			\
			flag = true;														\
		}																			\
		catch (...) {}																\
																					\
		if (!flag)																	\
		{																			\
			throw Exceptions::Core::logic_error(ASSERT_FORMAT(#func, EXCPT_EXP(#expected_except), "exception not throwed"), WHERE);	\
		}																			\
	}																				\
}																					
#endif