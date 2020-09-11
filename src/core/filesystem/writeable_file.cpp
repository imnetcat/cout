#include "writeable_file.h"
#include"../exception/non_readable.h"
#include"../exception/access_denied.h"
#include"../exception/file_not_exist.h"
#include"../exception/logic_error.h"
using namespace std;
using namespace Cout::Core::Filesystem;
using namespace Cout::Exceptions::Core;

WriteableFile::WriteableFile(const Path& p) :
	FileDescryptor(p) {}

WriteableFile::~WriteableFile()
{
	close();
};
ofstream& WriteableFile::whandle()
{
	return _whandle;
}
void WriteableFile::write(const Cout::Binary& data)
{
	if (!exist())
		throw file_not_exist(WHERE, "write file");
	if (!_whandle)
		throw Cout::Exceptions::Core::logic_error(WHERE, "writing in file first you need to open the file for writing");

	for(size_t i = 0; i < data.size(); i++)
		_whandle << data[i];
}

void WriteableFile::open()
{
	if (!exist())
		throw file_not_exist(WHERE, "open file for reading");
	_whandle = ofstream(_path, ios::binary | ios::app);
	writeable = _whandle && size();
	if (!_whandle)
		throw access_denied(WHERE, "open file for reading");
}

void WriteableFile::close()
{
	_whandle.close();
	writeable = false;
}

void WriteableFile::open4write()
{
	WriteableFile::open();
}

void WriteableFile::close4write()
{
	WriteableFile::close();
}