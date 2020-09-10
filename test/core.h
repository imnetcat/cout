#pragma once
#include "../src/core/config.h"
#ifdef INDEBUG
#include "../src/core/testing/module_test.h"

#include "core/exceptions.h"
#include "core/logging.h"
#include "core/filesystem.h"
using namespace Cout::Core::Testing;

ModuleTest CoreUnitTests = {
	{
		&FilesystemUnitTests,
		&LoggingUnitTests,
		&ExceptionssUnitTests
	}
};
#endif