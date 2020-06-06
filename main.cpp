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

void printSupportedServers(const EMAIL& mail)
{
	const auto& supps = mail.GetSupportedServers();

	for (const auto& [id, server] : supps)
	{
		cout << "/t   Server id:  /t" << id << " : " << endl;
		cout << "/t   Server name:/t" << server.name << " : " << endl;
		cout << "/t/t Required extended smtp: /t" << server.reqExt ? "true" : "false"; cout << endl;
		cout << "/t/t Required authentication: /t" << server.isAuth ? "true" : "false"; cout << endl;
		cout << "/t/t Required encryption: /t" << server.GetSecurity() << endl;
		cout << "/t ~" << endl;
	}
}

EMAIL::SERVER_ID int2Id(short i)
{
	switch (i)
	{
	case 1:
		return EMAIL::SERVER_ID::GMAIL_TLS;
		break;
	case 2:
		return EMAIL::SERVER_ID::GMAIL_SSL;
		break;
	case 3:
		return EMAIL::SERVER_ID::HOTMAIL_TSL;
		break;
	case 4:
		return EMAIL::SERVER_ID::AOL_TLS;
		break;
	case 5:
		return EMAIL::SERVER_ID::YAHOO_SSL;
		break;
	default:
		return EMAIL::SERVER_ID::UNDEFINED;
	}
}

