#pragma once
#include "../config.h"
#ifdef INDEBUG
#include "ilogger.h"
#include <iostream>
namespace Cout
{
	namespace Core
	{
		namespace Logging
		{
			class TesterLogger : public ILogger
			{
			public:
				TesterLogger();
			};
		}
	}
}
#endif
