#pragma once
#ifndef _BASE_EXCEPTIONS_H_
#define _BASE_EXCEPTIONS_H_
#include <string>
namespace Exception
{
	class base
	{
	public:
		base(const char* when);
		base(const std::string& when);
		virtual ~base() {};
		// indicates what exactly went wrong
		virtual const char* what() const noexcept = 0;

		// TODO: stacktrace:
		// indicates where in the program an error occurred
		//virtual const char* where() const noexcept = 0;

		// indicates under what conditions an exception was raised
		const std::string& when() const noexcept;
	private:
		const std::string msg_when;
	};
}
#endif
