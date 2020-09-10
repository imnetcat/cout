#pragma once
#include <filesystem>
namespace Core
{
	namespace Filesystem
	{
		namespace fs = std::filesystem;
		using Path = fs::path;
	}
}