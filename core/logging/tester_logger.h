#pragma once
#include "logger.h"
#include "../config.h"
#ifdef INDEBUG
#include <iostream>
namespace Core
{
	namespace Logging
	{
		class TesterLogger : public Logger
		{
		public:
			TesterLogger();
		};
	}
}
#endif
