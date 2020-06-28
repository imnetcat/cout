#pragma once
#include "copyable.h"
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
		class CopyableFile : public Copyable, virtual public FileDescryptor
		{
		public:
			CopyableFile(const Path& p) : FileDescryptor(p) {}
			void copy(const DirDescryptor& dest) const override
			{
				if (!exist())
					throw Exceptions::Core::file_not_exist("source file not found when copying");
				if (!dest.exist())
					throw Exceptions::Core::dir_not_exist("destination not found when copying");
				if (dest.listing().contains((*this)))
					throw Exceptions::Core::file_already_exist("copying destination already contains source file");

				bool test_o_access = std::ofstream(_path, std::ios::app).good();
				if (!test_o_access)
					throw Exceptions::Core::non_readable("copyable file descryptor busy");
				bool test_i_access = std::ifstream(_path).good();
				if (!test_i_access)
					throw Exceptions::Core::non_writable("copyable files descryptor busy");

				fs::copy(_path, dest.path());
			}
		};
	}
}