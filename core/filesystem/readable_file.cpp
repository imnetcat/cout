#include "readable_file.h"
#include"../exception/non_readable.h"
#include"../exception/access_denied.h"
#include"../exception/file_not_exist.h"
using namespace std;

Core::Filesystem::ReadableFile::ReadableFile(const Path& p) :
	FileDescryptor(p) {}

Core::Filesystem::ReadableFile::~ReadableFile()
{
	close();
};

std::vector<Core::Filesystem::Byte> Core::Filesystem::ReadableFile::read(size_t bytes2read, size_t start_pos)
{
	rhandle.seekg(start_pos, ios::beg);

	size_t s = size();

	vector<Byte> buffer(bytes2read);

	rhandle.read(buffer.data(), bytes2read);

	return buffer;
}

void Core::Filesystem::ReadableFile::open()
{
	if (!exist())
		throw Exception::file_not_exist("open file for reading");
	if (!size())
		throw Exception::non_readable("open empty file for reading");
	rhandle = ifstream(_path, ios::binary);
	readable = rhandle && size();
	if (!rhandle)
		throw Exception::access_denied("open file for reading");
}

void Core::Filesystem::ReadableFile::close()
{
	rhandle.close();
	readable = false;
}

void Core::Filesystem::ReadableFile::open4read()
{
	ReadableFile::open();
}

void Core::Filesystem::ReadableFile::close4read()
{
	ReadableFile::close();
}