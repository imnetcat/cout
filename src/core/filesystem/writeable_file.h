#pragma once
#include "writeable.h"
#include "opencloseable.h"
#include "file_descryptor.h"
#include <vector>
#include <fstream>
#include <istream>
namespace Core
{
	namespace Filesystem
	{
		class WriteableFile : public Writeable, virtual public OpenCloseable, virtual public FileDescryptor
		{
		public:
			WriteableFile(const Path& p);
			virtual ~WriteableFile();
			void write(const Binary& data) override;
			std::ofstream& whandle() override;
			void open() override;
			void close() override;
			void open4write();
			void close4write();
		private:
			std::ofstream _whandle;
			bool writeable;
		};
	}
}
