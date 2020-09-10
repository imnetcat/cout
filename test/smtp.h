#pragma once
#include "../core/config.h"
#ifdef INDEBUG
#include "../core/testing/module_test.h"
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