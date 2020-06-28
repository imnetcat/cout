#include "dir.h"
using namespace std;

Core::Filesystem::Dir::Dir(const Path& p) :
	CopyableDir(p),
	MoveableDir(p),
	DirDescryptor(p) {}
