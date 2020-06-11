#pragma once
#ifndef _BASE_EXCEPTIONS_H_
#define _BASE_EXCEPTIONS_H_
#include <string>
namespace CORE
{
	namespace Exception
	{
		class base
		{
		public:
			base(const char* when);
			base(const std::string& when);
			virtual ~base() {};
			virtual const char* what() const noexcept = 0;
			const char* when() const noexcept;
		private:
			const char* msg_when;
		};
	}
}
#endif
