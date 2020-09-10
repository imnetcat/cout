#pragma once
#include "dir_descryptor.h"
#include <vector>
#include <fstream>
#include <istream>
namespace Core
{
	namespace Filesystem
	{
		class Moveable
		{
		public:
			virtual ~Moveable() {}
			virtual void move(const DirDescryptor& dist) = 0;
		};
	}
}