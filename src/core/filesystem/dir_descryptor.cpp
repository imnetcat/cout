#include "dir_descryptor.h"
#include "../exception/invalid_argument.h"
#include "../exception/dir_not_exist.h"
#include "../exception/dir_already_exist.h"

Cout::Core::Filesystem::Path Cout::Core::Filesystem::DirDescryptor::path() const
{
	return _path;
}

void Cout::Core::Filesystem::DirDescryptor::path(const Path& new_path)
{
	if (new_path.empty())
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "path is empty");

	fs::file_status s = fs::status(new_path);
	bool exist = fs::status_known(s) ? fs::exists(s) : fs::exists(new_path);
	if (exist && !fs::is_directory(new_path))
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "path contains file not a dir");

	_path = new_path;
}

Cout::Core::Filesystem::DirDescryptor::DirDescryptor(const Path& p)
{
	path(p);
}

size_t Cout::Core::Filesystem::DirDescryptor::size() const
{
	if (!exist())
		throw Cout::Exceptions::Core::dir_not_exist(WHERE, "checking dir size");

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

void Cout::Core::Filesystem::DirDescryptor::remove() const
{
	if (!exist())
		throw Cout::Exceptions::Core::dir_not_exist(WHERE, "deleting unexisted dir");

	Descryptor::remove();
}
void Cout::Core::Filesystem::DirDescryptor::create() const
{
	if (exist())
		throw Cout::Exceptions::Core::dir_already_exist(WHERE, "creating new dir");

	fs::create_directories(_path);
}

Cout::Core::Filesystem::Collection Cout::Core::Filesystem::DirDescryptor::listing() const
{
	if (!exist())
		throw Cout::Exceptions::Core::dir_not_exist(WHERE, "listing unexisted dir");

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