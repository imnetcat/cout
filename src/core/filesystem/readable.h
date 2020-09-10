#pragma once
#include "../../core/types/binary.h"
#include <vector>
#include <fstream>
#include <istream>
namespace Core
{
	namespace Filesystem
	{
		class Readable
		{
		public:
			virtual ~Readable() {}
			virtual Binary read(size_t bytes2read, size_t start_pos = 0) = 0;
		};
	}
}