#pragma once
#include "../core/config.h"
#ifdef INDEBUG
#include "core.h"
#include "smtp.h"
using namespace Core::Testing;

ModuleTest UnitTests = {
	{
		&CoreUnitTests,
		&SMTPUnitTests
	}
};
#endif