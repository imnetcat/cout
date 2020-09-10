#pragma once
#include "copyable.h"
#include "dir_descryptor.h"
#include "../exception/file_already_exist.h"
#include "../exception/dir_not_exist.h"
#include "../exception/non_readable.h"
#include "../exception/non_writable.h"
#include <vector>
#include <fstream>
#include <istream>
namespace Cout
{
	namespace Core
	{
		namespace Filesystem
		{
			class CopyableDir : public Copyable, virtual public DirDescryptor
			{
			public:
				CopyableDir(const Path& p) : DirDescryptor(p) {};
				void copy(const DirDescryptor& dest) const override
				{
					if (!exist())
						throw Cout::Exceptions::Core::dir_not_exist(WHERE, "source folder not found when copying");
					if (!dest.exist())
						throw Cout::Exceptions::Core::dir_not_exist(WHERE, "destination not found when copying");
					if (dest.listing().contains((*this)))
						throw Cout::Exceptions::Core::file_already_exist(WHERE, "copying destination already contains source folder");

					auto dir_name = _path.filename();
					fs::copy(_path, dest.path() / dir_name, std::filesystem::copy_options::recursive);
				}
			};
		}
	}
}