#pragma once
#include <string>
#include <stdexcept>
#include "../config.h"
namespace Exceptions
{
	class base
	{
	public:
		base(const std::exception& ex);
		base(const std::string msg_where, const std::string msg_what);
		virtual ~base() {};

		// get hex id of exception
		//virtual const std::string id() const noexcept = 0;

		// indicates what exactly went wrong
		virtual const std::string what() const noexcept = 0;

		const std::string& when() const noexcept
		{
			return _when;
		}
		const std::string& where() const noexcept
		{
			return _where;
		}

		//
		const std::string log() const noexcept;
		//
		const std::string log(const std::string&, const std::string&) const noexcept;
	private:
		// indicates under what condition an exception was raised
		// for example "when: something = 1, and = some_other"
		const std::string _when;
		// indicates where in the program an error occurred
		const std::string _where;
	};
}

#define LEFT_SEP "("
#define RGHT_SEP ")"
#define _EXCEPTION__WRAP_FORMAT_(filep, lsep, lineno, rsep) filep lsep lineno rsep
#define _EXCEPTION__WRAP_DLEVEL_(filep, lineno) _EXCEPTION__WRAP_FORMAT_(filep, LEFT_SEP, #lineno, RGHT_SEP)
#define _EXCEPTION__WRAP_(filep, lineno) _EXCEPTION__WRAP_DLEVEL_(filep, lineno)

#ifdef INDEBUG
#define WHERE _EXCEPTION__WRAP_(__FILE__, __LINE__)
#else
#define WHERE _EXCEPTION__WRAP_("", __LINE__)
#endif