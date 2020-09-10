#pragma once
#include "../../src/core/config.h"
#ifdef INDEBUG
#include "../../src/network/protocol/smtp/mail/mail.h"
#include "../../src/network/protocol/smtp/exception.h"
#include "../../src/core/testing/assert.h"
#include "../../src/core/testing/module_test.h"
using namespace Core::Testing;

ModuleTest MailUnitTests = {
	{
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				ASSERT_EQUAL(mail.GetSenderName(), "User");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("Another");
				ASSERT_EQUAL(mail.GetSenderName(), "Another");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("Another user");
				ASSERT_EQUAL(mail.GetSenderName(), "Another user");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("2136547");
				ASSERT_EQUAL(mail.GetSenderName(), "2136547");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName(" 23 - jm5 b 893 ks;'[p\\");
				ASSERT_EQUAL(mail.GetSenderName(), " 23 - jm5 b 893 ks;'[p\\");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName(" ");
				ASSERT_EQUAL(mail.GetSenderName(), " ");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("qwerty");
				ASSERT_EQUAL(mail.GetSenderName(), "qwerty");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName(" qwerty ");
				ASSERT_EQUAL(mail.GetSenderName(), " qwerty ");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("\\qwerty\\");
				ASSERT_EQUAL(mail.GetSenderName(), "\\qwerty\\");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("");
				ASSERT_EQUAL(mail.GetSenderName(), "");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("	");
				ASSERT_EQUAL(mail.GetSenderName(), "	");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				ASSERT_EQUAL(mail.GetSenderMail(), "User");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("Another");
				ASSERT_EQUAL(mail.GetSenderMail(), "Another");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("Another user");
				ASSERT_EQUAL(mail.GetSenderMail(), "Another user");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("2136547");
				ASSERT_EQUAL(mail.GetSenderMail(), "2136547");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail(" 23 - jm5 b 893 ks;'[p\\");
				ASSERT_EQUAL(mail.GetSenderMail(), " 23 - jm5 b 893 ks;'[p\\");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail(" ");
				ASSERT_EQUAL(mail.GetSenderMail(), " ");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("qwerty");
				ASSERT_EQUAL(mail.GetSenderMail(), "qwerty");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail(" qwerty ");
				ASSERT_EQUAL(mail.GetSenderMail(), " qwerty ");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("\\qwerty\\");
				ASSERT_EQUAL(mail.GetSenderMail(), "\\qwerty\\");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("");
				ASSERT_EQUAL(mail.GetSenderMail(), "");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("	");
				ASSERT_EQUAL(mail.GetSenderMail(), "	");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				ASSERT_EQUAL(mail.GetReplyTo(), "User");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("Another");
				ASSERT_EQUAL(mail.GetReplyTo(), "Another");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("Another user");
				ASSERT_EQUAL(mail.GetReplyTo(), "Another user");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("2136547");
				ASSERT_EQUAL(mail.GetReplyTo(), "2136547");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo(" 23 - jm5 b 893 ks;'[p\\");
				ASSERT_EQUAL(mail.GetReplyTo(), " 23 - jm5 b 893 ks;'[p\\");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo(" ");
				ASSERT_EQUAL(mail.GetReplyTo(), " ");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("qwerty");
				ASSERT_EQUAL(mail.GetReplyTo(), "qwerty");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo(" qwerty ");
				ASSERT_EQUAL(mail.GetReplyTo(), " qwerty ");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("\\qwerty\\");
				ASSERT_EQUAL(mail.GetReplyTo(), "\\qwerty\\");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("");
				ASSERT_EQUAL(mail.GetReplyTo(), "");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("	");
				ASSERT_EQUAL(mail.GetReplyTo(), "	");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				ASSERT_EQUAL(mail.GetSubject(), "User");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("Another");
				ASSERT_EQUAL(mail.GetSubject(), "Another");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("Another user");
				ASSERT_EQUAL(mail.GetSubject(), "Another user");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("2136547");
				ASSERT_EQUAL(mail.GetSubject(), "2136547");
				mail.SetSubject(" 23 - jm5 b 893 ks;'[p\\");
				ASSERT_EQUAL(mail.GetSubject(), " 23 - jm5 b 893 ks;'[p\\");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject(" ");
				ASSERT_EQUAL(mail.GetSubject(), " ");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("qwerty");
				ASSERT_EQUAL(mail.GetSubject(), "qwerty");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject(" qwerty ");
				ASSERT_EQUAL(mail.GetSubject(), " qwerty ");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("\\qwerty\\");
				ASSERT_EQUAL(mail.GetSubject(), "\\qwerty\\");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("");
				ASSERT_EQUAL(mail.GetSubject(), "");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("	");
				ASSERT_EQUAL(mail.GetSubject(), "	");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EQUAL(mail.GetRecipientCount(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				ASSERT_EQUAL(mail.GetRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, mail.AddRecipient("", ""));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, mail.AddRecipient("", "somename"));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;

				mail.AddRecipient("qwerty1", "09898987436");
				expected["qwerty1"] = "09898987436";
				ASSERT_EQUAL(mail.GetRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddRecipient("qwerty1", "qwerty");
				expected["qwerty1"] = "qwerty";
				mail.AddRecipient("qwerty1");
				expected["qwerty1"] = "";
				mail.AddRecipient("qwerty1");
				expected["qwerty1"] = "";
				ASSERT_EQUAL(mail.GetRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddRecipient("qwerty1");
				mail.AddRecipient("qwerty2");
				mail.AddRecipient("Another user 1");
				mail.AddRecipient("Another user 2");
				mail.AddRecipient("Another user 3", "qwerty1");
				mail.AddRecipient("Another user 4");
				mail.AddRecipient("  11 user ", "tyuiop[");
				mail.AddRecipient(" 234user");
				ASSERT_EQUAL(mail.GetRecipientCount(), 8);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;

				mail.AddRecipient("qwerty1");
				expected["qwerty1"] = "";
				mail.AddRecipient("qwerty2");
				expected["qwerty2"] = "";

				mail.AddRecipient("Another user 1", "some name");
				expected["Another user 1"] = "some name";

				mail.AddRecipient("Another user 2");
				expected["Another user 2"] = "";

				mail.AddRecipient("Another user 3");
				expected["Another user 3"] = "";

				mail.AddRecipient("Another user 4");
				expected["Another user 4"] = "";

				mail.AddRecipient("  11 user ");
				expected["  11 user "] = "";

				mail.AddRecipient(" 234user");
				expected[" 234user"] = "";
				ASSERT_EQUAL(mail.GetRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddRecipient("qwerty1");
				mail.AddRecipient("qwerty2");
				mail.AddRecipient("Another user 1", "Another user 1");
				mail.AddRecipient("Another user 2", "Another user 2");
				mail.AddRecipient("Another user 3");
				mail.AddRecipient("Another user 4");
				mail.AddRecipient("  11 user ");
				mail.AddRecipient(" 234user");
				ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, mail.AddRecipient(""));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EQUAL(mail.GetCCRecipientCount(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				ASSERT_EQUAL(mail.GetCCRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, mail.AddCCRecipient("", ""));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, mail.AddCCRecipient("", "somename"));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;

				mail.AddCCRecipient("qwerty1", "09898987436");
				expected["qwerty1"] = "09898987436";
				ASSERT_EQUAL(mail.GetCCRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddCCRecipient("qwerty1", "qwerty");
				expected["qwerty1"] = "qwerty";
				mail.AddCCRecipient("qwerty1");
				expected["qwerty1"] = "";
				mail.AddCCRecipient("qwerty1");
				expected["qwerty1"] = "";
				ASSERT_EQUAL(mail.GetCCRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddCCRecipient("qwerty1");
				mail.AddCCRecipient("qwerty2");
				mail.AddCCRecipient("Another user 1");
				mail.AddCCRecipient("Another user 2");
				mail.AddCCRecipient("Another user 3", "qwerty1");
				mail.AddCCRecipient("Another user 4");
				mail.AddCCRecipient("  11 user ", "tyuiop[");
				mail.AddCCRecipient(" 234user");
				ASSERT_EQUAL(mail.GetCCRecipientCount(), 8);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;

				mail.AddCCRecipient("qwerty1");
				expected["qwerty1"] = "";
				mail.AddCCRecipient("qwerty2");
				expected["qwerty2"] = "";

				mail.AddCCRecipient("Another user 1", "some name");
				expected["Another user 1"] = "some name";

				mail.AddCCRecipient("Another user 2");
				expected["Another user 2"] = "";

				mail.AddCCRecipient("Another user 3");
				expected["Another user 3"] = "";

				mail.AddCCRecipient("Another user 4");
				expected["Another user 4"] = "";

				mail.AddCCRecipient("  11 user ");
				expected["  11 user "] = "";

				mail.AddCCRecipient(" 234user");
				expected[" 234user"] = "";
				ASSERT_EQUAL(mail.GetCCRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddCCRecipient("qwerty1");
				mail.AddCCRecipient("qwerty2");
				mail.AddCCRecipient("Another user 1", "Another user 1");
				mail.AddCCRecipient("Another user 2", "Another user 2");
				mail.AddCCRecipient("Another user 3");
				mail.AddCCRecipient("Another user 4");
				mail.AddCCRecipient("  11 user ");
				mail.AddCCRecipient(" 234user");
				ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, mail.AddCCRecipient(""));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EQUAL(mail.GetBCCRecipientCount(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				ASSERT_EQUAL(mail.GetBCCRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, mail.AddBCCRecipient("", ""));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, mail.AddBCCRecipient("", "somename"));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;

				mail.AddBCCRecipient("qwerty1", "09898987436");
				expected["qwerty1"] = "09898987436";
				ASSERT_EQUAL(mail.GetBCCRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddBCCRecipient("qwerty1", "qwerty");
				expected["qwerty1"] = "qwerty";
				mail.AddBCCRecipient("qwerty1");
				expected["qwerty1"] = "";
				mail.AddBCCRecipient("qwerty1");
				expected["qwerty1"] = "";
				ASSERT_EQUAL(mail.GetBCCRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddBCCRecipient("qwerty1");
				mail.AddBCCRecipient("qwerty2");
				mail.AddBCCRecipient("Another user 1");
				mail.AddBCCRecipient("Another user 2");
				mail.AddBCCRecipient("Another user 3", "qwerty1");
				mail.AddBCCRecipient("Another user 4");
				mail.AddBCCRecipient("  11 user ", "tyuiop[");
				mail.AddBCCRecipient(" 234user");
				ASSERT_EQUAL(mail.GetBCCRecipientCount(), 8);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;

				mail.AddBCCRecipient("qwerty1");
				expected["qwerty1"] = "";
				mail.AddBCCRecipient("qwerty2");
				expected["qwerty2"] = "";

				mail.AddBCCRecipient("Another user 1", "some name");
				expected["Another user 1"] = "some name";

				mail.AddBCCRecipient("Another user 2");
				expected["Another user 2"] = "";

				mail.AddBCCRecipient("Another user 3");
				expected["Another user 3"] = "";

				mail.AddBCCRecipient("Another user 4");
				expected["Another user 4"] = "";

				mail.AddBCCRecipient("  11 user ");
				expected["  11 user "] = "";

				mail.AddBCCRecipient(" 234user");
				expected[" 234user"] = "";
				ASSERT_EQUAL(mail.GetBCCRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddBCCRecipient("qwerty1");
				mail.AddBCCRecipient("qwerty2");
				mail.AddBCCRecipient("Another user 1", "Another user 1");
				mail.AddBCCRecipient("Another user 2", "Another user 2");
				mail.AddBCCRecipient("Another user 3");
				mail.AddBCCRecipient("Another user 4");
				mail.AddBCCRecipient("  11 user ");
				mail.AddBCCRecipient(" 234user");
				ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, mail.AddBCCRecipient(""));
			}),

		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelRecipients();
				ASSERT_EQUAL(mail.GetRecipientCount(), 0);
			}), 
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelRecipients();
				mail.DelRecipients();
				mail.DelRecipients();
				ASSERT_EQUAL(mail.GetRecipientCount(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddRecipient("Another user 1");
				mail.AddRecipient("Another user 2");
				mail.AddRecipient("Another user 3", "qwerty1");
				mail.AddRecipient("Another user 4");
				mail.DelRecipients();
				ASSERT_EQUAL(mail.GetRecipientCount(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelCCRecipients();
				ASSERT_EQUAL(mail.GetCCRecipientCount(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelCCRecipients();
				mail.DelCCRecipients();
				mail.DelCCRecipients();
				ASSERT_EQUAL(mail.GetCCRecipientCount(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddCCRecipient("Another user 1");
				mail.AddCCRecipient("Another user 2");
				mail.AddCCRecipient("Another user 3", "qwerty1");
				mail.AddCCRecipient("Another user 4");
				mail.DelCCRecipients();
				ASSERT_EQUAL(mail.GetCCRecipientCount(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelBCCRecipients();
				ASSERT_EQUAL(mail.GetBCCRecipientCount(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelBCCRecipients();
				mail.DelBCCRecipients();
				mail.DelBCCRecipients();
				ASSERT_EQUAL(mail.GetBCCRecipientCount(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddBCCRecipient("Another user 1");
				mail.AddBCCRecipient("Another user 2");
				mail.AddBCCRecipient("Another user 3", "qwerty1");
				mail.AddBCCRecipient("Another user 4");
				mail.DelBCCRecipients();
				ASSERT_EQUAL(mail.GetBCCRecipientCount(), 0);
			}),

		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddRecipient("Another user 1");
				mail.DelRecipients();
				mail.AddRecipient("Another user 1", "Another user name 1");
				expected["Another user 1"] = "Another user name 1";
				ASSERT_EQUAL(mail.GetRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddRecipient("Another user 1");
				mail.AddRecipient("user 1", "user name 1");
				mail.AddRecipient("Another user 1");
				mail.AddRecipient("Another user 1");
				mail.AddRecipient("1");
				mail.AddRecipient("2");
				mail.AddRecipient("3");
				mail.AddRecipient("4");
				mail.AddRecipient("5");
				mail.AddRecipient("26");
				mail.DelRecipients();
				mail.AddRecipient("Another user 1");
				expected["Another user 1"] = "";
				ASSERT_EQUAL(mail.GetRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddRecipient("qwerty1");
				mail.AddRecipient("qwerty2");
				mail.AddRecipient("Another user 1");
				mail.AddRecipient("Another user 2");
				mail.AddRecipient("Another user 3");
				mail.AddRecipient("Another user 4");
				mail.AddRecipient("1");
				mail.AddRecipient("2");
				mail.AddRecipient("3");
				mail.AddRecipient("4");
				mail.AddRecipient("5");
				mail.AddRecipient("6");
				mail.AddRecipient("  11 user ");
				mail.AddRecipient(" 234user");
				mail.DelRecipients();
				mail.AddRecipient("Another user 1");
				mail.AddRecipient("Another user 2");
				mail.AddRecipient("Another user 3");
				mail.AddRecipient("Another user 4");
				mail.AddRecipient("5");
				mail.AddRecipient("6");
				ASSERT_EQUAL(mail.GetRecipientCount(), 6);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddRecipient("qwerty1");
				mail.AddRecipient("qwerty2");
				mail.AddRecipient("Another user 1");
				mail.AddRecipient("Another user 2");
				mail.AddRecipient("Another user 3");
				mail.AddRecipient("Another user 4");
				mail.AddRecipient("1");
				mail.AddRecipient("2");
				mail.AddRecipient("3");
				mail.AddRecipient("4");
				mail.AddRecipient("5");
				mail.AddRecipient("6");
				mail.AddRecipient("  11 user ");
				mail.AddRecipient(" 234user");
				mail.DelRecipients();
				mail.AddRecipient("Another user 1");
				mail.AddRecipient("Another user 2");
				mail.AddRecipient("Another user 3");
				mail.AddRecipient("Another user 4");
				mail.DelRecipients();
				mail.AddRecipient("5");
				mail.AddRecipient("6");
				ASSERT_EQUAL(mail.GetRecipientCount(), 2);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddRecipient("j pp OKIP{{P____ 00");
				mail.AddRecipient("     ");
				mail.AddRecipient("asd");
				mail.AddRecipient(" Another user 2");
				mail.AddRecipient("Another user 3 ");
				mail.AddRecipient("4");
				mail.AddRecipient("111111");
				mail.AddRecipient("22222");
				mail.DelRecipients();
				mail.AddRecipient("Another user 1");
				mail.AddRecipient("22222");
				mail.DelRecipients();
				ASSERT_EQUAL(mail.GetRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddCCRecipient("Another user 1");
				mail.DelCCRecipients();
				mail.AddCCRecipient("Another user 1", "Another user name 1");
				expected["Another user 1"] = "Another user name 1";
				ASSERT_EQUAL(mail.GetCCRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddCCRecipient("Another user 1");
				mail.AddCCRecipient("user 1", "user name 1");
				mail.AddCCRecipient("Another user 1");
				mail.AddCCRecipient("Another user 1");
				mail.AddCCRecipient("1");
				mail.AddCCRecipient("2");
				mail.AddCCRecipient("3");
				mail.AddCCRecipient("4");
				mail.AddCCRecipient("5");
				mail.AddCCRecipient("26");
				mail.DelCCRecipients();
				mail.AddCCRecipient("Another user 1");
				expected["Another user 1"] = "";
				ASSERT_EQUAL(mail.GetCCRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddCCRecipient("qwerty1");
				mail.AddCCRecipient("qwerty2");
				mail.AddCCRecipient("Another user 1");
				mail.AddCCRecipient("Another user 2");
				mail.AddCCRecipient("Another user 3");
				mail.AddCCRecipient("Another user 4");
				mail.AddCCRecipient("1");
				mail.AddCCRecipient("2");
				mail.AddCCRecipient("3");
				mail.AddCCRecipient("4");
				mail.AddCCRecipient("5");
				mail.AddCCRecipient("6");
				mail.AddCCRecipient("  11 user ");
				mail.AddCCRecipient(" 234user");
				mail.DelCCRecipients();
				mail.AddCCRecipient("Another user 1");
				mail.AddCCRecipient("Another user 2");
				mail.AddCCRecipient("Another user 3");
				mail.AddCCRecipient("Another user 4");
				mail.AddCCRecipient("5");
				mail.AddCCRecipient("6");
				ASSERT_EQUAL(mail.GetCCRecipientCount(), 6);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddCCRecipient("qwerty1");
				mail.AddCCRecipient("qwerty2");
				mail.AddCCRecipient("Another user 1");
				mail.AddCCRecipient("Another user 2");
				mail.AddCCRecipient("Another user 3");
				mail.AddCCRecipient("Another user 4");
				mail.AddCCRecipient("1");
				mail.AddCCRecipient("2");
				mail.AddCCRecipient("3");
				mail.AddCCRecipient("4");
				mail.AddCCRecipient("5");
				mail.AddCCRecipient("6");
				mail.AddCCRecipient("  11 user ");
				mail.AddCCRecipient(" 234user");
				mail.DelCCRecipients();
				mail.AddCCRecipient("Another user 1");
				mail.AddCCRecipient("Another user 2");
				mail.AddCCRecipient("Another user 3");
				mail.AddCCRecipient("Another user 4");
				mail.DelCCRecipients();
				mail.AddCCRecipient("5");
				mail.AddCCRecipient("6");
				ASSERT_EQUAL(mail.GetCCRecipientCount(), 2);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddCCRecipient("j pp OKIP{{P____ 00");
				mail.AddCCRecipient("     ");
				mail.AddCCRecipient("asd");
				mail.AddCCRecipient(" Another user 2");
				mail.AddCCRecipient("Another user 3 ");
				mail.AddCCRecipient("4");
				mail.AddCCRecipient("111111");
				mail.AddCCRecipient("22222");
				mail.DelCCRecipients();
				mail.AddCCRecipient("Another user 1");
				mail.AddCCRecipient("22222");
				mail.DelCCRecipients();
				ASSERT_EQUAL(mail.GetCCRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddBCCRecipient("Another user 1");
				mail.DelBCCRecipients();
				mail.AddBCCRecipient("Another user 1", "Another user name 1");
				expected["Another user 1"] = "Another user name 1";
				ASSERT_EQUAL(mail.GetBCCRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddBCCRecipient("Another user 1");
				mail.AddBCCRecipient("user 1", "user name 1");
				mail.AddBCCRecipient("Another user 1");
				mail.AddBCCRecipient("Another user 1");
				mail.AddBCCRecipient("1");
				mail.AddBCCRecipient("2");
				mail.AddBCCRecipient("3");
				mail.AddBCCRecipient("4");
				mail.AddBCCRecipient("5");
				mail.AddBCCRecipient("26");
				mail.DelBCCRecipients();
				mail.AddBCCRecipient("Another user 1");
				expected["Another user 1"] = "";
				ASSERT_EQUAL(mail.GetBCCRecipient(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddBCCRecipient("qwerty1");
				mail.AddBCCRecipient("qwerty2");
				mail.AddBCCRecipient("Another user 1");
				mail.AddBCCRecipient("Another user 2");
				mail.AddBCCRecipient("Another user 3");
				mail.AddBCCRecipient("Another user 4");
				mail.AddBCCRecipient("1");
				mail.AddBCCRecipient("2");
				mail.AddBCCRecipient("3");
				mail.AddBCCRecipient("4");
				mail.AddBCCRecipient("5");
				mail.AddBCCRecipient("6");
				mail.AddBCCRecipient("  11 user ");
				mail.AddBCCRecipient(" 234user");
				mail.DelBCCRecipients();
				mail.AddBCCRecipient("Another user 1");
				mail.AddBCCRecipient("Another user 2");
				mail.AddBCCRecipient("Another user 3");
				mail.AddBCCRecipient("Another user 4");
				mail.AddBCCRecipient("5");
				mail.AddBCCRecipient("6");
				ASSERT_EQUAL(mail.GetBCCRecipientCount(), 6);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddBCCRecipient("qwerty1");
				mail.AddBCCRecipient("qwerty2");
				mail.AddBCCRecipient("Another user 1");
				mail.AddBCCRecipient("Another user 2");
				mail.AddBCCRecipient("Another user 3");
				mail.AddBCCRecipient("Another user 4");
				mail.AddBCCRecipient("1");
				mail.AddBCCRecipient("2");
				mail.AddBCCRecipient("3");
				mail.AddBCCRecipient("4");
				mail.AddBCCRecipient("5");
				mail.AddBCCRecipient("6");
				mail.AddBCCRecipient("  11 user ");
				mail.AddBCCRecipient(" 234user");
				mail.DelBCCRecipients();
				mail.AddBCCRecipient("Another user 1");
				mail.AddBCCRecipient("Another user 2");
				mail.AddBCCRecipient("Another user 3");
				mail.AddBCCRecipient("Another user 4");
				mail.DelBCCRecipients();
				mail.AddBCCRecipient("5");
				mail.AddBCCRecipient("6");
				ASSERT_EQUAL(mail.GetBCCRecipientCount(), 2);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddBCCRecipient("j pp OKIP{{P____ 00");
				mail.AddBCCRecipient("     ");
				mail.AddBCCRecipient("asd");
				mail.AddBCCRecipient(" Another user 2");
				mail.AddBCCRecipient("Another user 3 ");
				mail.AddBCCRecipient("4");
				mail.AddBCCRecipient("111111");
				mail.AddBCCRecipient("22222");
				mail.DelBCCRecipients();
				mail.AddBCCRecipient("Another user 1");
				mail.AddBCCRecipient("22222");
				mail.DelBCCRecipients();
				ASSERT_EQUAL(mail.GetBCCRecipient(), expected);
			}),


		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EQUAL(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EQUAL(mail.GetXMailer(), Protocol::SMTP::XMAILER);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				ASSERT_EQUAL(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::HIGH);
				ASSERT_EQUAL(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::HIGH);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::LOW);
				ASSERT_EQUAL(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::LOW);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				ASSERT_EQUAL(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::LOW);
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::LOW);
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				ASSERT_EQUAL(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				mail.SetXPriority();
				ASSERT_EQUAL(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL);
			}),

		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXMailer("AopjopjsG9d04k;SDg=-3dsgDS");
				ASSERT_EQUAL(mail.GetXMailer(), "AopjopjsG9d04k;SDg=-3dsgDS");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXMailer("AopjopjsG9d04k;SDg=-3dsgDS");
				mail.SetXMailer("");
				ASSERT_EQUAL(mail.GetXMailer(), "");
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXMailer("AopjopjsG9d04k;SDg=-3dsgDS");
				mail.SetXMailer("");
				mail.SetXMailer("1234568752457780957");
				mail.SetXMailer("IAhjio34   sad0-9 3");
				mail.SetXMailer("42j90,m9a 90as");
				mail.SetXMailer("=--(_io3;k2os89)&9sa");
				ASSERT_EQUAL(mail.GetXMailer(), "=--(_io3;k2os89)&9sa");
			}),

		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EQUAL(mail.GetBodySize(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddMsgLine("Hello,");
				mail.AddMsgLine("");
				mail.AddMsgLine("...");
				mail.AddMsgLine("How are you today?");
				mail.AddMsgLine("");
				mail.AddMsgLine("Regards");
				ASSERT_EQUAL(mail.GetBodySize(), 6);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.AddMsgLine("Hello,");
				expected.push_back("Hello,");
				mail.AddMsgLine("");
				expected.push_back("");
				mail.AddMsgLine("...");
				expected.push_back("...");
				mail.AddMsgLine("How are you today?");
				expected.push_back("How are you today?");
				mail.AddMsgLine("");
				expected.push_back("");
				mail.AddMsgLine("Regards");
				expected.push_back("Regards");
				ASSERT_EQUAL(mail.GetBody(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.AddMsgLine("");
				expected.push_back("");
				mail.AddMsgLine("");
				expected.push_back("");
				mail.AddMsgLine("                    ");
				expected.push_back("                    ");
				mail.AddMsgLine(" ");
				expected.push_back(" ");
				mail.AddMsgLine("");
				expected.push_back("");
				mail.AddMsgLine("              24h8340-cre23fsw-          ");
				expected.push_back("              24h8340-cre23fsw-          ");
				ASSERT_EQUAL(mail.GetBody(), expected);
			}),

		new UnitTest([]() {
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.AddMsgLine("Hello,");
				expected.push_back("Hello,");
				ASSERT_EXCEPTION(Exceptions::Core::out_of_range, mail.ModMsgLine(1, ""));
		}),
		new UnitTest([]() {
				Protocol::SMTP::MAIL mail;
				ASSERT_EXCEPTION(Exceptions::Core::out_of_range, mail.ModMsgLine(-9, " y54 zay5 8569"));
		}),
		new UnitTest([]() {
				Protocol::SMTP::MAIL mail;
				ASSERT_EXCEPTION(Exceptions::Core::out_of_range, mail.ModMsgLine(567, "46346174"));
		}),
		new UnitTest([]() {
				Protocol::SMTP::MAIL mail;
				ASSERT_EXCEPTION(Exceptions::Core::out_of_range, mail.ModMsgLine(-4577, "wsr sh"));
			}),
		new UnitTest([]() {
				Protocol::SMTP::MAIL mail;
				ASSERT_EXCEPTION(Exceptions::Core::out_of_range, mail.ModMsgLine(0, ""));
			}),
		new UnitTest([]() {
				Protocol::SMTP::MAIL mail;
				ASSERT_EXCEPTION(Exceptions::Core::out_of_range, mail.ModMsgLine(-1, "rty"));
			}),
		new UnitTest([]() {
				Protocol::SMTP::MAIL mail; 
				mail.AddMsgLine("Hello,");
				mail.ModMsgLine(0, "Hey hey heeeeeeey,");
				mail.AddMsgLine("");
				mail.AddMsgLine("...");
				mail.AddMsgLine("How are you today?");
				mail.AddMsgLine("");
				mail.ModMsgLine(4, "empty line");
				mail.AddMsgLine("Regards");
				mail.ModMsgLine(5, "regards");
				ASSERT_EXCEPTION(Exceptions::Core::out_of_range, mail.ModMsgLine(-1, "rty"));
			}),
		new UnitTest([]() {
				Protocol::SMTP::MAIL mail;
				mail.AddMsgLine("Hello,");
				mail.ModMsgLine(0, "Hey hey heeeeeeey,");
				mail.AddMsgLine("");
				mail.AddMsgLine("...");
				mail.AddMsgLine("How are you today?");
				mail.AddMsgLine("");
				mail.ModMsgLine(4, "empty line");
				mail.AddMsgLine("Regards");
				mail.ModMsgLine(5, "regards");
				ASSERT_EXCEPTION(Exceptions::Core::out_of_range, mail.ModMsgLine(55, "try to modify"));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.AddMsgLine("Hello,");
				expected.push_back("Hello,");
				mail.ModMsgLine(0, "Hey hey heeeeeeey,");
				expected[0] = "Hey hey heeeeeeey,";
				mail.AddMsgLine("");
				expected.push_back("");
				mail.AddMsgLine("...");
				expected.push_back("...");
				mail.AddMsgLine("How are you today?");
				expected.push_back("How are you today?");
				mail.AddMsgLine("");
				expected.push_back("");
				mail.ModMsgLine(4, "empty line");
				expected[4] = "empty line";
				mail.AddMsgLine("Regards");
				expected.push_back("Regards");
				mail.ModMsgLine(5, "regards");
				expected[5] = "regards";
				ASSERT_EQUAL(mail.GetBody(), expected);
			}),

		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				ASSERT_EXCEPTION(Exceptions::Core::out_of_range, mail.DelMsgLine(-1));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				ASSERT_EXCEPTION(Exceptions::Core::out_of_range, mail.DelMsgLine(0));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				ASSERT_EXCEPTION(Exceptions::Core::out_of_range, mail.DelMsgLine(-72865));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				ASSERT_EXCEPTION(Exceptions::Core::out_of_range, mail.DelMsgLine(72865));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.AddMsgLine("Hello,");
				expected.push_back("Hello,");
				mail.ModMsgLine(0, "Hey hey heeeeeeey,");
				expected[0] = "Hey hey heeeeeeey,";
				mail.DelMsgLine(0);
				expected.erase(expected.begin());
				mail.AddMsgLine("");
				expected.push_back("");
				mail.DelMsgLine(0);
				expected.erase(expected.begin());
				mail.AddMsgLine("...");
				expected.push_back("...");
				mail.AddMsgLine("How are you today?");
				expected.push_back("How are you today?");
				mail.AddMsgLine("");
				expected.push_back("");
				mail.ModMsgLine(2, "empty line");
				expected[2] = "empty line";
				mail.AddMsgLine("Regards");
				expected.push_back("Regards");
				mail.ModMsgLine(3, "regards");
				expected[3] = "regards";
				mail.DelMsgLine(0);
				expected.erase(expected.begin());
				mail.DelMsgLine(1);
				expected.erase(expected.begin() + 1);
				ASSERT_EQUAL(mail.GetBody(), expected);
			}),

		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.DelMsgLines();
				mail.DelMsgLines();
				mail.DelMsgLines();
				ASSERT_EQUAL(mail.GetBody(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.AddMsgLine("Hello,");
				mail.AddMsgLine("...");
				mail.AddMsgLine("...");
				mail.AddMsgLine("...");
				mail.AddMsgLine("...");

				mail.DelMsgLines();
				ASSERT_EQUAL(mail.GetBody(), expected);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.AddMsgLine("Hello,");
				mail.ModMsgLine(0, "Hey hey heeeeeeey,");
				mail.DelMsgLine(0);
				mail.AddMsgLine("");
				mail.DelMsgLine(0);
				mail.AddMsgLine("...");
				mail.AddMsgLine("How are you today?");
				mail.AddMsgLine("");
				mail.ModMsgLine(2, "empty line");
				mail.AddMsgLine("Regards");
				mail.ModMsgLine(3, "regards");
				mail.DelMsgLine(0);
				mail.DelMsgLine(1);

				mail.DelMsgLines();

				mail.AddMsgLine("regards");
				mail.AddMsgLine("regards");

				mail.DelMsgLines();
				ASSERT_EQUAL(mail.GetBody(), expected);
			}),

		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EQUAL(mail.GetAttachmentsSize(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, mail.AddAttachment(""));
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddAttachment("./test/files/7.jpg");
				mail.AddAttachment("./test/files/8.jpg");
				mail.AddAttachment("./test/files/9.png");
				ASSERT_EQUAL(mail.GetAttachmentsSize(), 3);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddAttachment("./test/files/7.jpg");
				mail.AddAttachment("./test/files/8.jpg");
				mail.AddAttachment("./test/files/9.png");
				mail.AddAttachment("./test/files/simple text.txt");
				mail.AddAttachment("./test/files/24.txt");
				mail.AddAttachment("./test/files/19_23.zip");
				ASSERT_EXCEPTION(Exceptions::Core::invalid_argument, mail.AddAttachment(""));
			}),

		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelAttachments();
				mail.DelAttachments();
				mail.DelAttachments();
				mail.DelAttachments();
				ASSERT_EQUAL(mail.GetAttachmentsSize(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddAttachment("./test/files/7.jpg");
				mail.AddAttachment("./test/files/8.jpg");
				mail.AddAttachment("./test/files/9.png");
				mail.DelAttachments();
				ASSERT_EQUAL(mail.GetAttachmentsSize(), 0);
			}),
		new UnitTest([]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddAttachment("./test/files/7.jpg");
				mail.AddAttachment("./test/files/8.jpg");
				mail.AddAttachment("./test/files/9.png");
				mail.AddAttachment("./test/files/simple text.txt");
				mail.AddAttachment("./test/files/24.txt");
				mail.AddAttachment("./test/files/19_23.zip");
				mail.DelAttachments();
				mail.AddAttachment("./test/files/simple text.txt");
				mail.AddAttachment("./test/files/24.txt");
				mail.AddAttachment("./test/files/19_23.zip");
				mail.DelAttachments();
				ASSERT_EQUAL(mail.GetAttachmentsSize(), 0);
			}),
	}
};
#endif