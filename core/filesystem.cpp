#include "filesystem.h"
using namespace std;

bool Filesystem::isExist(const fs::path& p)
{
	fs::file_status s = fs::file_status{};
	return fs::status_known(s) ? fs::exists(s) : fs::exists(p);
}

size_t Filesystem::getFileSize(const fs::path& p)
{
	return fs::file_size(p);
}

vector<byte> Filesystem::readFile(const fs::path& p, size_t start_pos, size_t bytes2read)
{
	ifstream ifs(p, ios::binary | ios::ate);

	if (!ifs)
		throw runtime_error(strerror(errno));

	auto end = ifs.tellg();
	ifs.seekg(start_pos, ios::beg);

	size_t size = static_cast<size_t>(end - ifs.tellg());

	if (size == 0) // avoid undefined behavior 
		return {};

	vector<byte> buffer(size);
	if (!bytes2read)
		bytes2read = size;

	if (!ifs.read((char*)buffer.data(), bytes2read))
		throw runtime_error(strerror(errno));

	return buffer;
}