#include "context_menu.h"
using namespace std;
using namespace Core::Filesystem;

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
void ContextMenu::read(ReadableFile& file, ReadCallback callback)
{
	file.open4read();
	callback(file.read(file.size(), 0));
	file.close4read();
}

void ContextMenu::move(MoveableFile& source, const DirDescryptor& dest)
{
	source.move(dest);
}
void ContextMenu::move(MoveableDir& source, const DirDescryptor& dest)
{
	source.move(dest);
}

void ContextMenu::copy(CopyableDir& source, const DirDescryptor& dest)
{
	source.copy(dest);
}
void ContextMenu::copy(CopyableFile& source, const DirDescryptor& dest)
{
	source.copy(dest);
}