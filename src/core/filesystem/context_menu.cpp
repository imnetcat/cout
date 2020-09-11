#include "context_menu.h"
void Cout::Core::Filesystem::ContextMenu::remove(const IDescryptor& source)
{
	source.remove();
}
void Cout::Core::Filesystem::ContextMenu::create(const IExDescryptor& source)
{
	source.create();
}
bool Cout::Core::Filesystem::ContextMenu::exist(const IDescryptor& d)
{
	return d.exist();
}
size_t Cout::Core::Filesystem::ContextMenu::size(const IExDescryptor& d)
{
	return d.size();
}
Cout::Core::Filesystem::Collection Cout::Core::Filesystem::ContextMenu::listing(const DirDescryptor& dir)
{
	return dir.listing();
}
void Cout::Core::Filesystem::ContextMenu::write(WriteableFile& file, const Cout::Binary& data)
{
	file.open4write();
	file.write(data);
	file.close4write();
}
void Cout::Core::Filesystem::ContextMenu::read(ReadableFile& file, size_t block_size, ReadCallback callback)
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
Cout::Binary Cout::Core::Filesystem::ContextMenu::read(ReadableFile& file)
{
	file.open4read();
	Binary data = file.read(file.size(), 0);
	file.close4read();
	return data;
}
void Cout::Core::Filesystem::ContextMenu::move(MoveableFile& source, const DirDescryptor& dest)
{
	source.move(dest);
}
void Cout::Core::Filesystem::ContextMenu::move(MoveableDir& source, const DirDescryptor& dest)
{
	source.move(dest);
}
void Cout::Core::Filesystem::ContextMenu::copy(const CopyableDir& source, const DirDescryptor& dest)
{
	source.copy(dest);
}
void Cout::Core::Filesystem::ContextMenu::copy(const CopyableFile& source, const DirDescryptor& dest)
{
	source.copy(dest);
}