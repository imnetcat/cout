#pragma once
#include "../src/core/config.h"
#ifdef INDEBUG
#include "../src/core/testing/test.h"
#include "core.h"
#include "smtp.h"
using namespace Cout::Core::Testing;

ModuleTest UnitTests = {
	{
		&CoreUnitTests,
		&SMTPUnitTests
	}
};
#endif