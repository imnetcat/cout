#pragma once
#include <filesystem>
namespace Cout
{
	namespace Core
	{
		namespace Filesystem
		{
			namespace fs = std::filesystem;
			using Path = fs::path;
		}
	}
}