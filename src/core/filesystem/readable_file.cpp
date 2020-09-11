#include "readable_file.h"
#include "../exception/non_readable.h"
#include "../exception/access_denied.h"
#include "../exception/file_not_exist.h"
#include "../exception/out_of_range.h"
#include <iterator>

Cout::Core::Filesystem::ReadableFile::ReadableFile(const Path& p) :
	FileDescryptor(p) {}

Cout::Core::Filesystem::ReadableFile::~ReadableFile()
{
	close();
};

Cout::Binary Cout::Core::Filesystem::ReadableFile::read(size_t bytes2read, size_t start_pos)
{
	rhandle.seekg(start_pos, std::ios::beg);
	size_t s = size();
	if (start_pos + bytes2read > s)
		throw Cout::Exceptions::Core::non_readable(WHERE, "open empty file for reading");

	SignedByte *buffer = new SignedByte[bytes2read];
	
	rhandle.read(buffer, bytes2read);

	return { buffer, bytes2read };
}

void Cout::Core::Filesystem::ReadableFile::open()
{
	if (!exist())
		throw Cout::Exceptions::Core::file_not_exist(WHERE, "open file for reading");
	if (!size())
		throw Cout::Exceptions::Core::non_readable(WHERE, "open empty file for reading");
	rhandle = std::ifstream(_path, std::ios::binary);
	readable = rhandle && size();
	if (!rhandle)
		throw Cout::Exceptions::Core::access_denied(WHERE, "open file for reading");
}

void Cout::Core::Filesystem::ReadableFile::close()
{
	rhandle.close();
	readable = false;
}

void Cout::Core::Filesystem::ReadableFile::open4read()
{
	ReadableFile::open();
}

void Cout::Core::Filesystem::ReadableFile::close4read()
{
	ReadableFile::close();
}