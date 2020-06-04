#pragma once
#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class Filesystem
{
public:
	static size_t getFileSize(const fs::path& p);
	static bool isExist(const fs::path& p);
	static std::vector<std::byte> readFile(const fs::path& p, size_t start_pos = 0, size_t bytes2read = 0);
};

#endif