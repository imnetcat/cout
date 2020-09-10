#pragma once
#include "../../src/core/config.h"
#ifdef INDEBUG
#include "../../src/network/smtpclient.h"
#include "../../src/network/protocol/smtp/exception.h"
#include "../../src/core/testing/assert.h"
#include "../../src/core/testing/module_test.h"
using namespace Cout::Core::Testing;
ModuleTest ClientUnitTests = {
	{
	new UnitTest([]()
		{
			Cout::Network::SMTPClient client;
			ASSERT_EQUAL(client.GetPassword(), "");
		}),
	new UnitTest([]()
		{
			Cout::Network::SMTPClient client;
			ASSERT_EQUAL(client.GetLogin(), "");
		}),
	new UnitTest([]()
		{
			Cout::Network::SMTPClient client;
			client.SetLogin("qwerty");
			ASSERT_EQUAL(client.GetLogin(), "qwerty");
		}),
	new UnitTest([]()
		{
			Cout::Network::SMTPClient client;
			client.SetPassword("password___");
			ASSERT_EQUAL(client.GetPassword(), "password___");
		}),
	new UnitTest([]()
		{
			Cout::Network::Protocol::SMTP::MAIL mail;
			Cout::Network::SMTPClient client;
			ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, client.Send(&mail));
		}),
	new UnitTest([]()
		{
			Cout::Network::Protocol::SMTP::MAIL mail;
			Cout::Network::SMTPClient client;
			mail.SetSenderMail("qwerty");
			ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, client.Send(&mail));
		}),
	}
};
#endif