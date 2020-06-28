#pragma once
#include "byte.h"
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
			virtual std::vector<Byte> read(size_t bytes2read, size_t start_pos = 0) = 0;
		};
	}
}