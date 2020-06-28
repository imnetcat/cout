#pragma once
#include "dir.h"
#include "file.h"
#include <functional>
#include <vector>
namespace Core
{
	namespace Filesystem
	{
		class ContextMenu
		{
		public:
			using ReadCallback = std::function<void(std::vector<Byte>)>;

			static void remove(const IDescryptor& source);
			static void create(const IExDescryptor& source);
			static bool exist(const IDescryptor& p);
			static size_t size(const IExDescryptor& p);

			static Collection listing(const DirDescryptor& dir);

			static void read(ReadableFile& file, size_t block_size, ReadCallback callback);
			static void read(ReadableFile& file, ReadCallback callback);
			
			static void move(MoveableFile& source, const DirDescryptor& dest);
			static void move(MoveableDir& source, const DirDescryptor& dest);
			static void copy(CopyableFile& source, const DirDescryptor& dest);
			static void copy(CopyableDir& source, const DirDescryptor& dest);
		};
	}
}