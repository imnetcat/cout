#include "email.h"
#include "utest.h"
#include "tests.h"

#include <iostream>
#include <string>
#include <conio.h> // for _getch()
using namespace std;
using namespace CORE;

bool isAnswerTrue(string answ)
{
	for (size_t i = 0; i < answ.size(); i++)
		answ[i] = tolower(answ[i]);

	return answ == "" ||
		   answ == "y" ||
		   answ == "yes";
}

void printSupportedServers()
{
	const auto& supps = EMAIL::Client::GetSupportedServers();

	for (const auto& [id, server] : supps)
	{
		const string ext = server.reqExt ? "true" : "false";
		const string auth = server.isAuth ? "true" : "false";
		cout << "~\t   Server id:  \t" << id  << endl;
		cout << "~\t   Server name:\t" << server.name << endl;
		cout << "~\t\t Required extended smtp: \t" << ext << endl;
		cout << "~\t\t Required authentication: \t" << auth << endl;
		cout << "~\t\t Required encryption: \t\t" << server.GetSecurity() << endl;
		cout << "~\t " << endl;
	}
}

EMAIL::Client::SERVER_ID int2Id(short i)
{
	switch (i)
	{
	case 1:
		return EMAIL::Client::SERVER_ID::GMAIL_TLS;
		break;
	case 2:
		return EMAIL::Client::SERVER_ID::GMAIL_SSL;
		break;
	case 3:
		return EMAIL::Client::SERVER_ID::HOTMAIL_TSL;
		break;
	case 4:
		return EMAIL::Client::SERVER_ID::AOL_TLS;
		break;
	case 5:
		return EMAIL::Client::SERVER_ID::YAHOO_SSL;
		break;
	default:
		return EMAIL::Client::SERVER_ID::UNDEFINED;
	}
}

int main()
{
#ifdef INDEBUG	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	{
		UTEST tester;
		tester.run(TEST::StructOfMail::SetSenderName, "setting up of sender name");
		tester.run(TEST::StructOfMail::SetSenderMail, "setting up of sender mail");
		tester.run(TEST::StructOfMail::SetReplyTo, "setting up of reply mail");
		tester.run(TEST::StructOfMail::SetSubject, "setting up of letter subject");
		tester.run(TEST::StructOfMail::RecipientsDefault, "default recipient values");
		tester.run(TEST::StructOfMail::AddRecipient, "adding recipients values");
		tester.run(TEST::StructOfMail::DelEmptyRecipients, "deleting empty recipients values");
		tester.run(TEST::StructOfMail::DelRecipients, "deleting recipients values");
		tester.run(TEST::StructOfMail::AddRecipientBeforeDel, "adding recipients before deleting");
		tester.run(TEST::StructOfMail::CCRecipientsDefault, "default ccrecipient values");
		tester.run(TEST::StructOfMail::AddCCRecipient, "adding ccrecipients values");
		tester.run(TEST::StructOfMail::DelEmptyCCRecipients, "deleting empty ccrecipients values");
		tester.run(TEST::StructOfMail::DelCCRecipients, "deleting ccrecipients values");
		tester.run(TEST::StructOfMail::AddCCRecipientBeforeDel, "adding ccrecipients before deleting");
		tester.run(TEST::StructOfMail::BCCRecipientsDefault, "default bccrecipient values");
		tester.run(TEST::StructOfMail::AddBCCRecipient, "adding bccrecipients values");
		tester.run(TEST::StructOfMail::DelEmptyBCCRecipients, "deleting empty bccrecipients values");
		tester.run(TEST::StructOfMail::DelBCCRecipients, "deleting bccrecipients values");
		tester.run(TEST::StructOfMail::AddBCCRecipientBeforeDel, "adding bccrecipients before deleting");
		tester.run(TEST::StructOfMail::DefXPriority, "default XPriority value");
		tester.run(TEST::StructOfMail::SetXPriority, "setting up XPriority");
		tester.run(TEST::StructOfMail::DefXMailer, "default XMailer value");
		tester.run(TEST::StructOfMail::SetXMailer, "setting up XMailer");
		tester.run(TEST::StructOfMail::DefLetterBody, "default letter body value");
		tester.run(TEST::StructOfMail::AddMsgLine, "adding line to letter body");
		tester.run(TEST::StructOfMail::ModMsgLine, "modifying line of letter body");
		tester.run(TEST::StructOfMail::DelMsgLine, "deleting line of letter body");
		tester.run(TEST::StructOfMail::DelEmptyMsgLine, "deleting of empty line in letter body");
		tester.run(TEST::StructOfMail::DelMsgLines, "deleting all lines of letter body");
		tester.run(TEST::StructOfMail::DelEmptyMsgLines, "deleting all lines of empty letter body");
		tester.run(TEST::StructOfMail::DefAttachment, "default attachments value");
		tester.run(TEST::StructOfMail::AddAttachment, "adding attachments value");
		tester.run(TEST::StructOfMail::DelAttachments, "deleting attachments value");
		tester.run(TEST::StructOfMail::DelEmptyAttachments, "deleting of empty attachments value");
	}
