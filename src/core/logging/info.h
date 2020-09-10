#pragma once
#include "log.h"
#include <functional>
namespace Cout
{
	namespace Core
	{
		namespace Logging
		{
			class Info : public Log
			{
			public:
				Info(const std::string&);
				Info();
			};
		}
	}
}