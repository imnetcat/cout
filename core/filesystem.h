#pragma once
#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_
#include <fstream>
#include <filesystem>
#include <vector>
namespace CORE
{
	namespace fs = std::filesystem;
	using Byte = char;

	class File;

	class Filesystem
	{
	public:
		struct file
		{
			static bool exist(const fs::path& p);
			static size_t size(const fs::path& p);
			static File open(const fs::path& p);
		};
	};

	class File
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
#endif