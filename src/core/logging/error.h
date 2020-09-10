#pragma once
#include "log.h"
#include <string>
#include <functional>
namespace Cout
{
	namespace Core
	{
		namespace Logging
		{
			class Error : public Log
			{
			public:
				Error(const std::string&);
				Error();
				const std::string log(const std::string& text) override;
			};
		}
	}
}