#include "file_descryptor.h"
#include "../exception/invalid_argument.h"
#include "../exception/file_not_exist.h"
#include "../exception/file_already_exist.h"
#include "../exception/access_denied.h"
#include <fstream>
using namespace std;
using namespace Cout::Core::Filesystem;
using namespace Cout::Exceptions::Core;

Path FileDescryptor::path() const
{
	return _path;
}
void FileDescryptor::path(const Path& new_path)
{
	if (new_path.empty())
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "path is empty");

	fs::file_status s = fs::status(new_path);
	bool exist = fs::status_known(s) ? fs::exists(s) : fs::exists(new_path);
	if (exist && fs::is_directory(new_path))
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "path contains dir not a file");

	_path = new_path;
}

FileDescryptor::FileDescryptor(const Path& p)
{
	path(p);
}

size_t FileDescryptor::size() const
{
	if (!exist())
		throw file_not_exist(WHERE, "checking file size");
	return fs::file_size(_path);
}

void FileDescryptor::remove() const
{
	if (!exist())
		throw file_not_exist(WHERE, "deleting unexisted file");

	Descryptor::remove();
}
void FileDescryptor::create() const
{
	if (exist())
		throw file_already_exist(WHERE, "creating new file");

	auto temp = _path;
	temp.remove_filename();
	if (!fs::exists(temp))
	{
		fs::create_directories(temp);
	}

	ofstream file(_path, ios::binary);
	file.close();
}