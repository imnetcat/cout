#pragma once
#include "moveable.h"
#include "file_descryptor.h"
#include "../exception/file_not_exist.h"
#include "../exception/file_already_exist.h"
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
		class MoveableFile : public Moveable, virtual public FileDescryptor
		{
		public:
			MoveableFile() {}
			MoveableFile(const Path& p) : FileDescryptor(p) {}
			void move(const DirDescryptor& dest) override
			{
				if (!exist())
					throw Exceptions::Core::file_not_exist(WHERE, "source file not found when moving");
				if (!dest.exist())
					throw Exceptions::Core::dir_not_exist(WHERE, "destination not found when moving");
				if (dest.listing().contains((*this)))
					throw Exceptions::Core::file_already_exist(WHERE, "moving destination already contains source file");

				bool test_o_access = std::ofstream(_path, std::ios::app).good();
				if (!test_o_access)
					throw Exceptions::Core::non_readable(WHERE, "moving file descryptor busy");
				bool test_i_access = std::ifstream(_path).good();
				if (!test_i_access)
					throw Exceptions::Core::non_writable(WHERE, "moving file descryptor busy");

				auto file_name = _path.filename();
				fs::copy(_path, dest.path() / file_name);
				remove();
				_path = dest.path() / file_name;
			}
		};
	}
}