#include "explorer.h"
#include "../exception/dir_not_exist.h"
#include "../exception/file_not_exist.h"
#include <algorithm>
using namespace std;
using namespace Core;

bool Filesystem::Explorer::isdir(const Path& p)
{
	return fs::is_directory(p);
}

bool Filesystem::Explorer::exist(const Path& p)
{
	return _component->exist(Descryptor(p));
}
size_t Filesystem::Explorer::size(const Path& p)
{
	if (!exist(p))
		throw Exception::file_not_exist("explorer checking size");

	if (isdir(p))
	{
		return _component->size(DirDescryptor(p));
	}
	else
	{
		return _component->size(FileDescryptor(p));
	}
}
Filesystem::Collection Filesystem::Explorer::listing(const Path& dir) const
{
	return _component->listing(DirDescryptor(dir));
}
vector<Filesystem::Byte> Filesystem::Explorer::read(const Path& file)
{
	vector<Filesystem::Byte> data;
	_component->read(ReadableFile(file), [&data](vector<Byte> block) {
		std::copy(block.begin(), block.end(), back_inserter(data));
	});
	return data;
}

void Filesystem::Explorer::read(const Path& file, size_t block_size, ReadCallback callback)
{
	_component->read(ReadableFile(file), block_size, callback);
}

void Filesystem::Explorer::move(const Path& source, const Path& dest)
{
	if (isdir(source))
	{
		_component->move(MoveableDir{ source }, { dest });
	}
	else
	{
		_component->move(MoveableFile{ source }, { dest });
	}
}
void Filesystem::Explorer::copy(const Path& source, const Path& dest)
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

void Filesystem::Explorer::remove(const Path& p)
{
	auto d = Descryptor(p);
	if (!_component->exist(d))
		throw Exception::file_not_exist("explorer deleting unexisted file or dir");

	_component->remove(d);
}
void Filesystem::Explorer::mkdir(const Path& p)
{
	_component->create(DirDescryptor{ p });
}
void Filesystem::Explorer::mkfile(const Path& p)
{
	_component->create(FileDescryptor{ p });
}

Filesystem::Path& Filesystem::Explorer::path()
{
	return _path;
}

void Filesystem::Explorer::cd(const Path& p)
{
	if (!exist(p))
		throw Exception::dir_not_exist("explorer change dir");
	if(!isdir(p))
		throw Exception::dir_not_exist("explorer change dir");

	_path = p;
}
