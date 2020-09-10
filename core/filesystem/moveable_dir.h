#pragma once
#include "moveable.h"
#include "dir_descryptor.h"
#include "../exception/dir_already_exist.h"
#include "../exception/dir_not_exist.h"
#include "../exception/non_readable.h"
#include "../exception/non_writable.h"
#include <vector>
#include <fstream>
#include <istream>
namespace Core
{
	namespace Filesystem
	{
		class MoveableDir : public Moveable, virtual public DirDescryptor
		{
		public:
			MoveableDir(const Path& p) : DirDescryptor(p) {};
			void move(const DirDescryptor& dest) override
			{
				if (!exist())
					throw Exceptions::Core::dir_not_exist(WHERE, "source folder not found when moving");
				if (!dest.exist())
					throw Exceptions::Core::dir_not_exist(WHERE, "destination not found when moving");
				if (dest.listing().contains((*this)))
					throw Exceptions::Core::dir_already_exist(WHERE, "moving destination already contains source folder");
				
				auto dir_name = _path.filename();
				fs::copy(_path, dest.path() / dir_name, std::filesystem::copy_options::recursive);
				remove();
				_path = dest.path() / dir_name;
			}
		};
	}
}