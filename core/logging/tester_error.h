#pragma once
#include "error.h"
namespace Core
{
	namespace Logging
	{
		class TesterError : public Error
		{
		public:
			TesterError();
		};
	}
}