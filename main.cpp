#include "client.h"
//#include "utest.h"
//#include "tests.h"

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
	const auto& supps = EMAIL::Requires::GetSupported();

	for (const auto& [id, smtp_server] : supps)
	{
		const string ext = smtp_server.reqExt ? "true" : "false";
		const string auth = smtp_server.isAuth ? "true" : "false";
		cout << "~\t   Server id:  \t" << id  << endl;
		cout << "~\t   Server name:\t" << smtp_server.name << endl;
		cout << "~\t\t Required extended smtp: \t" << ext << endl;
		cout << "~\t\t Required authentication: \t" << auth << endl;
		cout << "~\t\t Required encryption: \t\t" << smtp_server.GetSecurity() << endl;
		cout << "~\t " << endl;
	}
}

int main()
{
#ifdef INDEBUG	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*{
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

		tester.run(TEST::Client::DefAuth, "default authentication value");
		tester.run(TEST::Client::SetAuth, "setting up authentication value");
		tester.run(TEST::Client::SendExceptions, "sending the mail, awaiting exceptions");
	}
	*/
#endif

	string answ;
	string name, password, senderEmail, replyTo, title;
	vector<string> recipient_email;
	vector<string> ccrecipient_email;
	vector<string> bccrecipient_email;
	vector<string> body;
	vector<string> attachments;
	EMAIL::Server::ID smtp_server;

	/*
	{
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

		cout << "~" << endl;
		cout << "~\t  I support the following services," << endl;
		cout << "~\t             select the one you need." << endl;
		cout << "~" << endl;
		printSupportedServers();
		cout << "~" << endl;
		cout << "~\t  To choose - enter the smtp_server id: ";
		bool flag = false;
		do {
			short id;
			cin >> id;

			flag = false;
			switch (id)
			{
			case 1:
				smtp_server = EMAIL::Server::ID::GMAIL_TLS;
				break;
			case 2:
				smtp_server = EMAIL::Server::ID::GMAIL_SSL;
				break;
			case 3:
				smtp_server = EMAIL::Server::ID::HOTMAIL_TSL;
				break;
			case 4:
				smtp_server = EMAIL::Server::ID::AOL_TLS;
				break;
			case 5:
				smtp_server = EMAIL::Server::ID::YAHOO_SSL;
				break;
			default:
				flag = true;
			}

			if (flag)
			{
				cout << "~\t 	Server with such id is not in the list..." << endl;
				cout << "~\t							 try again" << endl;
			}
		} while (flag);

		if (EMAIL::Requires::GetSupported().at(smtp_server).isAuth)
		{
			cout << "~" << endl;
			cout << "~\t  Server require authentication." << endl;
			cout << "~\t		email address will be used as login, so enter" << endl;
			cout << "~\t		password of you email: ";
			cin.ignore(1);
			getline(cin, password);
		}

		cout << "~" << endl;
		cout << "~\t  Specify recipient emails	(at least 1 required)" << endl;
		cout << "~\t 		when done enter \"ok\"" << endl;
		cout << "~\t		   Recipients: " << endl;
		string s;
		flag = false;
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
	}
	cout << "~" << endl;
	cout << "~\t  Well done" << endl;
	cout << "~\t 			I try to send a letter..." << endl;
	cout << "~" << endl;

	cout << "~\t 						..." << endl;


	EMAIL::Client client;
	client.SetAuth(senderEmail, password);

	client.SetSenderName(name);
	client.SetSenderMail(senderEmail);
	client.SetReplyTo(replyTo);
	client.SetSubject(title);
	for (const auto& line : body)
	{
		client.AddAttachment(line);
	}
	client.SetXPriority(EMAIL::MAIL::PRIORITY::NORMAL);
	client.SetXMailer("My email client");
	try
	{
		for (const auto& r : recipient_email)
			client.AddRecipient(r);

		for (const auto& r : ccrecipient_email)
			client.AddCCRecipient(r);

		for (const auto& r : bccrecipient_email)
			client.AddBCCRecipient(r);

		for (const auto& line : body)
			client.AddMsgLine(line);

		client.send();
	}
	catch (const Exception::base&)
	{

	}

	cout << "~\t 						..." << endl;

	cout << "~" << endl;
	cout << "~\t 			Letter was send successfuly!" << endl;
	cout << "~\t  Bye ..." << endl;
	*/

	smtp_server = EMAIL::Server::ID::GMAIL_SSL;
	name = "SomeUser";
	senderEmail = "crazyhero019@gmail.com";
	replyTo = "crazyhero019@gmail.com";
	password = "Key09919925";
	
	recipient_email.push_back("guskov.danil@gmail.com");

	title = "Testing the framework";
	body.push_back("Hello man");
	body.push_back("this is working with ASCII");
	body.push_back("this is working with Unicode if you see hearth and unicorn");
	body.push_back("💗 " + UTILS::to_string(0x1F984));
	body.push_back("⚜" + UTILS::to_string(0x269C));
	body.push_back("🦄" + UTILS::to_string(0x1F61B));
	body.push_back("😛" + UTILS::to_string(0x1F61B));

	EMAIL::Client client;

	client.Use(smtp_server);
	client.SetAuth(senderEmail, password);

	client.SetSenderName(name);
	client.SetSenderMail(senderEmail);
	client.SetReplyTo(replyTo);
	client.SetSubject(title);
	for (const auto& line : body)
	{
		client.AddAttachment(line);
	}
	client.SetXPriority(EMAIL::MAIL::PRIORITY::NORMAL);
	client.SetXMailer("My email client");

	try
	{
		for (const auto& r : recipient_email)
			client.AddRecipient(r);

		for (const auto& r : ccrecipient_email)
			client.AddCCRecipient(r);

		for (const auto& r : bccrecipient_email)
			client.AddBCCRecipient(r);

		for (const auto& line : body)
			client.AddMsgLine(line);

		client.send();
	}
	catch (const Exception::base& exc)
	{
		cerr << "\t\tError appeared" << endl
			<< exc.what() << endl
			<< exc.when() << endl;
	}

	return 0;
}
