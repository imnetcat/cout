#include "writeable_file.h"
#include "../exception/non_readable.h"
#include "../exception/access_denied.h"
#include "../exception/file_not_exist.h"
#include "../exception/logic_error.h"

Cout::Core::Filesystem::WriteableFile::WriteableFile(const Path& p) :
	FileDescryptor(p) {}

Cout::Core::Filesystem::WriteableFile::~WriteableFile()
{
	close();
};
std::ofstream& Cout::Core::Filesystem::WriteableFile::whandle()
{
	return _whandle;
}
void Cout::Core::Filesystem::WriteableFile::write(const Cout::Binary& data)
{
	if (!exist())
		throw Cout::Exceptions::Core::file_not_exist(WHERE, "write file");
	if (!_whandle)
		throw Cout::Exceptions::Core::logic_error(WHERE, "writing in file first you need to open the file for writing");

	for(size_t i = 0; i < data.size(); i++)
		_whandle << data[i];
}

void Cout::Core::Filesystem::WriteableFile::open()
{
	if (!exist())
		throw Cout::Exceptions::Core::file_not_exist(WHERE, "open file for reading");
	_whandle = std::ofstream(_path, std::ios::binary | std::ios::app);
	writeable = _whandle && size();
	if (!_whandle)
		throw Cout::Exceptions::Core::access_denied(WHERE, "open file for reading");
}

void Cout::Core::Filesystem::WriteableFile::close()
{
	_whandle.close();
	writeable = false;
}

void Cout::Core::Filesystem::WriteableFile::open4write()
{
	WriteableFile::open();
}

void Cout::Core::Filesystem::WriteableFile::close4write()
{
	WriteableFile::close();
}