#include "dir_descryptor.h"
#include "../exception/invalid_argument.h"
#include "../exception/dir_not_exist.h"
#include "../exception/dir_already_exist.h"
using namespace Core::Filesystem;

Path DirDescryptor::path() const
{
	return _path;
}

void DirDescryptor::path(const Path& new_path)
{
	if (new_path.empty())
		throw Exception::invalid_argument("path is empty");

	fs::file_status s = fs::status(new_path);
	bool exist = fs::status_known(s) ? fs::exists(s) : fs::exists(new_path);
	if (exist && !fs::is_directory(new_path))
		throw Exception::invalid_argument("path contains file not a dir");

	_path = new_path;
}

DirDescryptor::DirDescryptor(const Path& p)
{
	path(p);
}

size_t DirDescryptor::size() const
{
	if (!exist())
		throw Core::Exception::dir_not_exist("checking dir size");

	size_t result = 0;
	for (const auto & entry : std::filesystem::directory_iterator(_path))
	{
		if (entry.is_directory())
			result += DirDescryptor(entry.path()).size();
		else
			result += FileDescryptor(entry.path()).size();
	}
	return result;
}

void DirDescryptor::remove() const
{
	if (!exist())
		throw Exception::dir_not_exist("deleting unexisted dir");

	Descryptor::remove();
}
void DirDescryptor::create() const
{
	if (exist())
		throw Exception::dir_already_exist("creating new dir");

	fs::create_directory(_path);
}

Collection DirDescryptor::listing() const
{
	if (!exist())
		throw Core::Exception::dir_not_exist("listing unexisted dir");

	Collection listing;
	for (const auto & entry : std::filesystem::directory_iterator(_path))
	{
		if (entry.is_directory())
			listing.dirs.push_back(entry.path());
		else
			listing.files.push_back(entry.path());
	}
	return listing;
}