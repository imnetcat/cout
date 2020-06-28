#pragma once
#include <string>
#include <stdexcept>
namespace Core
{
	namespace Exception
	{
		class base
		{
		public:
			base(const std::exception& ex);
			base(const std::string msg_when);
			base(const std::string msg_when, const std::string smg_where);
			virtual ~base() {};
			// indicates what exactly went wrong
			virtual const char* what() const noexcept = 0;

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
}