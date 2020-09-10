#pragma once
#include "error.h"
namespace Cout
{
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
}