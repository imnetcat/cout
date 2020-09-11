#include "explorer.h"
#include "../exception/dir_not_exist.h"
#include "../exception/file_not_exist.h"
#include "../../core/types/binary.h"
#include <algorithm>

bool Cout::Core::Filesystem::Explorer::isdir(const Path& p)
{
	return fs::is_directory(p);
}

void Cout::Core::Filesystem::Explorer::write(const Path& path, const Cout::Binary& data)
{
	WriteableFile file(path);
	_component->write(file, data);
}

bool Cout::Core::Filesystem::Explorer::exist(const Path& p)
{
	return _component->exist(Descryptor(p));
}
size_t Cout::Core::Filesystem::Explorer::size(const Path& p)
{
	if (!exist(p))
		throw Cout::Exceptions::Core::file_not_exist(WHERE, "explorer checking size");

	if (isdir(p))
	{
		return _component->size(DirDescryptor(p));
	}
	else
	{
		return _component->size(FileDescryptor(p));
	}
}
Cout::Core::Filesystem::Collection Cout::Core::Filesystem::Explorer::listing(const Path& dir) const
{
	return _component->listing(DirDescryptor(dir));
}
Cout::Binary Cout::Core::Filesystem::Explorer::read(const Path& fname)
{
	auto file = ReadableFile(fname);
	return _component->read(file);
}

void Cout::Core::Filesystem::Explorer::read(const Path& fname, size_t block_size, ReadCallback callback)
{
	auto file = ReadableFile(fname);
	_component->read(file, block_size, callback);
}

Cout::Core::Filesystem::Path Cout::Core::Filesystem::Explorer::temp()
{
	return fs::temp_directory_path();
}

void Cout::Core::Filesystem::Explorer::move(const Path& source, const Path& dest)
{
	if (isdir(source))
	{
		auto dir = MoveableDir{ source };
		_component->move(dir, { dest });
	}
	else
	{
		auto file = MoveableFile{ source };
		_component->move(file, { dest });
	}
}
void Cout::Core::Filesystem::Explorer::copy(const Path& source, const Path& dest)
{
	if (isdir(source))
	{
		_component->copy(CopyableDir{ source }, { dest });
	}
	else
	{
		_component->copy(CopyableFile{ source }, { dest });
	}
}

Cout::Core::Filesystem::Collection Cout::Core::Filesystem::Explorer::find(const Path& base_dir, const std::set<std::string>& files, int max_level, int level)
{
	Collection res;
	if (max_level == level)
		return res;

	auto list = listing(base_dir);
	for (auto& file : list.files)
	{
		if (files.count(file.path().filename().string()))
			res.files.push_back(file);
	}
	for (auto& dir : list.dirs)
	{
		if (files.count(dir.path().filename().string()))
			res.dirs.push_back(dir);
		res.append(find(base_dir, files, max_level, level + 1));
	}
	return res;
}
Cout::Core::Filesystem::Collection Cout::Core::Filesystem::Explorer::find(const Path& base_dir, const std::string& fnfile, int max_level, int level)
{
	Collection res;
	if (max_level == level)
		return res;

	auto list = listing(base_dir);
	for (auto& file : list.files)
	{
		if (fnfile == file.path().filename().string())
			res.files.push_back(file);
	}
	for (auto& dir : list.dirs)
	{
		if (fnfile == dir.path().filename().string())
			res.dirs.push_back(dir);
		res.append(find(base_dir, fnfile, max_level, level + 1));
	}
	return res;
}

void Cout::Core::Filesystem::Explorer::remove(const Path& p)
{
	auto d = Descryptor(p);
	if (!_component->exist(d))
		throw Cout::Exceptions::Core::file_not_exist(WHERE, "explorer deleting unexisted file or dir");

	_component->remove(d);
}
void Cout::Core::Filesystem::Explorer::mkdir(const Path& p)
{
	_component->create(DirDescryptor{ p });
}
void Cout::Core::Filesystem::Explorer::mkfile(const Path& p)
{
	_component->create(FileDescryptor{ p });
}

Cout::Core::Filesystem::Path& Cout::Core::Filesystem::Explorer::path()
{
	return _path;
}

void Cout::Core::Filesystem::Explorer::cd(const Path& p)
{
	if (!exist(p))
		throw Cout::Exceptions::Core::dir_not_exist(WHERE, "explorer change dir");
	if(!isdir(p))
		throw Cout::Exceptions::Core::dir_not_exist(WHERE, "explorer change dir");

	_path = p;
}
