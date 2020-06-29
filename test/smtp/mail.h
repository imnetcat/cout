#pragma once
#ifndef _TEST_EMAIL_H_
#define _TEST_EMAIL_H_
#include "../../protocol/smtp/client.h"
#include "../../protocol/smtp/exceptions.h"
#include "../../core/testing/assert.h"
#include "../../core/testing/module_test.h"
using namespace Core::Testing;

ModuleTest MailUnitTests = {
	"Mail", {
		new unit_equal("set up sender name", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				return AssertEqual(mail.GetSenderName(), "User");
			}),
		new unit_equal("change sender name 1", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("Another");
				return AssertEqual(mail.GetSenderName(), "Another");
			}),
		new unit_equal("change sender name 2", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("Another user");
				return AssertEqual(mail.GetSenderName(), "Another user");
			}),
		new unit_equal("change sender name 3", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("2136547");
				return AssertEqual(mail.GetSenderName(), "2136547");
			}),
		new unit_equal("change sender name 4", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName(" 23 - jm5 b 893 ks;'[p\\");
				return AssertEqual(mail.GetSenderName(), " 23 - jm5 b 893 ks;'[p\\");
			}),
		new unit_equal("change sender name 5", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName(" ");
				return AssertEqual(mail.GetSenderName(), " ");
			}),
		new unit_equal("change sender name 6", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("qwerty");
				return AssertEqual(mail.GetSenderName(), "qwerty");
			}),
		new unit_equal("change sender name 7", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName(" qwerty ");
				return AssertEqual(mail.GetSenderName(), " qwerty ");
			}),
		new unit_equal("change sender name 8", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("\\qwerty\\");
				return AssertEqual(mail.GetSenderName(), "\\qwerty\\");
			}),
		new unit_equal("change sender name 9", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("");
				return AssertEqual(mail.GetSenderName(), "");
			}),
		new unit_equal("change sender name 10", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderName("User");
				mail.SetSenderName("	");
				return AssertEqual(mail.GetSenderName(), "	");
			}),
		new unit_equal("set up sender mail", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				return AssertEqual(mail.GetSenderMail(), "User");
			}),
		new unit_equal("change sender mail 1", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("Another");
				return AssertEqual(mail.GetSenderMail(), "Another");
			}),
		new unit_equal("change sender mail 2", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("Another user");
				return AssertEqual(mail.GetSenderMail(), "Another user");
			}),
		new unit_equal("change sender mail 3", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("2136547");
				return AssertEqual(mail.GetSenderMail(), "2136547");
			}),
		new unit_equal("change sender mail 4", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail(" 23 - jm5 b 893 ks;'[p\\");
				return AssertEqual(mail.GetSenderMail(), " 23 - jm5 b 893 ks;'[p\\");
			}),
		new unit_equal("change sender mail 5", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail(" ");
				return AssertEqual(mail.GetSenderMail(), " ");
			}),
		new unit_equal("change sender mail 6", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("qwerty");
				return AssertEqual(mail.GetSenderMail(), "qwerty");
			}),
		new unit_equal("change sender mail 7", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail(" qwerty ");
				return AssertEqual(mail.GetSenderMail(), " qwerty ");
			}),
		new unit_equal("change sender mail 8", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("\\qwerty\\");
				return AssertEqual(mail.GetSenderMail(), "\\qwerty\\");
			}),
		new unit_equal("change sender mail 9", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("");
				return AssertEqual(mail.GetSenderMail(), "");
			}),
		new unit_equal("change sender mail 10", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSenderMail("User");
				mail.SetSenderMail("	");
				return AssertEqual(mail.GetSenderMail(), "	");
			}),
		new unit_equal("set up reply to", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				return AssertEqual(mail.GetReplyTo(), "User");
			}),
		new unit_equal("change reply to 1", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("Another");
				return AssertEqual(mail.GetReplyTo(), "Another");
			}),
		new unit_equal("change reply to 2", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("Another user");
				return AssertEqual(mail.GetReplyTo(), "Another user");
			}),
		new unit_equal("change reply to 3", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("2136547");
				return AssertEqual(mail.GetReplyTo(), "2136547");
			}),
		new unit_equal("change reply to 4", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo(" 23 - jm5 b 893 ks;'[p\\");
				return AssertEqual(mail.GetReplyTo(), " 23 - jm5 b 893 ks;'[p\\");
			}),
		new unit_equal("change reply to 5", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo(" ");
				return AssertEqual(mail.GetReplyTo(), " ");
			}),
		new unit_equal("change reply to 6", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("qwerty");
				return AssertEqual(mail.GetReplyTo(), "qwerty");
			}),
		new unit_equal("change reply to 7", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo(" qwerty ");
				return AssertEqual(mail.GetReplyTo(), " qwerty ");
			}),
		new unit_equal("change reply to 8", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("\\qwerty\\");
				return AssertEqual(mail.GetReplyTo(), "\\qwerty\\");
			}),
		new unit_equal("change reply to 9", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("");
				return AssertEqual(mail.GetReplyTo(), "");
			}),
		new unit_equal("change reply to 10", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetReplyTo("User");
				mail.SetReplyTo("	");
				return AssertEqual(mail.GetReplyTo(), "	");
			}),
		new unit_equal("set up subject", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				return AssertEqual(mail.GetSubject(), "User");
			}),
		new unit_equal("change subject 1", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("Another");
				return AssertEqual(mail.GetSubject(), "Another");
			}),
		new unit_equal("change subject 2", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("Another user");
				return AssertEqual(mail.GetSubject(), "Another user");
			}),
		new unit_equal("change subject 3", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("2136547");
				return AssertEqual(mail.GetSubject(), "2136547");
				mail.SetSubject(" 23 - jm5 b 893 ks;'[p\\");
				return AssertEqual(mail.GetSubject(), " 23 - jm5 b 893 ks;'[p\\");
			}),
		new unit_equal("change subject 4", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject(" ");
				return AssertEqual(mail.GetSubject(), " ");
			}),
		new unit_equal("change subject 5", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("qwerty");
				return AssertEqual(mail.GetSubject(), "qwerty");
			}),
		new unit_equal("change subject 6", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject(" qwerty ");
				return AssertEqual(mail.GetSubject(), " qwerty ");
			}),
		new unit_equal("change subject 7", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("\\qwerty\\");
				return AssertEqual(mail.GetSubject(), "\\qwerty\\");
			}),
		new unit_equal("change subject 8", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("");
				return AssertEqual(mail.GetSubject(), "");
			}),
		new unit_equal("change subject 9", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetSubject("User");
				mail.SetSubject("	");
				return AssertEqual(mail.GetSubject(), "	");
			}),
		new unit_equal("mail recipient count zero by default", []()
			{
				Protocol::SMTP::MAIL mail;
				return AssertEqual(mail.GetRecipientCount(), 0);
			}),
		new unit_equal("mail recipient list empty by default", []()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				return AssertEqual(mail.GetRecipient(), expected);
			}),
		new unit_exception("add recipient with empty email and name", 
			Exceptions::Core::invalid_argument("recipient email is empty"),
			[]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddRecipient("", "");
			}),
		new unit_exception("add recipient with empty email",
			Exceptions::Core::invalid_argument("recipient email is empty"),
			[]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddRecipient("", "somename");
			}),
		new unit_equal("set first recipient", []()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;

				mail.AddRecipient("qwerty1", "09898987436");
				expected["qwerty1"] = "09898987436";
				return AssertEqual(mail.GetRecipient(), expected);
			}),
		new unit_equal("add existed recipient does not change the list", []()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddRecipient("qwerty1", "qwerty");
				expected["qwerty1"] = "qwerty";
				mail.AddRecipient("qwerty1");
				expected["qwerty1"] = "";
				mail.AddRecipient("qwerty1");
				expected["qwerty1"] = "";
				return AssertEqual(mail.GetRecipient(), expected);
			}),
		new unit_equal("add recipients and then count it", []()
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
				return AssertEqual(mail.GetRecipientCount(), 8);
			}),
		new unit_equal("add recipients and then check it", []()
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
				return AssertEqual(mail.GetRecipient(), expected);
			}),
		new unit_exception("add recipients and then add empty recipient",
			Exceptions::Core::invalid_argument("recipient email is empty"),
			[]()
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
				mail.AddRecipient("");
			}),
		new unit_equal("mail ccrecipient count zero by default", []()
			{
				Protocol::SMTP::MAIL mail;
				return AssertEqual(mail.GetCCRecipientCount(), 0);
			}),
		new unit_equal("mail ccrecipient list empty by default", []()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				return AssertEqual(mail.GetCCRecipient(), expected);
			}),
		new unit_exception("add ccrecipient with empty email and name",
			Exceptions::Core::invalid_argument("recipient email is empty"),
			[]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddCCRecipient("", "");
			}),
		new unit_exception("add ccrecipient with empty email",
			Exceptions::Core::invalid_argument("recipient email is empty"),
			[]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddCCRecipient("", "somename");
			}),
		new unit_equal("set first ccrecipient", []()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;

				mail.AddCCRecipient("qwerty1", "09898987436");
				expected["qwerty1"] = "09898987436";
				return AssertEqual(mail.GetCCRecipient(), expected);
			}),
		new unit_equal("add existed ccrecipient does not change the list", []()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddCCRecipient("qwerty1", "qwerty");
				expected["qwerty1"] = "qwerty";
				mail.AddCCRecipient("qwerty1");
				expected["qwerty1"] = "";
				mail.AddCCRecipient("qwerty1");
				expected["qwerty1"] = "";
				return AssertEqual(mail.GetCCRecipient(), expected);
			}),
		new unit_equal("add ccrecipients and then count it", []()
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
				return AssertEqual(mail.GetCCRecipientCount(), 8);
			}),
		new unit_equal("add ccrecipients and then check it", []()
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
				return AssertEqual(mail.GetCCRecipient(), expected);
			}),
		new unit_exception("add ccrecipients and then add empty ccrecipient",
			Exceptions::Core::invalid_argument("recipient email is empty"),
			[]()
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
				mail.AddCCRecipient("");
			}),
		new unit_equal("mail bccrecipient count zero by default", []()
			{
				Protocol::SMTP::MAIL mail;
				return AssertEqual(mail.GetBCCRecipientCount(), 0);
			}),
		new unit_equal("mail bccrecipient list empty by default", []()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				return AssertEqual(mail.GetBCCRecipient(), expected);
			}),
		new unit_exception("add bccrecipient with empty email and name",
			Exceptions::Core::invalid_argument("recipient email is empty"),
			[]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddBCCRecipient("", "");
			}),
		new unit_exception("add bccrecipient with empty email",
			Exceptions::Core::invalid_argument("recipient email is empty"),
			[]()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddBCCRecipient("", "somename");
			}),
		new unit_equal("set first bccrecipient", []()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;

				mail.AddBCCRecipient("qwerty1", "09898987436");
				expected["qwerty1"] = "09898987436";
				return AssertEqual(mail.GetBCCRecipient(), expected);
			}),
		new unit_equal("add existed bccrecipient does not change the list", []()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddBCCRecipient("qwerty1", "qwerty");
				expected["qwerty1"] = "qwerty";
				mail.AddBCCRecipient("qwerty1");
				expected["qwerty1"] = "";
				mail.AddBCCRecipient("qwerty1");
				expected["qwerty1"] = "";
				return AssertEqual(mail.GetBCCRecipient(), expected);
			}),
		new unit_equal("add bccrecipients and then count it", []()
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
				return AssertEqual(mail.GetBCCRecipientCount(), 8);
			}),
		new unit_equal("add bccrecipients and then check it", []()
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
				return AssertEqual(mail.GetBCCRecipient(), expected);
			}),
		new unit_exception("add bccrecipients and then add empty recipient",
			Exceptions::Core::invalid_argument("recipient email is empty"),
		[]()
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
				mail.AddBCCRecipient("");
			}),

		new unit_equal("remove of empty list of recipients", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelRecipients();
				return AssertEqual(mail.GetRecipientCount(), 0);
			}), 
		new unit_equal("remove of already removed list of recipients", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelRecipients();
				mail.DelRecipients();
				mail.DelRecipients();
				return AssertEqual(mail.GetRecipientCount(), 0);
			}),
		new unit_equal("remove list of recipients", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddRecipient("Another user 1");
				mail.AddRecipient("Another user 2");
				mail.AddRecipient("Another user 3", "qwerty1");
				mail.AddRecipient("Another user 4");
				mail.DelRecipients();
				return AssertEqual(mail.GetRecipientCount(), 0);
			}),
		new unit_equal("remove of empty list of ccrecipients", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelCCRecipients();
				return AssertEqual(mail.GetCCRecipientCount(), 0);
			}),
		new unit_equal("remove of already removed list of ccrecipients", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelCCRecipients();
				mail.DelCCRecipients();
				mail.DelCCRecipients();
				return AssertEqual(mail.GetCCRecipientCount(), 0);
			}),
		new unit_equal("remove list of ccrecipients", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddCCRecipient("Another user 1");
				mail.AddCCRecipient("Another user 2");
				mail.AddCCRecipient("Another user 3", "qwerty1");
				mail.AddCCRecipient("Another user 4");
				mail.DelCCRecipients();
				return AssertEqual(mail.GetCCRecipientCount(), 0);
			}),
		new unit_equal("remove of empty list of bccrecipients", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelBCCRecipients();
				return AssertEqual(mail.GetBCCRecipientCount(), 0);
			}),
		new unit_equal("remove of already removed list of bccrecipients", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelBCCRecipients();
				mail.DelBCCRecipients();
				mail.DelBCCRecipients();
				return AssertEqual(mail.GetBCCRecipientCount(), 0);
			}),
		new unit_equal("remove list of bccrecipients", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddBCCRecipient("Another user 1");
				mail.AddBCCRecipient("Another user 2");
				mail.AddBCCRecipient("Another user 3", "qwerty1");
				mail.AddBCCRecipient("Another user 4");
				mail.DelBCCRecipients();
				return AssertEqual(mail.GetBCCRecipientCount(), 0);
			}),

		new unit_equal("add one recipient before clearing the list", []()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddRecipient("Another user 1");
				mail.DelRecipients();
				mail.AddRecipient("Another user 1", "Another user name 1");
				expected["Another user 1"] = "Another user name 1";
				return AssertEqual(mail.GetRecipient(), expected);
			}),
		new unit_equal("add one recipient before clearing the list with a lot of recipients in it", []()
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
				return AssertEqual(mail.GetRecipient(), expected);
			}),
		new unit_equal("add some recipients before clearing the list with a lot of recipients in it then count it", []()
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
				return AssertEqual(mail.GetRecipientCount(), 6);
			}),
		new unit_equal("add some recipients before clearing the list with a lot of recipients in it then delete list again and then count it", []()
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
				return AssertEqual(mail.GetRecipientCount(), 2);
			}),
		new unit_equal("add some recipients clear? then add, then delete list again and then clear count it", []()
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
				return AssertEqual(mail.GetRecipient(), expected);
			}),
		new unit_equal("add one ccrecipient before clearing the list", []()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddCCRecipient("Another user 1");
				mail.DelCCRecipients();
				mail.AddCCRecipient("Another user 1", "Another user name 1");
				expected["Another user 1"] = "Another user name 1";
				return AssertEqual(mail.GetCCRecipient(), expected);
			}),
		new unit_equal("add one ccrecipient before clearing the list with a lot of ccrecipients in it", []()
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
				return AssertEqual(mail.GetCCRecipient(), expected);
			}),
		new unit_equal("add some ccrecipients before clearing the list with a lot of ccrecipients in it then count it", []()
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
				return AssertEqual(mail.GetCCRecipientCount(), 6);
			}),
		new unit_equal("add some ccrecipients before clearing the list with a lot of ccrecipients in it then delete list again and then count it", []()
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
				return AssertEqual(mail.GetCCRecipientCount(), 2);
			}),
		new unit_equal("add some ccrecipients clear? then add, then delete list again and then clear count it", []()
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
				return AssertEqual(mail.GetCCRecipient(), expected);
			}),
		new unit_equal("add one bccrecipient before clearing the list", []()
			{
				Protocol::SMTP::MAIL mail;
				Protocol::SMTP::MAIL::Recipients expected;
				mail.AddBCCRecipient("Another user 1");
				mail.DelBCCRecipients();
				mail.AddBCCRecipient("Another user 1", "Another user name 1");
				expected["Another user 1"] = "Another user name 1";
				return AssertEqual(mail.GetBCCRecipient(), expected);
			}),
		new unit_equal("add one bccrecipient before clearing the list with a lot of bccrecipients in it", []()
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
				return AssertEqual(mail.GetBCCRecipient(), expected);
			}),
		new unit_equal("add some bccrecipients before clearing the list with a lot of bccrecipients in it then count it", []()
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
				return AssertEqual(mail.GetBCCRecipientCount(), 6);
			}),
		new unit_equal("add some bccrecipients before clearing the list with a lot of bccrecipients in it then delete list again and then count it", []()
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
				return AssertEqual(mail.GetBCCRecipientCount(), 2);
			}),
		new unit_equal("add some bccrecipients clear? then add, then delete list again and then clear count it", []()
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
				return AssertEqual(mail.GetBCCRecipient(), expected);
			}),


		new unit_equal("priority by default", []()
			{
				Protocol::SMTP::MAIL mail;
				return AssertEqual(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL);
			}),
		new unit_equal("XMailer by default", []()
			{
				Protocol::SMTP::MAIL mail;
				return AssertEqual(mail.GetXMailer(), Protocol::SMTP::XMAILER);
			}),
		new unit_equal("set priority", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				return AssertEqual(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL);
			}),
		new unit_equal("change priority 1", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::HIGH);
				return AssertEqual(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::HIGH);
			}),
		new unit_equal("change priority 2", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::LOW);
				return AssertEqual(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::LOW);
			}),
		new unit_equal("change priority 3", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				return AssertEqual(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL);
			}),
		new unit_equal("change priority 4", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::LOW);
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::LOW);
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				return AssertEqual(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL);
			}),
		new unit_equal("change priority to default", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
				mail.SetXPriority();
				return AssertEqual(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL);
			}),

		new unit_equal("set XMailer", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXMailer("AopjopjsG9d04k;SDg=-3dsgDS");
				return AssertEqual(mail.GetXMailer(), "AopjopjsG9d04k;SDg=-3dsgDS");
			}),
		new unit_equal("change XMailer 1", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXMailer("AopjopjsG9d04k;SDg=-3dsgDS");
				mail.SetXMailer("");
				return AssertEqual(mail.GetXMailer(), "");
			}),
		new unit_equal("change XMailer 2", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.SetXMailer("AopjopjsG9d04k;SDg=-3dsgDS");
				mail.SetXMailer("");
				mail.SetXMailer("1234568752457780957");
				mail.SetXMailer("IAhjio34   sad0-9 3");
				mail.SetXMailer("42j90,m9a 90as");
				mail.SetXMailer("=--(_io3;k2os89)&9sa");
				return AssertEqual(mail.GetXMailer(), "=--(_io3;k2os89)&9sa");
			}),

		new unit_equal("letter must be empty by default", []()
			{
				Protocol::SMTP::MAIL mail;
				return AssertEqual(mail.GetBodySize(), 0);
			}),
		new unit_equal("add lines to msg and check count of msg lines", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddMsgLine("Hello,");
				mail.AddMsgLine("");
				mail.AddMsgLine("...");
				mail.AddMsgLine("How are you today?");
				mail.AddMsgLine("");
				mail.AddMsgLine("Regards");
				return AssertEqual(mail.GetBodySize(), 6);
			}),
		new unit_equal("add lines to msg and check content 1", []()
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
				return AssertEqual(mail.GetBody(), expected);
			}),
		new unit_equal("add lines to msg and check content 2", []()
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
				return AssertEqual(mail.GetBody(), expected);
			}),

		new unit_exception("input one lines and than modify line index that more than body size when modify line",
			Exceptions::Core::out_of_range("modify line of message body"), []() {
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.AddMsgLine("Hello,");
				expected.push_back("Hello,");
				mail.ModMsgLine(1, "");
		}),
		new unit_exception("modify line index that more than body size",
			Exceptions::Core::out_of_range("modify line of message body"), []() {
				Protocol::SMTP::MAIL mail;
				mail.ModMsgLine(-9, " y54 zay5 8569");
		}),
		new unit_exception("modify line index that more than body size",
			Exceptions::Core::out_of_range("modify line of message body"), []() {
				Protocol::SMTP::MAIL mail;
				mail.ModMsgLine(567, "46346174");
		}),
		new unit_exception("modify line index that more than body size",
			Exceptions::Core::out_of_range("modify line of message body"), []() {
				Protocol::SMTP::MAIL mail;
				mail.ModMsgLine(-4577, "wsr sh");
			}),
		new unit_exception("modify line index that more than body size",
			Exceptions::Core::out_of_range("modify line of message body"), []() {
				Protocol::SMTP::MAIL mail;
				mail.ModMsgLine(0, "");
			}),
		new unit_exception("modify line index that more than body size",
			Exceptions::Core::out_of_range("modify line of message body"), []() {
				Protocol::SMTP::MAIL mail;
				mail.ModMsgLine(-1, "rty");
			}),
		new unit_exception("input some lines and than modify line of index that negative",
			Exceptions::Core::out_of_range("modify line of message body"), []() {
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
				mail.ModMsgLine(-1, "rty");
			}),
		new unit_exception("input some lines and than modify line of index that more than body size",
			Exceptions::Core::out_of_range("modify line of message body"), []() {
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
				mail.ModMsgLine(55, "try to modify");
			}),
		new unit_equal("modify line of msg", []()
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
				return AssertEqual(mail.GetBody(), expected);
			}),

		new unit_exception("delete line of index -1",
			Exceptions::Core::out_of_range("deleting line of message body"), []()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.DelMsgLine(-1);
			}),
		new unit_exception("delete line of empty msg with zero index",
			Exceptions::Core::out_of_range("deleting line of message body"), []()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.DelMsgLine(0);
			}),
		new unit_exception("delete line of index that negative",
			Exceptions::Core::out_of_range("deleting line of message body"), []()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.DelMsgLine(-72865);
			}),
		new unit_exception("delete line of index that more than body size",
			Exceptions::Core::out_of_range("deleting line of message body"), []()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.DelMsgLine(72865);
			}),
		new unit_equal("deleting line of msg", []()
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
				return AssertEqual(mail.GetBody(), expected);
			}),

		new unit_equal("deleting all lines of empty msg", []()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.DelMsgLines();
				mail.DelMsgLines();
				mail.DelMsgLines();
				return AssertEqual(mail.GetBody(), expected);
			}),
		new unit_equal("deleting all lines of small msg", []()
			{
				Protocol::SMTP::MAIL mail;
				std::vector<std::string> expected;
				mail.AddMsgLine("Hello,");
				mail.AddMsgLine("...");
				mail.AddMsgLine("...");
				mail.AddMsgLine("...");
				mail.AddMsgLine("...");

				mail.DelMsgLines();
				return AssertEqual(mail.GetBody(), expected);
			}),
		new unit_equal("deleting all msg lines", []()
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
				return AssertEqual(mail.GetBody(), expected);
			}),

		new unit_equal("by default we have zero attachments", []()
			{
				Protocol::SMTP::MAIL mail;
				return AssertEqual(mail.GetAttachmentsSize(), 0);
			}),
		new unit_exception("input is an empty attahchment path",
			Exceptions::Core::invalid_argument("input empty path"), []()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddAttachment("");
			}),
		new unit_equal("adding attachments", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddAttachment("./test/files/7.jpg");
				mail.AddAttachment("./test/files/8.jpg");
				mail.AddAttachment("./test/files/9.png");
				return AssertEqual(mail.GetAttachmentsSize(), 3);
			}),
		new unit_exception("input is an empty path before adding some attahchments",
			Exceptions::Core::invalid_argument("input empty path"), []()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddAttachment("./test/files/7.jpg");
				mail.AddAttachment("./test/files/8.jpg");
				mail.AddAttachment("./test/files/9.png");
				mail.AddAttachment("./test/files/simple text.txt");
				mail.AddAttachment("./test/files/24.txt");
				mail.AddAttachment("./test/files/19_23.zip");
				mail.AddAttachment("");
			}),

		new unit_equal("deleting empty list of attachments", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.DelAttachments();
				mail.DelAttachments();
				mail.DelAttachments();
				mail.DelAttachments();
				return AssertEqual(mail.GetAttachmentsSize(), 0);
			}),
		new unit_equal("deleting attachments", []()
			{
				Protocol::SMTP::MAIL mail;
				mail.AddAttachment("./test/files/7.jpg");
				mail.AddAttachment("./test/files/8.jpg");
				mail.AddAttachment("./test/files/9.png");
				mail.DelAttachments();
				return AssertEqual(mail.GetAttachmentsSize(), 0);
			}),
		new unit_equal("deleting, adding and then deleting again attachments", []()
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
				return AssertEqual(mail.GetAttachmentsSize(), 0);
			}),
	}
};
#endif