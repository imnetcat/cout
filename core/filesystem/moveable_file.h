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
			MoveableFile(const Path& p) : FileDescryptor(p) {}
			void move(const DirDescryptor& dest) override
			{
				if (!exist())
					throw Exception::file_not_exist("source file not found when moving");
				if (!dest.exist())
					throw Exception::dir_not_exist("destination not found when moving");
				if (dest.listing().contains((*this)))
					throw Exception::file_already_exist("moving destination already contains source file");

				bool test_o_access = std::ofstream(_path, std::ios::app).good();
				if (!test_o_access)
					throw Exception::non_readable("moving file descryptor busy");
				bool test_i_access = std::ifstream(_path).good();
				if (!test_i_access)
					throw Exception::non_writable("moving file descryptor busy");

				auto file_name = _path.filename();
				fs::copy(_path, dest.path() / file_name);
				remove();
				_path = dest.path() / file_name;
			}
		};
	}
}