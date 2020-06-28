#include "readable_file.h"
#include"../exception/non_readable.h"
#include"../exception/access_denied.h"
#include"../exception/file_not_exist.h"
using namespace std;
using namespace Core::Filesystem;
using namespace Exceptions::Core;

ReadableFile::ReadableFile(const Path& p) :
	FileDescryptor(p) {}

ReadableFile::~ReadableFile()
{
	close();
};

std::vector<Byte> ReadableFile::read(size_t bytes2read, size_t start_pos)
{
	rhandle.seekg(start_pos, ios::beg);

	size_t s = size();

	vector<Byte> buffer(bytes2read);

	rhandle.read(buffer.data(), bytes2read);

	return buffer;
}

void ReadableFile::open()
{
	if (!exist())
		throw file_not_exist("open file for reading");
	if (!size())
		throw non_readable("open empty file for reading");
	rhandle = ifstream(_path, ios::binary);
	readable = rhandle && size();
	if (!rhandle)
		throw access_denied("open file for reading");
}

void ReadableFile::close()
{
	rhandle.close();
	readable = false;
}

void ReadableFile::open4read()
{
	ReadableFile::open();
}

void ReadableFile::close4read()
{
	ReadableFile::close();
}