int main()
{
#ifdef INDEBUG
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try 
	{
		TESTS::GMAIL::tls_test_text();
		TESTS::GMAIL::ssl_test_text();
		TESTS::GMAIL::tls_test_attachments();
		TESTS::GMAIL::ssl_test_attachments();
	}
	catch (ERR e) 
	{
		ERRORS::processing(e);
	}
	catch (...)
	{
		// TODO: all standart exception proccesing
	}
#endif

	EMAIL mail;
	string answ;
	string name, senderEmail, replyTo, title;
	cout << "/t ~~~~~~~~~~~~ STMP Email-client demo						" << endl;
	cout << "/t ~														" << endl;
	cout << "/t ~ Hello, dear, let's write you letter..					" << endl;
	cout << "/t ~		* do not forget enable access from untrusted	" << endl;
	cout << "/t ~		  applications to your mailbox in its settings *" << endl;
	cout << "/t ~														" << endl;
	cout << "/t ~ First of all,											" << endl;
	cout << "/t     tell me you name: "; 
	getline(cin, name);
	mail.SetSenderName(name);

	cout << "/t ~														" << endl;
	cout << "/t ~ Okey, now I need you									" << endl;
	cout << "/t     email address: ";
	getline(cin, senderEmail);
	mail.SetSenderMail(senderEmail);

	cout << "/t ~														" << endl;
	cout << "/t ~ Send answers to the same address ?					" << endl;
	cout << "/t     (Y/n) yes by default: ";
	getline(cin, answ);
	if (isAnswerTrue(answ))
	{
		replyTo = senderEmail;
	}
	else
	{
		cout << "/t ~														" << endl;
		cout << "/t ~ leave a letter without " << endl;
		cout << "/t                 an address for answers ?  " << endl;
		cout << "/t     (Y/n) yes by default: ";
		getline(cin, answ);
		if (isAnswerTrue(answ))
		{
			cout << "/t ~														" << endl;
			cout << "/t ~ Then enter the address " << endl;
			cout << "/t		to which send replies: ";
			getline(cin, replyTo);
		}
	}
	mail.SetReplyTo(replyTo);

	cout << "/t ~														" << endl;
	cout << "/t ~ Enter the 											" << endl;
	cout << "/t  		title of you email: ";
	getline(cin, title);
	mail.SetSubject(title);

	EMAIL::SERVER_ID Id = EMAIL::SERVER_ID::UNDEFINED;
	while (Id == EMAIL::SERVER_ID::UNDEFINED)
	{
		cout << "/t ~														" << endl;
		cout << "/t ~ I support the following services,                     " << endl;
		cout << "/t             select the one you need.			     	" << endl;
		cout << "/t ~	         To choose - enter the server id			" << endl;
		printSupportedServers(mail);
		short id;
		cin >> id;
		Id = int2Id(id);
		if (Id == EMAIL::SERVER_ID::UNDEFINED)
		{
			cout << "/t ~	Server with such id is not in the list...		" << endl;
			cout << "/t							 try again			     	" << endl;
		}
	}
	mail.SetServer(Id);

	if (mail.IsAuthRequired())
	{
		cout << "/t ~														" << endl;
		cout << "/t ~ Server require authentication.						" << endl;
		cout << "/t		email address will be used as login, so enter		" << endl;
		cout << "/t		password of you email: ";
		string password;
		getline(cin, password);
		mail.SetAuth(senderEmail, password);
	}

	cout << "/t ~														" << endl;
	cout << "/t ~ Specify recipient emails	(at least 1 required)		" << endl;
	cout << "/t 		when done enter \"ok\"							" << endl;
	cout << "/t		   Recipients: " << endl;
	string recipient_email;
	while (recipient_email != "ok")
	{
		cout << "/t/t";
		getline(cin, recipient_email);
		if (recipient_email == "ok")
		{
			if(!mail.GetRecipientCount())
				recipient_email = "";
		}
		else
		{
			try
			{
				mail.AddRecipient(recipient_email);
			}
			catch (...) {}
		}
	}

	cout << "/t ~														" << endl;
	cout << "/t ~ Specify carbon copy recipient emails	(optional)		" << endl;
	cout << "/t 		when done enter \"ok\"							" << endl;
	cout << "/t		  CC Recipients: " << endl;
	recipient_email.clear();
	while (recipient_email != "ok")
	{
		cout << "/t/t";
		getline(cin, recipient_email);
		if (recipient_email != "ok")
		{
			try
			{
				mail.AddCCRecipient(recipient_email);

			}
			catch (...) {}
		}
	}

	cout << "/t ~														" << endl;
	cout << "/t ~ Specify blind carbon copy recipient					" << endl;
	cout << "/t			emails	(optional)		" << endl;
	cout << "/t 		when done enter \"ok\"							" << endl;
	cout << "/t		  BCC Recipients: " << endl;
	recipient_email.clear();
	while (recipient_email != "ok")
	{
		cout << "/t/t";
		getline(cin, recipient_email);
		if (recipient_email != "ok")
		{
			try
			{
				mail.AddBCCRecipient(recipient_email);
			}
			catch (...) {}
		}
	}

	cout << "/t ~														" << endl;
	cout << "/t ~ Write you letter										" << endl;
	cout << "/t 		when done press Esc botton						" << endl;
	cout << "/t		  Attachemnts: " << endl;
	string text;
	while (_getch() != 27) // wait for pressing Esc
	{
		cout << "/t/t";
		getline(cin, text);
		mail.AddMsgLine(text);
	}

	cout << "/t ~														" << endl;
	cout << "/t ~ Specify attachemnt files path	(optional)				" << endl;
	cout << "/t 		when done enter \"ok\"							" << endl;
	cout << "/t		  Letter body: " << endl;
	string attch_path;
	while (attch_path != "ok")
	{
		cout << "/t/t";
		getline(cin, attch_path);
		if (attch_path != "ok")
		{
			try
			{
				mail.AddAttachment(attch_path);
			}
			catch(...) { }
		}
	}

	mail.SetXPriority(SMTP::MAIL::PRIORITY::NORMAL);
	mail.SetXMailer("My email client");

	cout << "/t ~														" << endl;
	cout << "/t ~ Well done												" << endl;
	cout << "/t ~			I try to send a letter...					" << endl;
	cout << "/t ~														" << endl;

	cout << "/t ~						...								" << endl;

	try
	{
		mail.send();
	}
	catch (ERR)
	{

	}

	cout << "/t ~						...								" << endl;

	cout << "/t ~														" << endl;
	cout << "/t ~			Letter was send successfuly!				" << endl;
	cout << "/t ~ Bye ...												" << endl;

	return 0;
}
