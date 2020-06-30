#pragma once
#include "core.h"
#include "smtp.h"
#ifdef INDEBUG	
using namespace Core::Testing;

ModuleTest UnitTests = {
	"App",
	{
		&CoreUnitTests,
		&SMTPUnitTests
	}
};
#endif