#include "context_menu.h"
using namespace std;
using namespace Core::Filesystem;
using namespace Exceptions::Core;

void ContextMenu::remove(const IDescryptor& source)
{
	source.remove();
}
void ContextMenu::create(const IExDescryptor& source)
{
	source.create();
}
bool ContextMenu::exist(const IDescryptor& d)
{
	return d.exist();
}
size_t ContextMenu::size(const IExDescryptor& d)
{
	return d.size();
}

Collection ContextMenu::listing(const DirDescryptor& dir) 
{
	return dir.listing();
}

void ContextMenu::write(WriteableFile& file, const Binary& data)
{
	file.open4write();
	file.write(data);
	file.close4write();
}

void ContextMenu::read(ReadableFile& file, size_t block_size, ReadCallback callback)
{
	file.open4read();
	size_t size = file.size();

	for (size_t pos = 0; pos < size; pos += block_size)
	{
		if (pos + block_size > size)
			block_size = size - pos;
		callback(file.read(block_size, pos));
	}
	file.close4read();
}
Binary ContextMenu::read(ReadableFile& file)
{
	file.open4read();
	Binary data = file.read(file.size(), 0);
	file.close4read();
	return data;
}

void ContextMenu::move(MoveableFile& source, const DirDescryptor& dest)
{
	source.move(dest);
}
void ContextMenu::move(MoveableDir& source, const DirDescryptor& dest)
{
	source.move(dest);
}

void ContextMenu::copy(const CopyableDir& source, const DirDescryptor& dest)
{
	source.copy(dest);
}
void ContextMenu::copy(const CopyableFile& source, const DirDescryptor& dest)
{
	source.copy(dest);
}