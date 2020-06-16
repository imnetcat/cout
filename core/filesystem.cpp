#include "filesystem.h"
using namespace std;
using namespace CORE;

bool Filesystem::file::exist(const fs::path& p)
{
	if (p.empty())
		throw invalid_argument("input empty path");
	fs::file_status s = fs::file_status{};
	return fs::status_known(s) ? fs::exists(s) : fs::exists(p);
}

size_t Filesystem::file::size(const fs::path& p)
{
	return fs::file_size(p);
}

File Filesystem::file::open(const fs::path& p)
{
	return File(p);
}

const size_t File::Size() const noexcept
{
	return size;
}

void File::close() noexcept
{
	rhandle.close();
	whandle.close();
}

vector<Byte> File::Read(size_t start_pos, size_t bytes2read)
{
	auto end = rhandle.tellg();
	rhandle.seekg(start_pos, ios::beg);
	
	if (!size) // avoid undefined behavior 
		// TODO: add error 
		throw 0;

	if (!bytes2read)
		bytes2read = size;

	vector<Byte> buffer(bytes2read);

	if (!rhandle.read(buffer.data(), bytes2read))
		// TODO: add error 
		throw 0;

	return buffer;
}