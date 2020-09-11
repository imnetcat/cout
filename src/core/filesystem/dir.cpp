#include "dir.h"
Cout::Core::Filesystem::Dir::Dir(const Path& p) :
	CopyableDir(p),
	MoveableDir(p),
	DirDescryptor(p) {}
