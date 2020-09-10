#pragma once
#include "error.h"
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