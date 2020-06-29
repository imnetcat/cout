#pragma once
#include "readable.h"
#include "opencloseable.h"
#include "file_descryptor.h"
#include <vector>
#include <fstream>
#include <istream>
namespace Core
{
	namespace Filesystem
	{
		class ReadableFile : public Readable, virtual public OpenCloseable, virtual public FileDescryptor
		{
		public:
			ReadableFile(const Path& p);
			virtual ~ReadableFile();
			std::vector<Byte> read(size_t bytes2read, size_t start_pos = 0) override;
			void open() override;
			void close() override;
			void open4read();
			void close4read();
		private:
			std::ifstream rhandle;
			bool readable;
		};
	}
}
