#include "file_descryptor.h"
#include "../exception/invalid_argument.h"
#include "../exception/file_not_exist.h"
#include "../exception/file_already_exist.h"
#include "../exception/access_denied.h"
#include <fstream>

Cout::Core::Filesystem::Path Cout::Core::Filesystem::FileDescryptor::path() const
{
	return _path;
}
void Cout::Core::Filesystem::FileDescryptor::path(const Path& new_path)
{
	if (new_path.empty())
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "path is empty");

	fs::file_status s = fs::status(new_path);
	bool exist = fs::status_known(s) ? fs::exists(s) : fs::exists(new_path);
	if (exist && fs::is_directory(new_path))
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "path contains dir not a file");

	_path = new_path;
}

Cout::Core::Filesystem::FileDescryptor::FileDescryptor(const Path& p)
{
	path(p);
}

size_t Cout::Core::Filesystem::FileDescryptor::size() const
{
	if (!exist())
		throw Cout::Exceptions::Core::file_not_exist(WHERE, "checking file size");
	return fs::file_size(_path);
}

void Cout::Core::Filesystem::FileDescryptor::remove() const
{
	if (!exist())
		throw Cout::Exceptions::Core::file_not_exist(WHERE, "deleting unexisted file");

	Descryptor::remove();
}
void Cout::Core::Filesystem::FileDescryptor::create() const
{
	if (exist())
		throw Cout::Exceptions::Core::file_already_exist(WHERE, "creating new file");

	auto temp = _path;
	temp.remove_filename();
	if (!fs::exists(temp))
	{
		fs::create_directories(temp);
	}

	std::ofstream file(_path, std::ios::binary);
	file.close();
}