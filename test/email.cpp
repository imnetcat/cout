#include "email.h"
using namespace std;
void TEST::Utils::ModMsgLine(Protocol::SMTP::MAIL& mail, unsigned int Line, const char* Text)
{
	mail.ModMsgLine(Line, Text);
}
void TEST::Utils::DelMsgLine(Protocol::SMTP::MAIL& mail, unsigned int Line)
{
	mail.DelMsgLine(Line);
}
void TEST::Utils::AddRecipient(Protocol::SMTP::MAIL& mail, const char* email, const char* name)
{
	mail.AddRecipient(email, name);
}
void TEST::Utils::AddCCRecipient(Protocol::SMTP::MAIL& mail, const char* email, const char* name)
{
	mail.AddCCRecipient(email, name);
}
void TEST::Utils::AddBCCRecipient(Protocol::SMTP::MAIL& mail, const char* email, const char* name)
{
	mail.AddBCCRecipient(email, name);
}
void TEST::Utils::AddAttachment(Protocol::SMTP::MAIL& mail, const char* path)
{
	mail.AddAttachment(path);
}
void TEST::Utils::SetAuth(Protocol::SMTP::Client& client, const char* login, const char* pass)
{
	client.SetLogin(login);
	client.SetPassword(pass);
}
void TEST::Utils::ClientSend(Protocol::SMTP::Client client, Protocol::SMTP::MAIL& mail)
{
	client.Send(&mail);
}
void TEST::StructOfMail::SetSenderName()
{
	Protocol::SMTP::MAIL mail;
	mail.SetSenderName("User");
	Assert(mail.GetSenderName(), "User", "set up sender name");
	mail.SetSenderName("Another");
	Assert(mail.GetSenderName(), "Another", "change sender name");
	mail.SetSenderName("Another user");
	Assert(mail.GetSenderName(), "Another user", "change sender name");
	mail.SetSenderName("2136547");
	Assert(mail.GetSenderName(), "2136547", "change sender name");
	mail.SetSenderName(" 23 - jm5 b 893 ks;'[p\\");
	Assert(mail.GetSenderName(), " 23 - jm5 b 893 ks;'[p\\", "change sender name");
	mail.SetSenderName(" ");
	Assert(mail.GetSenderName(), " ", "change sender name");
	mail.SetSenderName("qwerty");
	Assert(mail.GetSenderName(), "qwerty", "change sender name");
	mail.SetSenderName(" qwerty ");
	Assert(mail.GetSenderName(), " qwerty ", "change sender name");
	mail.SetSenderName("\\qwerty\\");
	Assert(mail.GetSenderName(), "\\qwerty\\", "change sender name");
	mail.SetSenderName("");
	Assert(mail.GetSenderName(), "", "change sender name");
	mail.SetSenderName("	");
	Assert(mail.GetSenderName(), "	", "change sender name");
}
void TEST::StructOfMail::SetSenderMail()
{
	Protocol::SMTP::MAIL mail;
	mail.SetSenderMail("User");
	Assert(mail.GetSenderMail(), "User", "set up sender mail");
	mail.SetSenderMail("Another");
	Assert(mail.GetSenderMail(), "Another", "change sender mail");
	mail.SetSenderMail("Another user");
	Assert(mail.GetSenderMail(), "Another user", "change sender mail");
	mail.SetSenderMail("2136547");
	Assert(mail.GetSenderMail(), "2136547", "change sender mail");
	mail.SetSenderMail(" 23 - jm5 b 893 ks;'[p\\");
	Assert(mail.GetSenderMail(), " 23 - jm5 b 893 ks;'[p\\", "change sender mail");
	mail.SetSenderMail(" ");
	Assert(mail.GetSenderMail(), " ", "change sender mail");
	mail.SetSenderMail("qwerty");
	Assert(mail.GetSenderMail(), "qwerty", "change sender mail");
	mail.SetSenderMail(" qwerty ");
	Assert(mail.GetSenderMail(), " qwerty ", "change sender mail");
	mail.SetSenderMail("\\qwerty\\");
	Assert(mail.GetSenderMail(), "\\qwerty\\", "change sender mail");
	mail.SetSenderMail("");
	Assert(mail.GetSenderMail(), "", "change sender mail");
	mail.SetSenderMail("	");
	Assert(mail.GetSenderMail(), "	", "change sender mail");
}
void TEST::StructOfMail::SetReplyTo()
{
	Protocol::SMTP::MAIL mail;
	mail.SetReplyTo("User");
	Assert(mail.GetReplyTo(), "User", "set up reply to");
	mail.SetReplyTo("Another");
	Assert(mail.GetReplyTo(), "Another", "change reply to");
	mail.SetReplyTo("Another user");
	Assert(mail.GetReplyTo(), "Another user", "change reply to");
	mail.SetReplyTo("2136547");
	Assert(mail.GetReplyTo(), "2136547", "change reply to");
	mail.SetReplyTo(" 23 - jm5 b 893 ks;'[p\\");
	Assert(mail.GetReplyTo(), " 23 - jm5 b 893 ks;'[p\\", "change reply to");
	mail.SetReplyTo(" ");
	Assert(mail.GetReplyTo(), " ", "change reply to");
	mail.SetReplyTo("qwerty");
	Assert(mail.GetReplyTo(), "qwerty", "change reply to");
	mail.SetReplyTo(" qwerty ");
	Assert(mail.GetReplyTo(), " qwerty ", "change reply to");
	mail.SetReplyTo("\\qwerty\\");
	Assert(mail.GetReplyTo(), "\\qwerty\\", "change reply to");
	mail.SetReplyTo("");
	Assert(mail.GetReplyTo(), "", "change reply to");
	mail.SetReplyTo("	");
	Assert(mail.GetReplyTo(), "	", "change reply to");
}
void TEST::StructOfMail::SetSubject()
{
	Protocol::SMTP::MAIL mail;
	mail.SetSubject("User");
	Assert(mail.GetSubject(), "User", "set up subject");
	mail.SetSubject("Another");
	Assert(mail.GetSubject(), "Another", "change subject");
	mail.SetSubject("Another user");
	Assert(mail.GetSubject(), "Another user", "change subject");
	mail.SetSubject("2136547");
	Assert(mail.GetSubject(), "2136547", "change subject");
	mail.SetSubject(" 23 - jm5 b 893 ks;'[p\\");
	Assert(mail.GetSubject(), " 23 - jm5 b 893 ks;'[p\\", "change subject");
	mail.SetSubject(" ");
	Assert(mail.GetSubject(), " ", "change subject");
	mail.SetSubject("qwerty");
	Assert(mail.GetSubject(), "qwerty", "change subject");
	mail.SetSubject(" qwerty ");
	Assert(mail.GetSubject(), " qwerty ", "change subject");
	mail.SetSubject("\\qwerty\\");
	Assert(mail.GetSubject(), "\\qwerty\\", "change subject");
	mail.SetSubject("");
	Assert(mail.GetSubject(), "", "change subject");
	mail.SetSubject("	");
	Assert(mail.GetSubject(), "	", "change subject");
}
void TEST::StructOfMail::RecipientsDefault()
{
	Protocol::SMTP::MAIL mail;
	Protocol::SMTP::MAIL::Recipients expected;
	Assert(mail.GetRecipientCount(), 0, "zero by default");
	Assert(mail.GetRecipient(), expected, "zero by default");
}
void TEST::StructOfMail::AddRecipient()
{
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		
		AssertExceptions<Exceptions::Core::invalid_argument>("AddRecipient", "recipient have empty email", "recipient email is empty", TEST::Utils::AddRecipient, mail, "", "");
		
		Assert(mail.GetRecipientCount(), 0, "unchanged");
		Assert(mail.GetRecipient(), expected, "unchanged - 0 recipient");

		mail.AddRecipient("qwerty1");
		expected["qwerty1"] = "";
		Assert(mail.GetRecipientCount(), 1, "set first recipient");
		Assert(mail.GetRecipient(), expected, "1 recipients");
		mail.AddRecipient("qwerty1");
		expected["qwerty1"] = "";
		mail.AddRecipient("qwerty1");
		expected["qwerty1"] = "";
		mail.AddRecipient("qwerty1");
		expected["qwerty1"] = "";
		Assert(mail.GetRecipientCount(), 1, "unchanged");
		Assert(mail.GetRecipient(), expected, "1 recipients");

		mail.AddRecipient("qwerty2");
		expected["qwerty2"] = "";
		Assert(mail.GetRecipientCount(), 2, "add recipient");
		Assert(mail.GetRecipient(), expected, "2 recipients");

		mail.AddRecipient("Another user 1");
		expected["Another user 1"] = "";
		Assert(mail.GetRecipientCount(), 3, "add recipient");
		Assert(mail.GetRecipient(), expected, "3 recipients");

		mail.AddRecipient("Another user 2");
		expected["Another user 2"] = "";
		Assert(mail.GetRecipientCount(), 4, "add recipient");
		Assert(mail.GetRecipient(), expected, "4 recipients");

		mail.AddRecipient("Another user 3");
		expected["Another user 3"] = "";
		Assert(mail.GetRecipientCount(), 5, "add recipient");
		Assert(mail.GetRecipient(), expected, "5 recipients");

		mail.AddRecipient("Another user 4");
		expected["Another user 4"] = "";
		Assert(mail.GetRecipientCount(), 6, "add recipient");
		Assert(mail.GetRecipient(), expected, "6 recipients");

		mail.AddRecipient("  11 user ");
		expected["  11 user "] = "";
		Assert(mail.GetRecipientCount(), 7, "add recipient");
		Assert(mail.GetRecipient(), expected, "7 recipients");

		mail.AddRecipient(" 234user");
		expected[" 234user"] = "";
		Assert(mail.GetRecipientCount(), 8, "add recipient");
		Assert(mail.GetRecipient(), expected, "8 recipients");

		AssertExceptions<Exceptions::Core::invalid_argument>("AddRecipient", "recipient have empty email", "recipient email is empty", TEST::Utils::AddRecipient, mail, "", "");

		Assert(mail.GetRecipientCount(), 8, "unchanged");
		Assert(mail.GetRecipient(), expected, "unchanged - 8 recipient");
	}
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;

		AssertExceptions<Exceptions::Core::invalid_argument>("AddRecipient", "recipient have empty email", "recipient email is empty", TEST::Utils::AddRecipient, mail, "", "123");
		
		Assert(mail.GetRecipientCount(), 0, "unchanged");
		Assert(mail.GetRecipient(), expected, "unchanged - 0 recipients");

		mail.AddRecipient("qwerty1", "qwerty1");
		expected["qwerty1"] = "qwerty1";
		Assert(mail.GetRecipientCount(), 1, "set first recipient");
		Assert(mail.GetRecipient(), expected, "1 recipient");

		mail.AddRecipient("qwerty2", "name of qwerty2");
		expected["qwerty2"] = "name of qwerty2";
		Assert(mail.GetRecipientCount(), 2, "add recipient");
		Assert(mail.GetRecipient(), expected, "2 recipients");

		mail.AddRecipient("Another user 1", "some_name");
		expected["Another user 1"] = "some_name";
		Assert(mail.GetRecipientCount(), 3, "add recipient");
		Assert(mail.GetRecipient(), expected, "3 recipients");

		mail.AddRecipient("Another user 2");
		expected["Another user 2"] = "";
		Assert(mail.GetRecipientCount(), 4, "add recipient");
		Assert(mail.GetRecipient(), expected, "3 recipients and 1 without");

		mail.AddRecipient("Another user 3", "asqwedaszxcQWEAS_____-- as3 235");
		expected["Another user 3"] = "asqwedaszxcQWEAS_____-- as3 235";
		Assert(mail.GetRecipientCount(), 5, "add recipient");
		Assert(mail.GetRecipient(), expected, "4 recipients and 1 without");

		mail.AddRecipient("Another user 4", " 12983 klj    ");
		expected["Another user 4"] = " 12983 klj    ";
		Assert(mail.GetRecipientCount(), 6, "add recipient");
		Assert(mail.GetRecipient(), expected, "5 recipients and 1 without");

		mail.AddRecipient("  11 user ");
		expected["  11 user "] = "";
		Assert(mail.GetRecipientCount(), 7, "add recipient");
		Assert(mail.GetRecipient(), expected, "5 recipients and 2 without");

		mail.AddRecipient(" 234user", "YYYY-QQQQ");
		expected[" 234user"] = "YYYY-QQQQ";
		Assert(mail.GetRecipientCount(), 8, "add recipient");
		Assert(mail.GetRecipient(), expected, "6 recipients and 2 without");

		AssertExceptions<Exceptions::Core::invalid_argument>("AddRecipient", "recipient have empty email", "recipient email is empty", TEST::Utils::AddRecipient, mail, "", "name");

		Assert(mail.GetRecipientCount(), 8, "unchanged");
		Assert(mail.GetRecipient(), expected, "unchanged - 8 recipient");
	}
}
void TEST::StructOfMail::DelEmptyRecipients()
{
	{
		Protocol::SMTP::MAIL mail;
		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "already empty");
		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "simply empty");
	}
}
void TEST::StructOfMail::DelRecipients()
{
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddRecipient("Another user 1");
		Assert(mail.GetRecipientCount(), 1, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
		Assert(mail.GetRecipient(), expected, "not expected elements");
	}
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddRecipient("Another user 1");
		Assert(mail.GetRecipientCount(), 1, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
		Assert(mail.GetRecipient(), expected, "not expected elements");
	}
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddRecipient("qwerty1");
		mail.AddRecipient("qwerty2");
		mail.AddRecipient("Another user 1");
		mail.AddRecipient("Another user 2");
		mail.AddRecipient("Another user 3");
		mail.AddRecipient("Another user 4");
		mail.AddRecipient("  11 user ");
		mail.AddRecipient(" 234user");
		Assert(mail.GetRecipientCount(), 8, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
		Assert(mail.GetRecipient(), expected, "not expected elements");
	}
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
		Assert(mail.GetRecipientCount(), 8, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
		Assert(mail.GetRecipient(), expected, "not expected elements");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.AddRecipient("qwerty1", "qwerty1");
		mail.AddRecipient("qwerty2", "name of qwerty2");
		mail.AddRecipient("Another user 1", "some_name");
		Assert(mail.GetRecipientCount(), 3, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.AddRecipient("Another user 2");
		mail.AddRecipient("Another user 3", "asqwedaszxcQWEAS_____-- as3 235");
		mail.AddRecipient("Another user 4", " 12983 klj    ");
		mail.AddRecipient("  11 user ");
		mail.AddRecipient(" 234user", "YYYY-QQQQ");
		mail.AddRecipient("qwerty1", "qwerty1");
		mail.AddRecipient("qwerty2", "name of qwerty2");
		mail.AddRecipient("Another user 1", "some_name");
		Assert(mail.GetRecipientCount(), 8, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.AddRecipient("Another user 2");
		mail.AddRecipient("Another user 3", "asqwedaszxcQWEAS_____-- as3 235");
		mail.AddRecipient("Another user 4", " 12983 klj    ");
		mail.AddRecipient("  11 user ");
		mail.AddRecipient(" 234user", "YYYY-QQQQ");
		mail.AddRecipient("qwerty1", "qwerty1");
		mail.AddRecipient("qwerty2", "name of qwerty2");
		mail.AddRecipient("Another user 1", "some_name");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "already empty");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "simply empty");
	}
}
void TEST::StructOfMail::AddRecipientBeforeDel()
{
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddRecipient("Another user 1");
		Assert(mail.GetRecipientCount(), 1, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
		Assert(mail.GetRecipient(), expected, "not expected elements");

		mail.AddRecipient("Another user 1");
		expected["Another user 1"] = "";
		Assert(mail.GetRecipient(), expected, "add recipient");
		Assert(mail.GetRecipientCount(), 1, "add recipient");
	}
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddRecipient("Another user 1");
		Assert(mail.GetRecipientCount(), 1, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
		Assert(mail.GetRecipient(), expected, "not expected elements");

		mail.AddRecipient("Another user 1");
		expected["Another user 1"] = "";
		Assert(mail.GetRecipient(), expected, "add recipient");
		Assert(mail.GetRecipientCount(), 1, "add recipient");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.AddRecipient("qwerty1");
		mail.AddRecipient("qwerty2");
		mail.AddRecipient("Another user 1");
		mail.AddRecipient("Another user 2");
		mail.AddRecipient("Another user 3");
		mail.AddRecipient("Another user 4");
		mail.AddRecipient("  11 user ");
		mail.AddRecipient(" 234user");
		Assert(mail.GetRecipientCount(), 8, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");

		mail.AddRecipient("Another user 1");
		mail.AddRecipient("Another user 2");
		mail.AddRecipient("Another user 3");
		mail.AddRecipient("Another user 4");
		Assert(mail.GetRecipientCount(), 4, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
	}
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
		Assert(mail.GetRecipientCount(), 8, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
		Assert(mail.GetRecipient(), expected, "not expected elements");
		mail.AddRecipient("Another user 1");
		expected["Another user 1"] = "";
		Assert(mail.GetRecipient(), expected, "add recipient");
		Assert(mail.GetRecipientCount(), 1, "add recipient");
		mail.AddRecipient("22222");
		expected["22222"] = "";
		Assert(mail.GetRecipient(), expected, "add recipient");
		Assert(mail.GetRecipientCount(), 2, "add recipient");
		mail.DelRecipients();
		expected.clear();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
		Assert(mail.GetRecipient(), expected, "not expected elements");
	}
}
void TEST::StructOfMail::CCRecipientsDefault()
{
	Protocol::SMTP::MAIL mail;
	Protocol::SMTP::MAIL::Recipients expected;
	Assert(mail.GetCCRecipientCount(), 0, "zero by default");
	Assert(mail.GetCCRecipient(), expected, "zero by default");
}
void TEST::StructOfMail::AddCCRecipient()
{
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;

		AssertExceptions<Exceptions::Core::invalid_argument>("AddCCRecipient", "recipient have empty email", "recipient email is empty", TEST::Utils::AddCCRecipient, mail, "", "");

		Assert(mail.GetCCRecipientCount(), 0, "unchanged");
		Assert(mail.GetCCRecipient(), expected, "unchanged - 0 recipient");

		mail.AddCCRecipient("qwerty1");
		expected["qwerty1"] = "";
		Assert(mail.GetCCRecipientCount(), 1, "set first recipient");
		Assert(mail.GetCCRecipient(), expected, "1 recipients");

		mail.AddCCRecipient("qwerty2");
		expected["qwerty2"] = "";
		Assert(mail.GetCCRecipientCount(), 2, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "2 recipients");

		mail.AddCCRecipient("Another user 1");
		expected["Another user 1"] = "";
		Assert(mail.GetCCRecipientCount(), 3, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "3 recipients");

		mail.AddCCRecipient("Another user 2");
		expected["Another user 2"] = "";
		Assert(mail.GetCCRecipientCount(), 4, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "4 recipients");

		mail.AddCCRecipient("Another user 3");
		expected["Another user 3"] = "";
		Assert(mail.GetCCRecipientCount(), 5, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "5 recipients");

		mail.AddCCRecipient("Another user 4");
		expected["Another user 4"] = "";
		Assert(mail.GetCCRecipientCount(), 6, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "6 recipients");

		mail.AddCCRecipient("  11 user ");
		expected["  11 user "] = "";
		Assert(mail.GetCCRecipientCount(), 7, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "7 recipients");

		mail.AddCCRecipient(" 234user");
		expected[" 234user"] = "";
		Assert(mail.GetCCRecipientCount(), 8, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "8 recipients");

		AssertExceptions<Exceptions::Core::invalid_argument>("AddCCRecipient", "recipient have empty email", "recipient email is empty", TEST::Utils::AddCCRecipient, mail, "", "");
		
		Assert(mail.GetCCRecipientCount(), 8, "unchanged");
		Assert(mail.GetCCRecipient(), expected, "unchanged - 8 recipient");
	}
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;

		AssertExceptions<Exceptions::Core::invalid_argument>("AddCCRecipient", "recipient have empty email", "recipient email is empty", TEST::Utils::AddCCRecipient, mail, "", "12 975  846");
		
		Assert(mail.GetCCRecipientCount(), 0, "unchanged");
		Assert(mail.GetCCRecipient(), expected, "unchanged - 0 recipients");

		mail.AddCCRecipient("qwerty1", "qwerty1");
		expected["qwerty1"] = "qwerty1";
		Assert(mail.GetCCRecipientCount(), 1, "set first recipient");
		Assert(mail.GetCCRecipient(), expected, "1 recipients");

		mail.AddCCRecipient("qwerty2", "name of qwerty2");
		expected["qwerty2"] = "name of qwerty2";
		Assert(mail.GetCCRecipientCount(), 2, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "2 recipients");

		mail.AddCCRecipient("Another user 1", "some_name");
		expected["Another user 1"] = "some_name";
		Assert(mail.GetCCRecipientCount(), 3, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "3 recipients");

		mail.AddCCRecipient("Another user 2");
		expected["Another user 2"] = "";
		Assert(mail.GetCCRecipientCount(), 4, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "4 recipients");

		mail.AddCCRecipient("Another user 3", "asqwedaszxcQWEAS_____-- as3 235");
		expected["Another user 3"] = "asqwedaszxcQWEAS_____-- as3 235";
		Assert(mail.GetCCRecipientCount(), 5, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "5 recipients");

		mail.AddCCRecipient("Another user 4", " 12983 klj    ");
		expected["Another user 4"] = " 12983 klj    ";
		Assert(mail.GetCCRecipientCount(), 6, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "6 recipients");

		mail.AddCCRecipient("  11 user ");
		expected["  11 user "] = "";
		Assert(mail.GetCCRecipientCount(), 7, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "7 recipients");

		mail.AddCCRecipient(" 234user", "YYYY-QQQQ");
		expected[" 234user"] = "YYYY-QQQQ";
		Assert(mail.GetCCRecipientCount(), 8, "add recipient");
		Assert(mail.GetCCRecipient(), expected, "8 recipients");

		AssertExceptions<Exceptions::Core::invalid_argument>("AddCCRecipient", "recipient have empty email", "recipient email is empty", TEST::Utils::AddCCRecipient, mail, "", "srtu5gsq");
		
		Assert(mail.GetCCRecipientCount(), 8, "unchanged");
		Assert(mail.GetCCRecipient(), expected, "unchanged - 8 recipient");
	}
}
void TEST::StructOfMail::DelEmptyCCRecipients()
{
	{
		Protocol::SMTP::MAIL mail;
		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "already empty");
		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "simply empty");
	}
}
void TEST::StructOfMail::DelCCRecipients()
{
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddCCRecipient("Another user 1");
		Assert(mail.GetCCRecipientCount(), 1, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetCCRecipient(), expected, "not expected elements");
	}
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddCCRecipient("Another user 1");
		mail.AddCCRecipient("Another user 2");
		mail.AddCCRecipient("Another user 3");
		Assert(mail.GetCCRecipientCount(), 3, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetCCRecipient(), expected, "not expected elements");
	}
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddCCRecipient("qwerty1");
		mail.AddCCRecipient("qwerty2");
		mail.AddCCRecipient("Another user 1");
		mail.AddCCRecipient("Another user 2");
		mail.AddCCRecipient("Another user 3");
		mail.AddCCRecipient("Another user 4");
		mail.AddCCRecipient("  11 user ");
		mail.AddCCRecipient(" 234user");
		Assert(mail.GetCCRecipientCount(), 8, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetCCRecipient(), expected, "not expected elements");
	}
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
		Assert(mail.GetCCRecipientCount(), 8, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetCCRecipient(), expected, "not expected elements");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.AddCCRecipient("qwerty1", "qwerty1");
		mail.AddCCRecipient("qwerty2", "name of qwerty2");
		mail.AddCCRecipient("Another user 1", "some_name");
		Assert(mail.GetCCRecipientCount(), 3, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.AddCCRecipient("Another user 2");
		mail.AddCCRecipient("Another user 3", "asqwedaszxcQWEAS_____-- as3 235");
		mail.AddCCRecipient("Another user 4", " 12983 klj    ");
		mail.AddCCRecipient("  11 user ");
		mail.AddCCRecipient(" 234user", "YYYY-QQQQ");
		mail.AddCCRecipient("qwerty1", "qwerty1");
		mail.AddCCRecipient("qwerty2", "name of qwerty2");
		mail.AddCCRecipient("Another user 1", "some_name");
		Assert(mail.GetCCRecipientCount(), 8, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.AddCCRecipient("Another user 2");
		mail.AddCCRecipient("Another user 3", "asqwedaszxcQWEAS_____-- as3 235");
		mail.AddCCRecipient("Another user 4", " 12983 klj    ");
		mail.AddCCRecipient("  11 user ");
		mail.AddCCRecipient(" 234user", "YYYY-QQQQ");
		mail.AddCCRecipient("qwerty1", "qwerty1");
		mail.AddCCRecipient("qwerty2", "name of qwerty2");
		mail.AddCCRecipient("Another user 1", "some_name");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "already empty");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "simply empty");
	}
}
void TEST::StructOfMail::AddCCRecipientBeforeDel()
{
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddCCRecipient("Another user 1");
		Assert(mail.GetCCRecipientCount(), 1, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetCCRecipient(), expected, "");

		mail.AddCCRecipient("Another user 1");
		expected["Another user 1"] = "";
		Assert(mail.GetCCRecipient(), expected, "add recipient");
		Assert(mail.GetCCRecipientCount(), 1, "add recipient");
	}
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddCCRecipient("Another user 1");
		mail.AddCCRecipient("Another user 2");
		mail.AddCCRecipient("Another user 3");
		Assert(mail.GetCCRecipientCount(), 3, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetCCRecipient(), expected, "");

		mail.AddCCRecipient("Another user 1");
		mail.AddCCRecipient("Another user 2");
		expected["Another user 1"] = "";
		expected["Another user 2"] = "";
		Assert(mail.GetCCRecipient(), expected, "add recipient");
		Assert(mail.GetCCRecipientCount(), 2, "add recipient");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.AddCCRecipient("qwerty1");
		mail.AddCCRecipient("qwerty2");
		mail.AddCCRecipient("Another user 1");
		mail.AddCCRecipient("Another user 2");
		mail.AddCCRecipient("Another user 3");
		mail.AddCCRecipient("Another user 4");
		mail.AddCCRecipient("  11 user ");
		mail.AddCCRecipient(" 234user");
		Assert(mail.GetCCRecipientCount(), 8, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");

		mail.AddCCRecipient("Another user 1");
		mail.AddCCRecipient("Another user 2");
		mail.AddCCRecipient("Another user 3");
		mail.AddCCRecipient("Another user 4");
		Assert(mail.GetCCRecipientCount(), 4, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
	}
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
		Assert(mail.GetCCRecipientCount(), 8, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetCCRecipient(), expected, "not expected elements");
		mail.AddCCRecipient("Another user 1");
		expected["Another user 1"] = "";
		Assert(mail.GetCCRecipient(), expected, "add recipient");
		Assert(mail.GetCCRecipientCount(), 1, "add recipient");
		mail.AddCCRecipient("22222");
		expected["22222"] = "";
		Assert(mail.GetCCRecipient(), expected, "add recipient");
		Assert(mail.GetCCRecipientCount(), 2, "add recipient");
		mail.DelCCRecipients();
		expected.clear();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetCCRecipient(), expected, "not expected elements");
	}
}
void TEST::StructOfMail::BCCRecipientsDefault()
{
	Protocol::SMTP::MAIL mail;
	Protocol::SMTP::MAIL::Recipients expected;
	Assert(mail.GetBCCRecipientCount(), 0, "zero by default");
	Assert(mail.GetBCCRecipient(), expected, "zero by default");
}
void TEST::StructOfMail::AddBCCRecipient()
{
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;

		AssertExceptions<Exceptions::Core::invalid_argument>("AddBCCRecipient", "recipient have empty email", "recipient email is empty", TEST::Utils::AddBCCRecipient, mail, "", "");
		
		Assert(mail.GetBCCRecipientCount(), 0, "unchanged");
		Assert(mail.GetBCCRecipient(), expected, "unchanged - 0 recipient");

		mail.AddBCCRecipient("qwerty1");
		expected["qwerty1"] = "";
		Assert(mail.GetBCCRecipientCount(), 1, "set first recipient");
		Assert(mail.GetBCCRecipient(), expected, "1 recipients");

		mail.AddBCCRecipient("qwerty2");
		expected["qwerty2"] = "";
		Assert(mail.GetBCCRecipientCount(), 2, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "2 recipients");

		mail.AddBCCRecipient("Another user 1");
		expected["Another user 1"] = "";
		Assert(mail.GetBCCRecipientCount(), 3, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "3 recipients");

		mail.AddBCCRecipient("Another user 2");
		expected["Another user 2"] = "";
		Assert(mail.GetBCCRecipientCount(), 4, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "4 recipients");

		mail.AddBCCRecipient("Another user 3");
		expected["Another user 3"] = "";
		Assert(mail.GetBCCRecipientCount(), 5, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "5 recipients");

		mail.AddBCCRecipient("Another user 4");
		expected["Another user 4"] = "";
		Assert(mail.GetBCCRecipientCount(), 6, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "6 recipients");

		mail.AddBCCRecipient("  11 user ");
		expected["  11 user "] = "";
		Assert(mail.GetBCCRecipientCount(), 7, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "7 recipients");

		mail.AddBCCRecipient(" 234user");
		expected[" 234user"] = "";
		Assert(mail.GetBCCRecipientCount(), 8, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "8 recipients");

		AssertExceptions<Exceptions::Core::invalid_argument>("AddBCCRecipient", "recipient have empty email", "recipient email is empty", TEST::Utils::AddBCCRecipient, mail, "", "");
		
		Assert(mail.GetBCCRecipientCount(), 8, "unchanged");
		Assert(mail.GetBCCRecipient(), expected, "unchanged - 8 recipient");
	}
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;

		AssertExceptions<Exceptions::Core::invalid_argument>("AddBCCRecipient", "recipient have empty email", "recipient email is empty", TEST::Utils::AddBCCRecipient, mail, "", "124563-907");
		
		Assert(mail.GetBCCRecipientCount(), 0, "unchanged");
		Assert(mail.GetBCCRecipient(), expected, "unchanged - 0 recipients");

		mail.AddBCCRecipient("qwerty1", "qwerty1");
		expected["qwerty1"] = "qwerty1";
		Assert(mail.GetBCCRecipientCount(), 1, "set first recipient");
		Assert(mail.GetBCCRecipient(), expected, "1 recipient");

		mail.AddBCCRecipient("qwerty2", "name of qwerty2");
		expected["qwerty2"] = "name of qwerty2";
		Assert(mail.GetBCCRecipientCount(), 2, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "2 recipients");

		mail.AddBCCRecipient("Another user 1", "some_name");
		expected["Another user 1"] = "some_name";
		Assert(mail.GetBCCRecipientCount(), 3, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "3 recipients");

		mail.AddBCCRecipient("Another user 2");
		expected["Another user 2"] = "";
		Assert(mail.GetBCCRecipientCount(), 4, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "3 recipients and 1 without");

		mail.AddBCCRecipient("Another user 3", "asqwedaszxcQWEAS_____-- as3 235");
		expected["Another user 3"] = "asqwedaszxcQWEAS_____-- as3 235";
		Assert(mail.GetBCCRecipientCount(), 5, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "4 recipients and 1 without");

		mail.AddBCCRecipient("Another user 4", " 12983 klj    ");
		expected["Another user 4"] = " 12983 klj    ";
		Assert(mail.GetBCCRecipientCount(), 6, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "5 recipients and 1 without");

		mail.AddBCCRecipient("  11 user ");
		expected["  11 user "] = "";
		Assert(mail.GetBCCRecipientCount(), 7, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "5 recipients and 2 without");

		mail.AddBCCRecipient(" 234user", "YYYY-QQQQ");
		expected[" 234user"] = "YYYY-QQQQ";
		Assert(mail.GetBCCRecipientCount(), 8, "add recipient");
		Assert(mail.GetBCCRecipient(), expected, "6 recipients and 2 without");

		AssertExceptions<Exceptions::Core::invalid_argument>("AddBCCRecipient", "recipient have empty email", "recipient email is empty", TEST::Utils::AddBCCRecipient, mail, "", "asxmdsdhfa");
		
		Assert(mail.GetBCCRecipientCount(), 8, "unchanged");
		Assert(mail.GetBCCRecipient(), expected, "unchanged - 8 recipient");
	}
}
void TEST::StructOfMail::DelEmptyBCCRecipients()
{
	{
		Protocol::SMTP::MAIL mail;
		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "already empty");
		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "simply empty");
	}
}
void TEST::StructOfMail::DelBCCRecipients()
{
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddBCCRecipient("Another user 1");
		Assert(mail.GetBCCRecipientCount(), 1, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetBCCRecipient(), expected, "not expected elements");
	}
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddBCCRecipient("Another user 11");
		mail.AddBCCRecipient("Another user 22");
		mail.AddBCCRecipient("Another user 33");
		Assert(mail.GetBCCRecipientCount(), 3, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetBCCRecipient(), expected, "not expected elements");
	}
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddBCCRecipient("qwerty1");
		mail.AddBCCRecipient("qwerty2");
		mail.AddBCCRecipient("Another user 1");
		mail.AddBCCRecipient("Another user 2");
		mail.AddBCCRecipient("Another user 3");
		mail.AddBCCRecipient("Another user 4");
		mail.AddBCCRecipient("  11 user ");
		mail.AddBCCRecipient(" 234user");
		Assert(mail.GetBCCRecipientCount(), 8, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetBCCRecipient(), expected, "not expected elements");
	}
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
		Assert(mail.GetBCCRecipientCount(), 8, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetBCCRecipient(), expected, "not expected elements");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.AddBCCRecipient("qwerty1", "qwerty1");
		mail.AddBCCRecipient("qwerty2", "name of qwerty2");
		mail.AddBCCRecipient("Another user 1", "some_name");
		Assert(mail.GetBCCRecipientCount(), 3, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.AddBCCRecipient("Another user 2");
		mail.AddBCCRecipient("Another user 3", "asqwedaszxcQWEAS_____-- as3 235");
		mail.AddBCCRecipient("Another user 4", " 12983 klj    ");
		mail.AddBCCRecipient("  11 user ");
		mail.AddBCCRecipient(" 234user", "YYYY-QQQQ");
		mail.AddBCCRecipient("qwerty1", "qwerty1");
		mail.AddBCCRecipient("qwerty2", "name of qwerty2");
		mail.AddBCCRecipient("Another user 1", "some_name");
		Assert(mail.GetBCCRecipientCount(), 8, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.AddBCCRecipient("Another user 2");
		mail.AddBCCRecipient("Another user 3", "asqwedaszxcQWEAS_____-- as3 235");
		mail.AddBCCRecipient("Another user 4", " 12983 klj    ");
		mail.AddBCCRecipient("  11 user ");
		mail.AddBCCRecipient(" 234user", "YYYY-QQQQ");
		mail.AddBCCRecipient("qwerty1", "qwerty1");
		mail.AddBCCRecipient("qwerty2", "name of qwerty2");
		mail.AddBCCRecipient("Another user 1", "some_name");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "already empty");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "simply empty");
	}
}
void TEST::StructOfMail::AddBCCRecipientBeforeDel()
{
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddBCCRecipient("Another user 1");
		Assert(mail.GetBCCRecipientCount(), 1, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetBCCRecipient(), expected, "not expected elements");

		mail.AddBCCRecipient("Another user 1");
		expected["Another user 1"] = "";
		Assert(mail.GetBCCRecipient(), expected, "add recipient");
		Assert(mail.GetBCCRecipientCount(), 1, "add recipient");
	}
	{
		Protocol::SMTP::MAIL mail;
		Protocol::SMTP::MAIL::Recipients expected;
		mail.AddBCCRecipient("Another user 1");
		mail.AddBCCRecipient("Another user 11");
		mail.AddBCCRecipient("Another user 1111");
		Assert(mail.GetBCCRecipientCount(), 3, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetBCCRecipient(), expected, "not expected elements");

		mail.AddBCCRecipient("IEU sd9 0 f03i;akp", "555");
		mail.AddBCCRecipient("i09e:Dkoi ;3ok;dA skpf");
		expected["IEU sd9 0 f03i;akp"] = "555";
		expected["i09e:Dkoi ;3ok;dA skpf"] = "";
		Assert(mail.GetBCCRecipient(), expected, "add recipient");
		Assert(mail.GetBCCRecipientCount(), 2, "add recipient");
	}
	{
		Protocol::SMTP::MAIL mail;
		mail.AddBCCRecipient("qwerty1");
		mail.AddBCCRecipient("qwerty2");
		mail.AddBCCRecipient("Another user 1");
		mail.AddBCCRecipient("Another user 2");
		mail.AddBCCRecipient("Another user 3");
		mail.AddBCCRecipient("Another user 4");
		mail.AddBCCRecipient("  11 user ");
		mail.AddBCCRecipient(" 234user");
		Assert(mail.GetBCCRecipientCount(), 8, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");

		mail.AddBCCRecipient("Another user 1");
		mail.AddBCCRecipient("Another user 2");
		mail.AddBCCRecipient("Another user 3");
		mail.AddBCCRecipient("Another user 4");
		Assert(mail.GetBCCRecipientCount(), 4, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
	}
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
		mail.AddBCCRecipient("1101111");
		mail.AddBCCRecipient("222202");
		mail.AddBCCRecipient("10011111");
		mail.AddBCCRecipient("0222202");
		mail.AddBCCRecipient("10111011");
		mail.AddBCCRecipient("22002022");
		mail.AddBCCRecipient("010110111");
		mail.AddBCCRecipient("2200020220");
		Assert(mail.GetBCCRecipientCount(), 16, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetBCCRecipient(), expected, "not expected elements");
		mail.AddBCCRecipient("Another user 1");
		expected["Another user 1"];
		Assert(mail.GetBCCRecipient(), expected, "add recipient");
		Assert(mail.GetBCCRecipientCount(), 1, "add recipient");
		mail.AddBCCRecipient("22222");
		expected["22222"] = "";
		Assert(mail.GetBCCRecipient(), expected, "add recipient");
		Assert(mail.GetBCCRecipientCount(), 2, "add recipient");
		mail.DelBCCRecipients();
		expected.clear();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetBCCRecipient(), expected, "not expected elements");
	}
}
void TEST::StructOfMail::DefXPriority()
{
	Protocol::SMTP::MAIL mail;
	Assert(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL, "priority by default");
}
void TEST::StructOfMail::DefXMailer()
{
	Protocol::SMTP::MAIL mail;
	Assert(mail.GetXMailer(), Protocol::SMTP::XMAILER, "XMailer by default");
}
void TEST::StructOfMail::SetXPriority()
{
	Protocol::SMTP::MAIL mail;
	Assert(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL, "priority by default");
	mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
	Assert(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL, "set priority");
	mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::HIGH);
	Assert(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::HIGH, "change priority");
	mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::LOW);
	Assert(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::LOW, "change priority");
	mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
	Assert(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL, "change priority");
	mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
	Assert(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL, "change priority");
	mail.SetXPriority(Protocol::SMTP::MAIL::PRIORITY::NORMAL);
	Assert(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL, "change priority");
	mail.SetXPriority();
	Assert(mail.GetXPriority(), Protocol::SMTP::MAIL::PRIORITY::NORMAL, "set priority by default");
}
void TEST::StructOfMail::SetXMailer()
{
	Protocol::SMTP::MAIL mail;
	mail.SetXMailer("AopjopjsG9d04k;SDg=-3dsgDS");
	Assert(mail.GetXMailer(), "AopjopjsG9d04k;SDg=-3dsgDS", "set XMailer");
	mail.SetXMailer("");
	Assert(mail.GetXMailer(), "", "change XMailer");
	mail.SetXMailer("1234568752457780957");
	Assert(mail.GetXMailer(), "1234568752457780957", "change XMailer");
	mail.SetXMailer("IAhjio34   sad0-9 3");
	Assert(mail.GetXMailer(), "IAhjio34   sad0-9 3", "change XMailer");
	mail.SetXMailer("42j90,m9a 90as");
	Assert(mail.GetXMailer(), "42j90,m9a 90as", "change XMailer");
	mail.SetXMailer("=--(_io3;k2os89)&9sa");
	Assert(mail.GetXMailer(), "=--(_io3;k2os89)&9sa", "change XMailer");
}
void TEST::StructOfMail::DefLetterBody()
{
	Protocol::SMTP::MAIL mail;
	Assert(mail.GetBodySize(), 0, "letter must be empty by default");
}
void TEST::StructOfMail::AddMsgLine()
{
	{
		Protocol::SMTP::MAIL mail;
		vector<string> expected;
		mail.AddMsgLine("Hello,");
		expected.push_back("Hello,");
		Assert(mail.GetBodySize(), 1, "add line to msg");
		Assert(mail.GetBody(), expected, "add line to msg");
		mail.AddMsgLine("");
		expected.push_back("");
		Assert(mail.GetBodySize(), 2, "add line to msg");
		Assert(mail.GetBody(), expected, "add line to msg");
		mail.AddMsgLine("...");
		expected.push_back("...");
		Assert(mail.GetBodySize(), 3, "add line to msg");
		Assert(mail.GetBody(), expected, "add line to msg");
		mail.AddMsgLine("How are you today?");
		expected.push_back("How are you today?");
		Assert(mail.GetBodySize(), 4, "add line to msg");
		Assert(mail.GetBody(), expected, "add line to msg");
		mail.AddMsgLine("");
		expected.push_back("");
		Assert(mail.GetBodySize(), 5, "add line to msg");
		Assert(mail.GetBody(), expected, "add line to msg");
		mail.AddMsgLine("Regards");
		expected.push_back("Regards");
		Assert(mail.GetBodySize(), 6, "add line to msg");
		Assert(mail.GetBody(), expected, "add line to msg");
	}
	{
		Protocol::SMTP::MAIL mail;
		vector<string> expected;
		mail.AddMsgLine("");
		expected.push_back("");
		Assert(mail.GetBodySize(), 1, "add line to msg");
		Assert(mail.GetBody(), expected, "add line to msg");
		mail.AddMsgLine("");
		expected.push_back("");
		Assert(mail.GetBodySize(), 2, "add line to msg");
		Assert(mail.GetBody(), expected, "add line to msg");
		mail.AddMsgLine("                    ");
		expected.push_back("                    ");
		Assert(mail.GetBodySize(), 3, "add line to msg");
		Assert(mail.GetBody(), expected, "add line to msg");
		mail.AddMsgLine(" ");
		expected.push_back(" ");
		Assert(mail.GetBodySize(), 4, "add line to msg");
		Assert(mail.GetBody(), expected, "add line to msg");
		mail.AddMsgLine("");
		expected.push_back("");
		Assert(mail.GetBodySize(), 5, "add line to msg");
		Assert(mail.GetBody(), expected, "add line to msg");
		mail.AddMsgLine("              24h8340-cre23fsw-          ");
		expected.push_back("              24h8340-cre23fsw-          ");
		Assert(mail.GetBodySize(), 6, "add line to msg");
		Assert(mail.GetBody(), expected, "add line to msg");
	}
}
void TEST::StructOfMail::ModMsgLine()
{
	Protocol::SMTP::MAIL mail;
	vector<string> expected;
	mail.AddMsgLine("Hello,");
	expected.push_back("Hello,");
	Assert(mail.GetBodySize(), 1, "add line to msg");
	Assert(mail.GetBody(), expected, "add line to msg");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, 1, "");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, -9, " y54 zay5 8569");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, 567, "46346174");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, 2, "asdg y");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, 36965, " ");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, 67, "");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, -4577, "wsr sh");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, -1, "rty");
	mail.ModMsgLine(0, "Hey hey heeeeeeey,");
	expected[0] = "Hey hey heeeeeeey,";
	Assert(mail.GetBodySize(), 1, "mod line of msg");
	Assert(mail.GetBody(), expected, "mod line of msg");
	mail.AddMsgLine("");
	expected.push_back("");
	Assert(mail.GetBodySize(), 2, "add line to msg");
	Assert(mail.GetBody(), expected, "add line to msg");
	mail.AddMsgLine("...");
	expected.push_back("...");
	Assert(mail.GetBodySize(), 3, "add line to msg");
	Assert(mail.GetBody(), expected, "add line to msg");
	mail.AddMsgLine("How are you today?");
	expected.push_back("How are you today?");
	Assert(mail.GetBodySize(), 4, "add line to msg");
	Assert(mail.GetBody(), expected, "add line to msg");
	mail.AddMsgLine("");
	expected.push_back("");
	Assert(mail.GetBodySize(), 5, "add line to msg");
	Assert(mail.GetBody(), expected, "add line to msg");
	mail.ModMsgLine(4, "empty line");
	expected[4] = "empty line";
	Assert(mail.GetBodySize(), 5, "mod line of msg");
	Assert(mail.GetBody(), expected, "mod line of msg");
	mail.AddMsgLine("Regards");
	expected.push_back("Regards");
	Assert(mail.GetBodySize(), 6, "add line to msg");
	Assert(mail.GetBody(), expected, "add line to msg");
	mail.ModMsgLine(5, "regards");
	expected[5] = "regards";
	Assert(mail.GetBodySize(), 6, "mod line of msg");
	Assert(mail.GetBody(), expected, "mod line of msg");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, 6, "");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, 6, " y54 zay5 8569");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, 66, "46346174");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, 58, "asdg y");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, 16458, " ");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, 6479, "");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, -457, "wsr sh");
	AssertExceptions<Exceptions::Core::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::Utils::ModMsgLine, mail, -1, "rty");
}
void TEST::StructOfMail::DelMsgLine()
{
	Protocol::SMTP::MAIL mail;
	vector<string> expected;
	AssertExceptions<Exceptions::Core::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::Utils::DelMsgLine, mail, 1);
	AssertExceptions<Exceptions::Core::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::Utils::DelMsgLine, mail, 3);
	mail.AddMsgLine("Hello,");
	expected.push_back("Hello,");
	Assert(mail.GetBodySize(), 1, "add line to msg");
	Assert(mail.GetBody(), expected, "add line to msg");
	mail.ModMsgLine(0, "Hey hey heeeeeeey,");
	expected[0] = "Hey hey heeeeeeey,";
	Assert(mail.GetBodySize(), 1, "mod line of msg");
	Assert(mail.GetBody(), expected, "mod line of msg");
	mail.DelMsgLine(0);
	expected.erase(expected.begin());
	Assert(mail.GetBodySize(), 0, "del line of msg");
	Assert(mail.GetBody(), expected, "del line of msg");
	mail.AddMsgLine("");
	expected.push_back("");
	Assert(mail.GetBodySize(), 1, "add line to msg");
	Assert(mail.GetBody(), expected, "add line to msg");
	mail.DelMsgLine(0);
	expected.erase(expected.begin());
	Assert(mail.GetBodySize(), 0, "del line of msg");
	Assert(mail.GetBody(), expected, "del line of msg");
	mail.AddMsgLine("...");
	expected.push_back("...");
	Assert(mail.GetBodySize(), 1, "add line to msg");
	Assert(mail.GetBody(), expected, "add line to msg");
	mail.AddMsgLine("How are you today?");
	expected.push_back("How are you today?");
	Assert(mail.GetBodySize(), 2, "add line to msg");
	Assert(mail.GetBody(), expected, "add line to msg");
	mail.AddMsgLine("");
	expected.push_back("");
	Assert(mail.GetBodySize(), 3, "add line to msg");
	Assert(mail.GetBody(), expected, "add line to msg");
	mail.ModMsgLine(2, "empty line");
	expected[2] = "empty line";
	Assert(mail.GetBodySize(), 3, "mod line of msg");
	Assert(mail.GetBody(), expected, "mod line of msg");
	mail.AddMsgLine("Regards");
	expected.push_back("Regards");
	Assert(mail.GetBodySize(), 4, "add line to msg");
	Assert(mail.GetBody(), expected, "add line to msg");
	mail.ModMsgLine(3, "regards");
	expected[3] = "regards";
	Assert(mail.GetBodySize(), 4, "mod line of msg");
	Assert(mail.GetBody(), expected, "mod line of msg");
	mail.DelMsgLine(0);
	expected.erase(expected.begin());
	Assert(mail.GetBodySize(), 3, "del line of msg");
	Assert(mail.GetBody(), expected, "del line of msg");
	mail.DelMsgLine(1);
	expected.erase(expected.begin()+1);
	Assert(mail.GetBodySize(), 2, "del line of msg");
	Assert(mail.GetBody(), expected, "del line of msg");
	AssertExceptions<Exceptions::Core::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::Utils::DelMsgLine, mail, 2);
	AssertExceptions<Exceptions::Core::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::Utils::DelMsgLine, mail, 83);
	AssertExceptions<Exceptions::Core::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::Utils::DelMsgLine, mail, 3627);
	AssertExceptions<Exceptions::Core::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::Utils::DelMsgLine, mail, 557828);
}
void TEST::StructOfMail::DelEmptyMsgLine()
{
	Protocol::SMTP::MAIL mail;
	AssertExceptions<Exceptions::Core::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::Utils::DelMsgLine, mail, 0);
	AssertExceptions<Exceptions::Core::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::Utils::DelMsgLine, mail, 10);
	AssertExceptions<Exceptions::Core::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::Utils::DelMsgLine, mail, 10000000);
	AssertExceptions<Exceptions::Core::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::Utils::DelMsgLine, mail, 154376);
	AssertExceptions<Exceptions::Core::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::Utils::DelMsgLine, mail, -384018);
	AssertExceptions<Exceptions::Core::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::Utils::DelMsgLine, mail, -0);
	AssertExceptions<Exceptions::Core::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::Utils::DelMsgLine, mail, -1);
}
void TEST::StructOfMail::DelMsgLines()
{
	{
		Protocol::SMTP::MAIL mail;
		vector<string> expected;
		mail.AddMsgLine("Hello,");
		expected.push_back("Hello,");

		mail.DelMsgLines();
		expected.clear();
		Assert(mail.GetBodySize(), 0, "del all lines of msg");
		Assert(mail.GetBody(), expected, "del all lines of msg");
	}
	{
		Protocol::SMTP::MAIL mail;
		vector<string> expected;
		mail.AddMsgLine("Hello,");
		mail.AddMsgLine("...");
		mail.AddMsgLine("...");
		mail.AddMsgLine("...");
		mail.AddMsgLine("...");
		Assert(mail.GetBodySize(), 5, "add line to msg");

		mail.DelMsgLines();
		expected.clear();
		Assert(mail.GetBodySize(), 0, "del all lines of msg");
		Assert(mail.GetBody(), expected, "del all lines of msg");
	}
	{
		Protocol::SMTP::MAIL mail;
		vector<string> expected;
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
		Assert(mail.GetBodySize(), 2, "del line of msg");
		Assert(mail.GetBody(), expected, "del line of msg");

		mail.DelMsgLines();
		expected.clear();
		Assert(mail.GetBodySize(), 0, "del all lines of msg");
		Assert(mail.GetBody(), expected, "del all lines of msg");

		mail.AddMsgLine("regards");
		expected.push_back("regards");
		mail.AddMsgLine("regards");
		expected.push_back("regards");
		Assert(mail.GetBodySize(), 2, "add line to msg");
		Assert(mail.GetBody(), expected, "mod line to msg");

		mail.DelMsgLines();
		expected.clear();
		Assert(mail.GetBodySize(), 0, "del all lines of msg");
		Assert(mail.GetBody(), expected, "del all lines of msg");
	}
}
void TEST::StructOfMail::DelEmptyMsgLines()
{
	Protocol::SMTP::MAIL mail;
	mail.DelMsgLines();
	Assert(mail.GetBodySize(), 0, "del all lines of msg");
	mail.DelMsgLines();
	Assert(mail.GetBodySize(), 0, "del all lines of msg");
	mail.AddMsgLine("...");
	mail.AddMsgLine("...");
	mail.DelMsgLines();
	Assert(mail.GetBodySize(), 0, "del all lines of msg");
	mail.AddMsgLine("...");
	mail.DelMsgLines();
	Assert(mail.GetBodySize(), 0, "del all lines of msg");
	mail.DelMsgLines();
	Assert(mail.GetBodySize(), 0, "del all lines of msg");
}
void TEST::StructOfMail::DefAttachment()
{
	Protocol::SMTP::MAIL mail;
	Assert(mail.GetAttachmentsSize(), 0, "default we have zero attachments");
}
void TEST::StructOfMail::AddAttachment()
{
	Protocol::SMTP::MAIL mail;
	AssertExceptions<Exceptions::Core::invalid_argument>("AddAttachment", "input is an empty string", "input empty path", TEST::Utils::AddAttachment, mail, "");
	mail.AddAttachment("./test-files/1.jpg");
	Assert(mail.GetAttachmentsSize(), 1, "add attachment");
	mail.AddAttachment("./test-files/2.app");
	Assert(mail.GetAttachmentsSize(), 2, "add attachment");
	mail.AddAttachment("./test-files/3.bin");
	Assert(mail.GetAttachmentsSize(), 3, "add attachment");

	AssertExceptions<Exceptions::Core::invalid_argument>("AddAttachment", "input is an empty string", "input empty path", TEST::Utils::AddAttachment, mail, "");

	mail.AddAttachment("./test-files/4.bgm");
	Assert(mail.GetAttachmentsSize(), 4, "add attachment");
	mail.AddAttachment("./test-files/5.txt");
	Assert(mail.GetAttachmentsSize(), 5, "add attachment");
	mail.AddAttachment("./test-files/5.qwerty");
	Assert(mail.GetAttachmentsSize(), 6, "add attachment");

	AssertExceptions<Exceptions::Core::invalid_argument>("AddAttachment", "input is an empty string", "input empty path", TEST::Utils::AddAttachment, mail, "");
}
void TEST::StructOfMail::DelAttachments()
{
	Protocol::SMTP::MAIL mail;
	mail.AddAttachment("./test-files/1.jpg");
	mail.AddAttachment("./test-files/2.app");
	mail.AddAttachment("./test-files/3.bin");
	Assert(mail.GetAttachmentsSize(), 3, "add attachment");
	
	mail.DelAttachments();
	Assert(mail.GetAttachmentsSize(), 0, "del attachment");

	mail.AddAttachment("./test-files/4.bgm");
	mail.AddAttachment("./test-files/5.txt");
	mail.AddAttachment("./test-files/5.qwerty");
	mail.AddAttachment("./test-files/1.jpg");
	mail.AddAttachment("./test-files/2.app");
	mail.AddAttachment("./test-files/3.bin");
	Assert(mail.GetAttachmentsSize(), 6, "add attachment");

	mail.DelAttachments();
	Assert(mail.GetAttachmentsSize(), 0, "del attachment");
}
void TEST::StructOfMail::DelEmptyAttachments()
{
	Protocol::SMTP::MAIL mail;

	mail.DelAttachments();
	Assert(mail.GetAttachmentsSize(), 0, "empty");

	mail.DelAttachments();
	Assert(mail.GetAttachmentsSize(), 0, "empty");

	mail.DelAttachments();
	Assert(mail.GetAttachmentsSize(), 0, "empty");

	mail.AddAttachment("./test-files/4.bgm");
	mail.AddAttachment("./test-files/5.txt");

	mail.DelAttachments();
	Assert(mail.GetAttachmentsSize(), 0, "del attachment");

	mail.DelAttachments();
	Assert(mail.GetAttachmentsSize(), 0, "already empty");

	mail.AddAttachment("./test-files/4.bgm");
	mail.AddAttachment("./test-files/5.txt");
	mail.AddAttachment("./test-files/5.qwerty");
	mail.AddAttachment("./test-files/1.jpg");
	mail.AddAttachment("./test-files/2.app");
	mail.AddAttachment("./test-files/3.bin");
	Assert(mail.GetAttachmentsSize(), 6, "add attachment");

	mail.DelAttachments();
	Assert(mail.GetAttachmentsSize(), 0, "del attachment");

	mail.DelAttachments();
	Assert(mail.GetAttachmentsSize(), 0, "already empty");
}

void TEST::Client::DefAuth()
{
	Protocol::SMTP::Client client;
	Assert(client.GetLogin(), "", "empty by default");
	Assert(client.GetPassword(), "", "empty by default");
}
void TEST::Client::SetAuth()
{
	Protocol::SMTP::Client client;
	client.SetLogin("qwerty");
	client.SetPassword("password___");
	Assert(client.GetLogin(), "qwerty", "set up login is incorrect");
	Assert(client.GetPassword(), "password___", "set up password is incorrect");
}
void TEST::Client::SendExceptionss()
{
	Protocol::SMTP::MAIL mail;
	Protocol::SMTP::Client client;

	AssertExceptions<Exceptions::Core::invalid_argument>("client send", "sender mail is not specified", "empty sender mail", TEST::Utils::ClientSend, client, mail);

	mail.SetSenderMail("qwerty");

	AssertExceptions<Exceptions::Core::invalid_argument>("client send", "recipient mail is not specified", "empty receiver mail", TEST::Utils::ClientSend, client, mail);
}
