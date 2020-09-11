#include "file.h"

Cout::Core::Filesystem::File::File(const Path& p) :
	CopyableFile(p),
	MoveableFile(p),
	ReadableFile(p),
	WriteableFile(p),
	FileDescryptor(p) {}

Cout::Core::Filesystem::File::~File()
{
	close();
}

void Cout::Core::Filesystem::File::open()
{
	ReadableFile::open();
	WriteableFile::open();
}
void Cout::Core::Filesystem::File::close()
{
	ReadableFile::close();
	WriteableFile::close();
}
