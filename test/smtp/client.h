#pragma once
#include "../../src/core/config.h"
#ifdef INDEBUG
#include "../../src/network/smtpclient.h"
#include "../../src/network/protocol/smtp/exception.h"
#include "../../src/core/testing/assert.h"
#include "../../src/core/testing/module_test.h"
using namespace Core::Testing;
ModuleTest ClientUnitTests = {
	{
	new UnitTest([]()
		{
			Protocol::SMTP::Client client;
			ASSERT_EQUAL(client.GetPassword(), "");
		}),
	new UnitTest([]()
		{
			Protocol::SMTP::Client client;
			ASSERT_EQUAL(client.GetLogin(), "");
		}),
	new UnitTest([]()
		{
			Protocol::SMTP::Client client;
			client.SetLogin("qwerty");
			ASSERT_EQUAL(client.GetLogin(), "qwerty");
		}),
	new UnitTest([]()
		{
			Protocol::SMTP::Client client;
			client.SetPassword("password___");
			ASSERT_EQUAL(client.GetPassword(), "password___");
		}),
	new UnitTest([]()
		{
			Protocol::SMTP::MAIL mail;
			Protocol::SMTP::Client client;
			ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, client.Send(&mail));
		}),
	new UnitTest([]()
		{
			Protocol::SMTP::MAIL mail;
			Protocol::SMTP::Client client;
			mail.SetSenderMail("qwerty");
			ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, client.Send(&mail));
		}),
	}
};
#endif