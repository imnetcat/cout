#pragma once
#include "dir.h"
#include "file.h"
#include <functional>
#include <vector>
#include "../../core/types/binary.h"
namespace Cout
{
	namespace Core
	{
		namespace Filesystem
		{
			class ContextMenu
			{
			public:
				using ReadCallback = std::function<void(const Binary&)>;

				static void remove(const IDescryptor& source);
				static void create(const IExDescryptor& source);
				static bool exist(const IDescryptor& p);
				static size_t size(const IExDescryptor& p);

				static Collection listing(const DirDescryptor& dir);

				static void read(ReadableFile& file, size_t block_size, ReadCallback callback);
				static Binary read(ReadableFile& file);

				static void write(WriteableFile& file, const Binary& data);

				static void move(MoveableFile& source, const DirDescryptor& dest);
				static void move(MoveableDir& source, const DirDescryptor& dest);
				static void copy(const CopyableFile& source, const DirDescryptor& dest);
				static void copy(const CopyableDir& source, const DirDescryptor& dest);
			};
		}
	}
}