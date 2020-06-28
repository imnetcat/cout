#pragma once
namespace Core
{
	namespace Filesystem
	{
		class OpenCloseable
		{
		public:
			virtual ~OpenCloseable() {}
			virtual void open() = 0;
			virtual void close() = 0;
		};
	}
}