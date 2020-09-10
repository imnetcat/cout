#pragma once
#include "../../core/types/binary.h"
#include <vector>
#include <fstream>
#include <istream>
namespace Cout
{
	namespace Core
	{
		namespace Filesystem
		{
			class Writeable
			{
			public:
				virtual ~Writeable() {}
				virtual void write(const Binary& data) = 0;
				virtual std::ofstream& whandle() = 0;
			};
		}
	}
}