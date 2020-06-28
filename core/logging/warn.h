#pragma once
#include "log.h"
#include "../patterns/facade.h"
#include <functional>
namespace Core
{
	namespace Logging
	{
		class Warn : private Log
		{
		public:
			Warn();
			const std::string log(const std::string& text);
		};
	}
}