#pragma once
#include "copyable_file.h"
#include "moveable_file.h"
#include "readable_file.h"
#include "writeable_file.h"
#include "file_descryptor.h"
#include <vector>
#include <fstream>
#include <istream>
namespace Core
{
	namespace Filesystem
	{
		class File : 
			public CopyableFile, 
			public MoveableFile, 
			public ReadableFile,
			public WriteableFile
		{
		public:
			File(const Path&);
			~File();
			void open() override;
			void close() override;
		};
	}
}