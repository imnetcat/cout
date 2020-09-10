#pragma once
#include "../src/core/config.h"
#ifdef INDEBUG
#include "../src/core/testing/module_test.h"
#include "smtp/mail.h"
#include "smtp/client.h"
using namespace Core::Testing;

ModuleTest SMTPUnitTests = {
	{
		&MailUnitTests,
		&ClientUnitTests
	}
};
#endif