#endif

	string answ;
	string name, senderEmail, replyTo, title;
	vector<string> recipient_email;
	vector<string> ccrecipient_email;
	vector<string> bccrecipient_email;
	vector<string> body;
	vector<string> attachments;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~\t\t\t     STMP Email-client demo" << endl;
	cout << "~" << endl;
	cout << "~\t  Hello, dear, let's write you letter.." << endl;
	cout << "~\t 		* do not forget enable access from untrusted" << endl;
	cout << "~\t 		  applications to your mailbox in its settings *" << endl;
	cout << "~" << endl;
	cout << "~\t  First of all," << endl;
	cout << "~\t     tell me you name: ";
	getline(cin, name);

	cout << "~" << endl;
	cout << "~\t  Okey, now I need you" << endl;
	cout << "~\t     email address: ";
	getline(cin, senderEmail);

	cout << "~" << endl;
	cout << "~\t  Send answers to the same address ?" << endl;
	cout << "~\t     (Y/n) yes by default: ";
	getline(cin, answ);
	if (isAnswerTrue(answ))
	{
		replyTo = senderEmail;
	}
	else
	{
		cout << "~" << endl;
		cout << "~\t  leave a letter without " << endl;
		cout << "\t                 an address for answers ?" << endl;
		cout << "~\t     (Y/n) yes by default: ";
		getline(cin, answ);
		if (isAnswerTrue(answ))
		{
			cout << "~" << endl;
			cout << "~\t  Then enter the address " << endl;
			cout << "~\t		to which send replies: ";
			getline(cin, replyTo);
		}
	}

	cout << "~" << endl;
	cout << "~\t  Enter the title of you email: ";
	getline(cin, title);

	EMAIL::Client client;
	EMAIL::Client::SERVER_ID Id = EMAIL::Client::SERVER_ID::UNDEFINED;
	while (Id == EMAIL::Client::SERVER_ID::UNDEFINED)
	{
		cout << "~" << endl;
		cout << "~\t  I support the following services," << endl;
		cout << "~\t             select the one you need." << endl;
		cout << "~" << endl;
		printSupportedServers();
		cout << "~" << endl;
		cout << "~\t  To choose - enter the server id: ";
		short id;
		cin >> id;
		Id = int2Id(id);
		if (Id == EMAIL::Client::SERVER_ID::UNDEFINED)
		{
			cout << "~\t 	Server with such id is not in the list..." << endl;
			cout << "~\t							 try again" << endl;
		}
	}
	client.SetServer(Id);

	if (client.IsAuthRequired())
	{
		cout << "~" << endl;
		cout << "~\t  Server require authentication." << endl;
		cout << "~\t		email address will be used as login, so enter" << endl;
		cout << "~\t		password of you email: ";
		string password;
		cin.ignore(1);
		getline(cin, password);
		client.SetAuth(senderEmail, password);
	}

	cout << "~" << endl;
	cout << "~\t  Specify recipient emails	(at least 1 required)" << endl;
	cout << "~\t 		when done enter \"ok\"" << endl;
	cout << "~\t		   Recipients: " << endl;
	string s;
	bool flag = false;
	while (s != "ok")
	{
		cout << "\t\t";
		getline(cin, s);
		if (s == "ok")
		{
			if (!flag)
				s = "";
		}
		else
		{
			flag = true;
			recipient_email.push_back(s);
		}
	}

	cout << "~" << endl;
	cout << "~\t  Specify carbon copy recipient emails	(optional)" << endl;
	cout << "~\t 		when done enter \"ok\"" << endl;
	cout << "~\t		  CC Recipients: " << endl;
	s.clear();
	while (s != "ok")
	{
		cout << "\t\t";
		getline(cin, s);
		if (s != "ok")
		{
			ccrecipient_email.push_back(s);
		}
	}

	cout << "~" << endl;
	cout << "~\t  Specify blind carbon copy recipient" << endl;
	cout << "~\t			emails	(optional)" << endl;
	cout << "~\t 		when done enter \"ok\"" << endl;
	cout << "~\t		  BCC Recipients: " << endl;
	s.clear();
	while (s != "ok")
	{
		cout << "\t\t";
		getline(cin, s);
		if (s != "ok")
		{
			bccrecipient_email.push_back(s);
		}
	}

	cout << "~" << endl;
	cout << "~\t  Write you letter" << endl;
	cout << "~\t 		when done press Esc botton" << endl;
	cout << "~\t		  Attachemnts: " << endl;
	s.clear();
	while (_getch() != 27) // wait for pressing Esc
	{
		cout << "\t\t";
		getline(cin, s);
		body.push_back(s);
	}

	cout << "~" << endl;
	cout << "~\t  Specify attachemnt files path	(optional)" << endl;
	cout << "~\t 		when done enter \"ok\"" << endl;
	cout << "~\t		  Letter body: " << endl;
	s.clear();
	while (s != "ok")
	{
		cout << "\t\t";
		getline(cin, s);
		if (s != "ok")
		{
			attachments.push_back(s);
		}
	}

	cout << "~" << endl;
	cout << "~\t  Well done" << endl;
	cout << "~\t 			I try to send a letter..." << endl;
	cout << "~" << endl;

	cout << "~\t 						..." << endl;

	EMAIL::MAIL mail;
	mail.SetSenderName(name);
	mail.SetSenderMail(senderEmail);
	mail.SetReplyTo(replyTo);
	mail.SetSubject(title);
	for (const auto& line : body)
	{
		mail.AddAttachment(line);
	}
	mail.SetXPriority(EMAIL::MAIL::PRIORITY::NORMAL);
	mail.SetXMailer("My email client");
	try
	{
		for (const auto& r : recipient_email)
			mail.AddRecipient(r);

		for (const auto& r : ccrecipient_email)
			mail.AddCCRecipient(r);

		for (const auto& r : bccrecipient_email)
			mail.AddBCCRecipient(r);

		for (const auto& line : body)
			mail.AddMsgLine(line);

		client.send(mail);
	}
	catch (const Exception::base&)
	{

	}

	cout << "~\t 						..." << endl;

	cout << "~" << endl;
	cout << "~\t 			Letter was send successfuly!" << endl;
	cout << "~\t  Bye ..." << endl;

	return 0;
}
