#ifndef _TEST_SMTP_H_
#define _TEST_SMTP_H_
#include "../core/testing/module_test.h"

#include "smtp/mail.h"
#include "smtp/client.h"
#ifdef INDEBUG	
using namespace Core::Testing;

ModuleTest SMTPUnitTests = {
	"SMTP",
	{
		&MailUnitTests,
		&ClientUnitTests
	}
};
#endif
#endif