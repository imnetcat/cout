#pragma once
#include <fstream>
#include <filesystem>
#include <vector>
namespace CORE
{
	namespace fs = std::filesystem;
	using Byte = char;
	
	class IDescryptor
	{
	public:
		virtual void open() = 0;
		virtual void close() = 0;
	};

	class Descryptor : public IDescryptor
	{
	public:
		void open();
		void close();
	};

	class IFile : public IDescryptor
	{
	public:
		virtual ~IFile();
		virtual bool exist() = 0;
		virtual size_t size() = 0;
	};

	class IDirectory : public IDescryptor
	{
	public:
		virtual ~IDirectory();
		virtual bool exist() = 0;
		virtual size_t size() = 0;
		virtual IDescryptor& list() = 0;
	};

	class File : public IFile
	{
	public:
		virtual ~File();
		bool exist();
		size_t size();
	};

	class Directory : public IDirectory
	{
	public:
		virtual ~Directory();
		bool exist();
		size_t size();
		IDescryptor& list();
	};

	class Filesystem
	{
	public:
		static IDescryptor& open(const fs::path& p);
		static bool exist(const fs::path& p);
		static size_t size(const fs::path& p);
	};

	class File : public IFile
	{
	public:
		File(const fs::path& p) : path(p),
			size(Filesystem::file::size(p)),
			rhandle(std::ifstream(p, std::ios::binary)),
			whandle(std::ofstream(p, std::ios::binary)),
			readable(rhandle),
			writeble(whandle)
		{
			if (!Filesystem::file::exist(p))
				throw 1; // TODO: add error
		}
		void close() noexcept;
		std::vector<Byte> Read(size_t start_pos = 0, size_t bytes2read = 0);
		const size_t Size() const noexcept;
	private:
		std::ifstream rhandle;
		std::ofstream whandle;
		const bool readable;
		const bool writeble;
		const fs::path& path;
		const size_t size;
	};
}