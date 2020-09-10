#pragma once
#include "descryptor.h"
namespace Cout
{
	namespace Core
	{
		namespace Filesystem
		{
			class FileDescryptor : public IExDescryptor
			{
			public:
				FileDescryptor() {};
				FileDescryptor(const Path& p);
				void remove() const override;
				void create() const override;
				size_t size() const override;
				Path path() const override;
				void path(const Path& new_path) override;
			};
		}
	}
}