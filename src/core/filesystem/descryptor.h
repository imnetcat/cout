#pragma once
#include "../../core/types/byte.h"
#include "path.h"
namespace Cout
{
	namespace Core
	{
		namespace Filesystem
		{
			class IDescryptor
			{
			public:
				virtual ~IDescryptor() {};
				virtual void remove() const = 0;
				virtual bool exist() const = 0;
			};

			class Descryptor : public IDescryptor
			{
			public:
				Descryptor(const Path& p) : _path(p) {};
				bool exist() const override
				{
					fs::file_status s = fs::status(_path);
					bool result = fs::status_known(s) ? fs::exists(s) : fs::exists(_path);
					return result;
				}
				void remove() const override
				{
					fs::remove_all(_path);
				}
			protected:
				Path _path;
			};

			class IExDescryptor : public Descryptor
			{
			public:
				IExDescryptor() : Descryptor("") {}
				virtual ~IExDescryptor() {};
				virtual void create() const = 0;
				virtual size_t size() const = 0;
				virtual Path path() const = 0;
				virtual void path(const Path&) = 0;

				bool operator==(const IExDescryptor& obj)
				{
					return this->path().filename() == obj.path().filename();
				}
			};
		}
	}
}