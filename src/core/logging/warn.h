#pragma once
#include "log.h"
#include "../pattern/facade.h"
#include <functional>
namespace Cout
{
	namespace Core
	{
		namespace Logging
		{
			class Warn : public Log
			{
			public:
				Warn(const std::string&);
				Warn();
				const std::string log(const std::string& text) override;
			};
		}
	}
}