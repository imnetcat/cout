#pragma once
#include "../core/testing/module_test.h"
#include "../core/testing/assert.h"

#include "core/exceptions.h"
#include "core/logging.h"
#include "core/filesystem.h"
using namespace Core::Testing;

ModuleTest CoreUnitTests = {
	"Core",
	{
		&FilesystemUnitTests,
		&LoggingUnitTests,
		&ExceptionsUnitTests
	}
};
