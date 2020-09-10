#pragma once
#include "context_menu.h"
#include "../pattern/facade.h"
#include <functional>
#include <vector>
#include <string>
#include <set>
namespace Cout
{
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

				Path temp();

				Collection listing(const Path& dir) const;

				void move(const Path& source, const Path& dest);
				void copy(const Path& source, const Path& dest);

				void remove(const Path& p);
				void mkdir(const Path& p);
				void mkfile(const Path& p);

				using ReadCallback = ContextMenu::ReadCallback;
				void read(const Path& file, size_t block_size, ReadCallback callback);

				Binary read(const Path& file);

				void write(const Path& file, const Binary& data);

				Path& path();

				Collection find(const Path& base_dir, const std::set<std::string>& files, int max_level, int level = 0);
				Collection find(const Path& base_dir, const std::string& file, int max_level, int level = 0);

				void cd(const Path&);

			private:
				Path _path;
			};
		}
	}
}