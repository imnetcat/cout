#pragma once
#include "byte.h"
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
				return fs::status_known(s) ? fs::exists(s) : fs::exists(_path);
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
				return this->path() == obj.path();
			}
		};
	}
}