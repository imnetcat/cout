#pragma once
#include "../core/config.h"
#ifdef INDEBUG
#include "../core/testing/module_test.h"

#include "core/exceptions.h"
#include "core/logging.h"
#include "core/filesystem.h"
using namespace Core::Testing;

ModuleTest CoreUnitTests = {
	{
		&FilesystemUnitTests,
		&LoggingUnitTests,
		&ExceptionssUnitTests
	}
};
#endif