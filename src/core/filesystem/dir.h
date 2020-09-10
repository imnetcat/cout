#pragma once
#include "path.h"
#include "copyable_dir.h"
#include "moveable_dir.h"
#include "dir_descryptor.h"
#include <vector>
#include <fstream>
#include <istream>
namespace Core
{
	namespace Filesystem
	{
		class Dir :
			public CopyableDir,
			public MoveableDir,
			virtual public DirDescryptor
		{
		public:
			Dir(const Path&);
		};
	}
}