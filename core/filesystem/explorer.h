#pragma once
#include "context_menu.h"
#include "../patterns/facade.h"
#include <functional>
#include <vector>
namespace Core
{
	namespace Filesystem
	{
		class Explorer : public Pattern::Facade<ContextMenu>
		{
		public:
			Explorer() : _path(fs::current_path()) {}
			Explorer(const Path& p) : _path(p) {}

			bool exist(const Path& p);

			bool isdir(const Path& p);

			size_t size(const Path& p);

			Collection listing(const Path& dir) const;

			void move(const Path& source, const Path& dest);
			void copy(const Path& source, const Path& dest);

			void remove(const Path& p);
			void mkdir(const Path& p);
			void mkfile(const Path& p);

			using ReadCallback = ContextMenu::ReadCallback;
			void read(const Path& file, size_t block_size, ReadCallback callback);

			std::vector<Byte> read(const Path& file);

			Path& path();

			void cd(const Path&);

		private:
			Path _path;
		};
	}
}