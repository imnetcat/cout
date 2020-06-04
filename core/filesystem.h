#pragma once
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class Filesystem
{
public:
	static size_t getFileSize(const fs::path& p);
	static bool isExist(const fs::path& p);
	static vector<byte> readFile(const fs::path& p, size_t start_pos = 0, size_t bytes2read = 0);
};
