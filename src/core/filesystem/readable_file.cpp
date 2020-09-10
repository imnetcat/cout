#include "readable_file.h"
#include"../exception/non_readable.h"
#include"../exception/access_denied.h"
#include"../exception/file_not_exist.h"
#include"../exception/out_of_range.h"
#include <iterator>
using namespace std;
using namespace Cout::Core::Filesystem;
using namespace Cout::Exceptions::Core;

ReadableFile::ReadableFile(const Path& p) :
	FileDescryptor(p) {}

ReadableFile::~ReadableFile()
{
	close();
};

Cout::Binary ReadableFile::read(size_t bytes2read, size_t start_pos)
{
	rhandle.seekg(start_pos, ios::beg);
	size_t s = size();
	if (start_pos + bytes2read > s)
		throw Cout::Exceptions::Core::non_readable(WHERE, "open empty file for reading");

	SignedByte *buffer = new SignedByte[bytes2read];
	
	rhandle.read(buffer, bytes2read);

	return { buffer, bytes2read };
}

void ReadableFile::open()
{
	if (!exist())
		throw file_not_exist(WHERE, "open file for reading");
	if (!size())
		throw non_readable(WHERE, "open empty file for reading");
	rhandle = ifstream(_path, ios::binary);
	readable = rhandle && size();
	if (!rhandle)
		throw access_denied(WHERE, "open file for reading");
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