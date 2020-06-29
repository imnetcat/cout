#ifndef _TEST_SMTP_CLIENT_H_
#define _TEST_SMTP_CLIENT_H_
#include "../../protocol/smtp/client.h"
#include "../../protocol/smtp/exceptions.h"
#include "../../core/testing/assert.h"
#include "../../core/testing/module_test.h"
using namespace Core::Testing;
ModuleTest ClientUnitTests = {
	"Client",
	{
	new unit_equal("password empty by default", []()
		{
			Protocol::SMTP::Client client;
			return AssertEqual(client.GetPassword(), "");
		}),
	new unit_equal("login empty by default", []()
		{
			Protocol::SMTP::Client client;
			return AssertEqual(client.GetLogin(), "");
		}),
	new unit_equal("set up login", []()
		{
			Protocol::SMTP::Client client;
			client.SetLogin("qwerty");
			return AssertEqual(client.GetLogin(), "qwerty");
		}),
	new unit_equal("set up passwd", []()
		{
			Protocol::SMTP::Client client;
			client.SetPassword("password___");
			return AssertEqual(client.GetPassword(), "password___");
		}),
	new unit_exception("try to sending a mail without sender address", 
		Exceptions::Core::invalid_argument("sender not specified"), []()
		{
			Protocol::SMTP::MAIL mail;
			Protocol::SMTP::Client client;
			client.Send(&mail);
		}),
	new unit_exception("try to sending a mail without receiver",
		Exceptions::Core::invalid_argument("receiver not specified"), []()
		{
			Protocol::SMTP::MAIL mail;
			Protocol::SMTP::Client client;
			mail.SetSenderMail("qwerty");
			client.Send(&mail);
		}),
	}
};
#endif