#pragma once
#include "core.h"
#include "smtp.h"
using namespace Core::Testing;

ModuleTest UnitTests = {
	"App",
	{
		&CoreUnitTests,
		&SMTPUnitTests
	}
};
