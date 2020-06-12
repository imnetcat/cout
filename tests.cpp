#include "tests.h"
using namespace std;
void TEST::UTILS::ModMsgLine(EMAIL::MAIL& mail, unsigned int Line, const char* Text)
{
	mail.ModMsgLine(Line, Text);
}
void TEST::UTILS::DelMsgLine(EMAIL::MAIL& mail, unsigned int Line)
{
	mail.DelMsgLine(Line);
}
void TEST::UTILS::AddRecipient(EMAIL::MAIL& mail, const char* email, const char* name)
{
	mail.AddRecipient(email, name);
}
void TEST::UTILS::AddCCRecipient(EMAIL::MAIL& mail, const char* email, const char* name)
{
	mail.AddCCRecipient(email, name);
}
void TEST::UTILS::AddBCCRecipient(EMAIL::MAIL& mail, const char* email, const char* name)
{
	mail.AddBCCRecipient(email, name);
}
void TEST::UTILS::AddAttachment(EMAIL::MAIL& mail, const char* path)
{
	mail.AddAttachment(path);
}
void TEST::UTILS::SetAuth(EMAIL::Client& client, const char* login, const char* pass)
{
	client.SetAuth(login, pass);
}
void TEST::UTILS::ClientSend(EMAIL::Client client, EMAIL::MAIL mail)
{
	client.send(mail);
}
void TEST::StructOfMail::SetSenderName()
{
	EMAIL::MAIL mail;
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
	EMAIL::MAIL mail;
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
	EMAIL::MAIL mail;
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
	EMAIL::MAIL mail;
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
	EMAIL::MAIL mail;
	EMAIL::MAIL::Recipients expected;
	Assert(mail.GetRecipientCount(), 0, "zero by default");
	Assert(mail.GetRecipient(), expected, "zero by default");
}
void TEST::StructOfMail::AddRecipient()
{
	{
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
		
		AssertException<CORE::Exception::invalid_argument>("AddRecipient", "recipient have empty email", "recipient email is empty", TEST::UTILS::AddRecipient, mail, "", "");
		
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

		AssertException<CORE::Exception::invalid_argument>("AddRecipient", "recipient have empty email", "recipient email is empty", TEST::UTILS::AddRecipient, mail, "", "");

		Assert(mail.GetRecipientCount(), 8, "unchanged");
		Assert(mail.GetRecipient(), expected, "unchanged - 8 recipient");
	}
	{
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;

		AssertException<CORE::Exception::invalid_argument>("AddRecipient", "recipient have empty email", "recipient email is empty", TEST::UTILS::AddRecipient, mail, "", "123");
		
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

		AssertException<CORE::Exception::invalid_argument>("AddRecipient", "recipient have empty email", "recipient email is empty", TEST::UTILS::AddRecipient, mail, "", "name");

		Assert(mail.GetRecipientCount(), 8, "unchanged");
		Assert(mail.GetRecipient(), expected, "unchanged - 8 recipient");
	}
}
void TEST::StructOfMail::DelEmptyRecipients()
{
	{
		EMAIL::MAIL mail;
		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
	}
	{
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
		mail.AddRecipient("Another user 1");
		Assert(mail.GetRecipientCount(), 1, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
		Assert(mail.GetRecipient(), expected, "not expected elements");
	}
	{
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
		mail.AddRecipient("Another user 1");
		Assert(mail.GetRecipientCount(), 1, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
		Assert(mail.GetRecipient(), expected, "not expected elements");
	}
	{
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
		EMAIL::MAIL mail;
		mail.AddRecipient("qwerty1", "qwerty1");
		mail.AddRecipient("qwerty2", "name of qwerty2");
		mail.AddRecipient("Another user 1", "some_name");
		Assert(mail.GetRecipientCount(), 3, "add recipient");

		mail.DelRecipients();
		Assert(mail.GetRecipientCount(), 0, "remove recipients");
	}
	{
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
	EMAIL::MAIL mail;
	EMAIL::MAIL::Recipients expected;
	Assert(mail.GetCCRecipientCount(), 0, "zero by default");
	Assert(mail.GetCCRecipient(), expected, "zero by default");
}
void TEST::StructOfMail::AddCCRecipient()
{
	{
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;

		AssertException<CORE::Exception::invalid_argument>("AddCCRecipient", "recipient have empty email", "recipient email is empty", TEST::UTILS::AddCCRecipient, mail, "", "");

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

		AssertException<CORE::Exception::invalid_argument>("AddCCRecipient", "recipient have empty email", "recipient email is empty", TEST::UTILS::AddCCRecipient, mail, "", "");
		
		Assert(mail.GetCCRecipientCount(), 8, "unchanged");
		Assert(mail.GetCCRecipient(), expected, "unchanged - 8 recipient");
	}
	{
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;

		AssertException<CORE::Exception::invalid_argument>("AddCCRecipient", "recipient have empty email", "recipient email is empty", TEST::UTILS::AddCCRecipient, mail, "", "12 975  846");
		
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

		AssertException<CORE::Exception::invalid_argument>("AddCCRecipient", "recipient have empty email", "recipient email is empty", TEST::UTILS::AddCCRecipient, mail, "", "srtu5gsq");
		
		Assert(mail.GetCCRecipientCount(), 8, "unchanged");
		Assert(mail.GetCCRecipient(), expected, "unchanged - 8 recipient");
	}
}
void TEST::StructOfMail::DelEmptyCCRecipients()
{
	{
		EMAIL::MAIL mail;
		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
	}
	{
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
		mail.AddCCRecipient("Another user 1");
		Assert(mail.GetCCRecipientCount(), 1, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetCCRecipient(), expected, "not expected elements");
	}
	{
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
		mail.AddCCRecipient("Another user 1");
		mail.AddCCRecipient("Another user 2");
		mail.AddCCRecipient("Another user 3");
		Assert(mail.GetCCRecipientCount(), 3, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetCCRecipient(), expected, "not expected elements");
	}
	{
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
		EMAIL::MAIL mail;
		mail.AddCCRecipient("qwerty1", "qwerty1");
		mail.AddCCRecipient("qwerty2", "name of qwerty2");
		mail.AddCCRecipient("Another user 1", "some_name");
		Assert(mail.GetCCRecipientCount(), 3, "add recipient");

		mail.DelCCRecipients();
		Assert(mail.GetCCRecipientCount(), 0, "remove recipients");
	}
	{
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
	EMAIL::MAIL mail;
	EMAIL::MAIL::Recipients expected;
	Assert(mail.GetBCCRecipientCount(), 0, "zero by default");
	Assert(mail.GetBCCRecipient(), expected, "zero by default");
}
void TEST::StructOfMail::AddBCCRecipient()
{
	{
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;

		AssertException<CORE::Exception::invalid_argument>("AddBCCRecipient", "recipient have empty email", "recipient email is empty", TEST::UTILS::AddBCCRecipient, mail, "", "");
		
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

		AssertException<CORE::Exception::invalid_argument>("AddBCCRecipient", "recipient have empty email", "recipient email is empty", TEST::UTILS::AddBCCRecipient, mail, "", "");
		
		Assert(mail.GetBCCRecipientCount(), 8, "unchanged");
		Assert(mail.GetBCCRecipient(), expected, "unchanged - 8 recipient");
	}
	{
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;

		AssertException<CORE::Exception::invalid_argument>("AddBCCRecipient", "recipient have empty email", "recipient email is empty", TEST::UTILS::AddBCCRecipient, mail, "", "124563-907");
		
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

		AssertException<CORE::Exception::invalid_argument>("AddBCCRecipient", "recipient have empty email", "recipient email is empty", TEST::UTILS::AddBCCRecipient, mail, "", "asxmdsdhfa");
		
		Assert(mail.GetBCCRecipientCount(), 8, "unchanged");
		Assert(mail.GetBCCRecipient(), expected, "unchanged - 8 recipient");
	}
}
void TEST::StructOfMail::DelEmptyBCCRecipients()
{
	{
		EMAIL::MAIL mail;
		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
	}
	{
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
		mail.AddBCCRecipient("Another user 1");
		Assert(mail.GetBCCRecipientCount(), 1, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetBCCRecipient(), expected, "not expected elements");
	}
	{
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
		mail.AddBCCRecipient("Another user 11");
		mail.AddBCCRecipient("Another user 22");
		mail.AddBCCRecipient("Another user 33");
		Assert(mail.GetBCCRecipientCount(), 3, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
		Assert(mail.GetBCCRecipient(), expected, "not expected elements");
	}
	{
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
		EMAIL::MAIL mail;
		mail.AddBCCRecipient("qwerty1", "qwerty1");
		mail.AddBCCRecipient("qwerty2", "name of qwerty2");
		mail.AddBCCRecipient("Another user 1", "some_name");
		Assert(mail.GetBCCRecipientCount(), 3, "add recipient");

		mail.DelBCCRecipients();
		Assert(mail.GetBCCRecipientCount(), 0, "remove recipients");
	}
	{
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
		EMAIL::MAIL::Recipients expected;
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
	EMAIL::MAIL mail;
	Assert(mail.GetXPriority(), EMAIL::MAIL::PRIORITY::NORMAL, "priority by default");
}
void TEST::StructOfMail::DefXMailer()
{
	EMAIL::MAIL mail;
	Assert(mail.GetXMailer(), EMAIL::XMAILER, "XMailer by default");
}
void TEST::StructOfMail::SetXPriority()
{
	EMAIL::MAIL mail;
	Assert(mail.GetXPriority(), EMAIL::MAIL::PRIORITY::NORMAL, "priority by default");
	mail.SetXPriority(EMAIL::MAIL::PRIORITY::NORMAL);
	Assert(mail.GetXPriority(), EMAIL::MAIL::PRIORITY::NORMAL, "set priority");
	mail.SetXPriority(EMAIL::MAIL::PRIORITY::HIGH);
	Assert(mail.GetXPriority(), EMAIL::MAIL::PRIORITY::HIGH, "change priority");
	mail.SetXPriority(EMAIL::MAIL::PRIORITY::LOW);
	Assert(mail.GetXPriority(), EMAIL::MAIL::PRIORITY::LOW, "change priority");
	mail.SetXPriority(EMAIL::MAIL::PRIORITY::NORMAL);
	Assert(mail.GetXPriority(), EMAIL::MAIL::PRIORITY::NORMAL, "change priority");
	mail.SetXPriority(EMAIL::MAIL::PRIORITY::NORMAL);
	Assert(mail.GetXPriority(), EMAIL::MAIL::PRIORITY::NORMAL, "change priority");
	mail.SetXPriority(EMAIL::MAIL::PRIORITY::NORMAL);
	Assert(mail.GetXPriority(), EMAIL::MAIL::PRIORITY::NORMAL, "change priority");
	mail.SetXPriority();
	Assert(mail.GetXPriority(), EMAIL::MAIL::PRIORITY::NORMAL, "set priority by default");
}
void TEST::StructOfMail::SetXMailer()
{
	EMAIL::MAIL mail;
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
	EMAIL::MAIL mail;
	Assert(mail.GetBodySize(), 0, "letter must be empty by default");
}
void TEST::StructOfMail::AddMsgLine()
{
	{
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
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
	EMAIL::MAIL mail;
	vector<string> expected;
	mail.AddMsgLine("Hello,");
	expected.push_back("Hello,");
	Assert(mail.GetBodySize(), 1, "add line to msg");
	Assert(mail.GetBody(), expected, "add line to msg");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, 1, "");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, -9, " y54 zay5 8569");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, 567, "46346174");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, 2, "asdg y");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, 36965, " ");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, 67, "");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, -4577, "wsr sh");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, -1, "rty");
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
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, 6, "");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, 6, " y54 zay5 8569");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, 66, "46346174");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, 58, "asdg y");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, 16458, " ");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, 6479, "");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, -457, "wsr sh");
	AssertException<CORE::Exception::out_of_range>("ModMsgLine", "input line index that more than body size", "modify line of message body", TEST::UTILS::ModMsgLine, mail, -1, "rty");
}
void TEST::StructOfMail::DelMsgLine()
{
	EMAIL::MAIL mail;
	vector<string> expected;
	AssertException<CORE::Exception::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::UTILS::DelMsgLine, mail, 1);
	AssertException<CORE::Exception::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::UTILS::DelMsgLine, mail, 3);
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
	AssertException<CORE::Exception::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::UTILS::DelMsgLine, mail, 2);
	AssertException<CORE::Exception::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::UTILS::DelMsgLine, mail, 83);
	AssertException<CORE::Exception::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::UTILS::DelMsgLine, mail, 3627);
	AssertException<CORE::Exception::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::UTILS::DelMsgLine, mail, 557828);
}
void TEST::StructOfMail::DelEmptyMsgLine()
{
	EMAIL::MAIL mail;
	AssertException<CORE::Exception::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::UTILS::DelMsgLine, mail, 0);
	AssertException<CORE::Exception::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::UTILS::DelMsgLine, mail, 10);
	AssertException<CORE::Exception::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::UTILS::DelMsgLine, mail, 10000000);
	AssertException<CORE::Exception::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::UTILS::DelMsgLine, mail, 154376);
	AssertException<CORE::Exception::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::UTILS::DelMsgLine, mail, -384018);
	AssertException<CORE::Exception::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::UTILS::DelMsgLine, mail, -0);
	AssertException<CORE::Exception::out_of_range>("DelMsgLine", "input line index that more than body size", "deleting line of message body", TEST::UTILS::DelMsgLine, mail, -1);
}
void TEST::StructOfMail::DelMsgLines()
{
	{
		EMAIL::MAIL mail;
		vector<string> expected;
		mail.AddMsgLine("Hello,");
		expected.push_back("Hello,");

		mail.DelMsgLines();
		expected.clear();
		Assert(mail.GetBodySize(), 0, "del all lines of msg");
		Assert(mail.GetBody(), expected, "del all lines of msg");
	}
	{
		EMAIL::MAIL mail;
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
		EMAIL::MAIL mail;
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
	EMAIL::MAIL mail;
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
	EMAIL::MAIL mail;
	Assert(mail.GetAttachmentsSize(), 0, "default we have zero attachments");
}
void TEST::StructOfMail::AddAttachment()
{
	EMAIL::MAIL mail;
	AssertException<CORE::Exception::invalid_argument>("AddAttachment", "input is an empty string", "input empty path", TEST::UTILS::AddAttachment, mail, "");
	mail.AddAttachment("./test-files/1.jpg");
	Assert(mail.GetAttachmentsSize(), 1, "add attachment");
	mail.AddAttachment("./test-files/2.app");
	Assert(mail.GetAttachmentsSize(), 2, "add attachment");
	mail.AddAttachment("./test-files/3.bin");
	Assert(mail.GetAttachmentsSize(), 3, "add attachment");

	AssertException<CORE::Exception::invalid_argument>("AddAttachment", "input is an empty string", "input empty path", TEST::UTILS::AddAttachment, mail, "");

	mail.AddAttachment("./test-files/4.bgm");
	Assert(mail.GetAttachmentsSize(), 4, "add attachment");
	mail.AddAttachment("./test-files/5.txt");
	Assert(mail.GetAttachmentsSize(), 5, "add attachment");
	mail.AddAttachment("./test-files/5.qwerty");
	Assert(mail.GetAttachmentsSize(), 6, "add attachment");

	AssertException<CORE::Exception::invalid_argument>("AddAttachment", "input is an empty string", "input empty path", TEST::UTILS::AddAttachment, mail, "");
}
void TEST::StructOfMail::DelAttachments()
{
	EMAIL::MAIL mail;
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
	EMAIL::MAIL mail;

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
void TEST::Client::DefServer()
{
	EMAIL::Client client;
	Assert(client.GetServer(), EMAIL::Client::SERVER_ID::UNDEFINED, "undefined by default");
}
void TEST::Client::SetServer()
{
	auto supps = EMAIL::Client::GetSupportedServers();
	{
		EMAIL::Client client;
		auto server_id = EMAIL::Client::GMAIL_SSL;
		client.SetServer(server_id);
		Assert(supps.at(server_id).isAuth, client.IsAuthRequired(), "set up auth server param is incorect");
		Assert(supps.at(server_id).reqExt, client.IsExtRequired(), "set up extensions server param is incorect");
		Assert((supps.at(server_id).sec != EMAIL::ESMTPS::SMTP_SECURITY_TYPE::NO_SECURITY),
			client.IsEncrypRequired(), "set up encryption server param is incorect");
	}
	{
		EMAIL::Client client;
		auto server_id = EMAIL::Client::GMAIL_TLS;
		client.SetServer(server_id);
		Assert(supps.at(server_id).isAuth, client.IsAuthRequired(), "set up auth server param is incorect");
		Assert(supps.at(server_id).reqExt, client.IsExtRequired(), "set up extensions server param is incorect");
		Assert((supps.at(server_id).sec != EMAIL::ESMTPS::SMTP_SECURITY_TYPE::NO_SECURITY),
			client.IsEncrypRequired(), "set up encryption server param is incorect");
	}
	{
		EMAIL::Client client;
		auto server_id = EMAIL::Client::HOTMAIL_TSL;
		client.SetServer(server_id);
		Assert(supps.at(server_id).isAuth, client.IsAuthRequired(), "set up auth server param is incorect");
		Assert(supps.at(server_id).reqExt, client.IsExtRequired(), "set up extensions server param is incorect");
		Assert((supps.at(server_id).sec != EMAIL::ESMTPS::SMTP_SECURITY_TYPE::NO_SECURITY),
			client.IsEncrypRequired(), "set up encryption server param is incorect");
	}
	{
		EMAIL::Client client;
		auto server_id = EMAIL::Client::AOL_TLS;
		client.SetServer(server_id);
		Assert(supps.at(server_id).isAuth, client.IsAuthRequired(), "set up auth server param is incorect");
		Assert(supps.at(server_id).reqExt, client.IsExtRequired(), "set up extensions server param is incorect");
		Assert((supps.at(server_id).sec != EMAIL::ESMTPS::SMTP_SECURITY_TYPE::NO_SECURITY),
			client.IsEncrypRequired(), "set up encryption server param is incorect");
	}
}
void TEST::Client::DefAuth()
{
	EMAIL::Client client;
	Assert(client.GetLogin(), "", "empty by default");
	Assert(client.GetPassword(), "", "empty by default");
}
void TEST::Client::SetAuth()
{
	EMAIL::Client client;
	AssertException<CORE::Exception::invalid_argument>("SetAuth", "set up server first", "smtp server not specified", TEST::UTILS::SetAuth, client, "qwerty", "password___");
	client.SetServer(EMAIL::Client::GMAIL_SSL);
	client.SetAuth("qwerty", "password___");
	Assert(client.GetLogin(), "qwerty", "set up login is incorrect");
	Assert(client.GetPassword(), "password___", "set up password is incorrect");
}
void TEST::Client::DefSecurity()
{
	EMAIL::Client client;
	AssertBool(!client.IsEncrypRequired(), "!IsEncrypRequired", "no security by default");
}
void TEST::Client::SendExceptions()
{
	EMAIL::MAIL mail;
	EMAIL::Client client;

	AssertException<CORE::Exception::invalid_argument>("client send", "sender mail is not specified", "empty sender mail", TEST::UTILS::ClientSend, client, mail);

	mail.SetSenderMail("qwerty");

	AssertException<CORE::Exception::invalid_argument>("client send", "recipient mail is not specified", "empty receiver mail", TEST::UTILS::ClientSend, client, mail);

	mail.AddRecipient("recipient");

	AssertException<CORE::Exception::invalid_argument>("client send", "server is not specified", "smtp server not specified", TEST::UTILS::ClientSend, client, mail);

	client.SetServer(EMAIL::Client::SERVER_ID::GMAIL_SSL);

	AssertException<CORE::Exception::invalid_argument>("client send", "invalid auth", "the set auth value does not match the required server", TEST::UTILS::ClientSend, client, mail);
}
