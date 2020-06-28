#include "explorer.h"
#include "../exception/dir_not_exist.h"
#include "../exception/file_not_exist.h"
#include <algorithm>
using namespace std;
using namespace Core::Filesystem;
using namespace Exceptions::Core;

bool Explorer::isdir(const Path& p)
{
	return fs::is_directory(p);
}

bool Explorer::exist(const Path& p)
{
	return _component->exist(Descryptor(p));
}
size_t Explorer::size(const Path& p)
{
	if (!exist(p))
		throw file_not_exist("explorer checking size");

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
vector<Byte> Explorer::read(const Path& fname)
{
	auto file = ReadableFile(fname);
	vector<Byte> data;
	_component->read(file, [&data](vector<Byte> block) {
		std::copy(block.begin(), block.end(), back_inserter(data));
	});
	return data;
}

void Explorer::read(const Path& fname, size_t block_size, ReadCallback callback)
{
	auto file = ReadableFile(fname);
	_component->read(file, block_size, callback);
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

void Explorer::remove(const Path& p)
{
	auto d = Descryptor(p);
	if (!_component->exist(d))
		throw file_not_exist("explorer deleting unexisted file or dir");

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
		throw dir_not_exist("explorer change dir");
	if(!isdir(p))
		throw dir_not_exist("explorer change dir");

	_path = p;
}
