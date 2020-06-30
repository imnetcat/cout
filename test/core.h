#pragma once
#include "../core/testing/module_test.h"

#include "core/exceptions.h"
#include "core/logging.h"
#include "core/filesystem.h"
#ifdef INDEBUG	
using namespace Core::Testing;

ModuleTest CoreUnitTests = {
	"Core",
	{
		&FilesystemUnitTests,
		&LoggingUnitTests,
		&ExceptionssUnitTests
	}
};
#endif