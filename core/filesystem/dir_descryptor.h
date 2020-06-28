#pragma once
#include "descryptor.h"
#include "file_descryptor.h"
namespace Core
{
	namespace Filesystem
	{
		struct Collection;

		class DirDescryptor : public IExDescryptor
		{
		public:
			DirDescryptor(const Path& p);
			void remove() const override;
			void create() const override;
			size_t size() const override;
			Path path() const override;
			void path(const Path& new_path) override;
			Collection listing() const;
		};


		struct Collection
		{
			std::vector<DirDescryptor> dirs;
			std::vector<FileDescryptor> files;
			bool contains(const IExDescryptor& d)
			{
				bool result = std::count(files.begin(), files.end(), d);
				if (!result)
					result = std::count(dirs.begin(), dirs.end(), d);

				return result;
			}
		};
	}
}