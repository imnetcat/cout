#include "explorer.h"
#include "../exception/dir_not_exist.h"
#include "../exception/file_not_exist.h"
#include "../../core/types/binary.h"
#include <algorithm>
using namespace std;
using namespace Cout::Core::Filesystem;
using namespace Cout::Exceptions::Core;

bool Explorer::isdir(const Path& p)
{
	return fs::is_directory(p);
}

void Explorer::write(const Path& path, const Cout::Binary& data)
{
	WriteableFile file(path);
	_component->write(file, data);
}

bool Explorer::exist(const Path& p)
{
	return _component->exist(Descryptor(p));
}
size_t Explorer::size(const Path& p)
{
	if (!exist(p))
		throw file_not_exist(WHERE, "explorer checking size");

	if (isdir(p))
	{
		return _component->size(DirDescryptor(p));
	}
	else
	{
		return _component->size(FileDescryptor(p));
	}
}
Collection Explorer::listing(const Path& dir) const
{
	return _component->listing(DirDescryptor(dir));
}
Cout::Binary Explorer::read(const Path& fname)
{
	auto file = ReadableFile(fname);
	return _component->read(file);
}

void Explorer::read(const Path& fname, size_t block_size, ReadCallback callback)
{
	auto file = ReadableFile(fname);
	_component->read(file, block_size, callback);
}

Path Explorer::temp()
{
	return fs::temp_directory_path();
}

void Explorer::move(const Path& source, const Path& dest)
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
void Explorer::copy(const Path& source, const Path& dest)
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

Collection Explorer::find(const Path& base_dir, const set<string>& files, int max_level, int level)
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
Collection Explorer::find(const Path& base_dir, const string& fnfile, int max_level, int level)
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

void Explorer::remove(const Path& p)
{
	auto d = Descryptor(p);
	if (!_component->exist(d))
		throw file_not_exist(WHERE, "explorer deleting unexisted file or dir");

	_component->remove(d);
}
void Explorer::mkdir(const Path& p)
{
	_component->create(DirDescryptor{ p });
}
void Explorer::mkfile(const Path& p)
{
	_component->create(FileDescryptor{ p });
}

Path& Explorer::path()
{
	return _path;
}

void Explorer::cd(const Path& p)
{
	if (!exist(p))
		throw dir_not_exist(WHERE, "explorer change dir");
	if(!isdir(p))
		throw dir_not_exist(WHERE, "explorer change dir");

	_path = p;
}
