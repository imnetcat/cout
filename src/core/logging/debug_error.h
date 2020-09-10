#pragma once
#include "error.h"
namespace Cout
{
	namespace Core
	{
		namespace Logging
		{
			class DebugError : public Error
			{
			public:
				DebugError();
			};
		}
	}
}