#pragma once
#include "dir_descryptor.h"
#include <vector>
#include <fstream>
#include <istream>
namespace Core
{
	namespace Filesystem
	{
		class Copyable
		{
		public:
			virtual ~Copyable() {}
			virtual void copy(const DirDescryptor& dist) = 0;
		};
	}
}