#include "core/exception.h"
#include "core/config.h"
#include "protocol/smtp/client.h"

#include <iostream>
#include <string>
#include <conio.h> // for _getch()
using namespace std;

bool isAnswerTrue(string answ)
{
	for (size_t i = 0; i < answ.size(); i++)
		answ[i] = tolower(answ[i]);

	return answ == "" ||
		   answ == "y" ||
		   answ == "yes";
}

ostream& operator << (ostream& out, const std::map<const Protocol::SMTP::Server::ID, const Protocol::SMTP::Server>& obj)
{
	for (const auto& [key, item] : obj)
	{
		out << "\tKey: " << key << endl;
		out << "\t\tHost: " << item.host << endl;
		out << "\t\tPort: " << item.port << endl;
	}
	return out;
}

int main()
{
#ifdef INDEBUG	
	{
	}
#endif

	string answ;
	string name, password, senderEmail, replyTo, title;
	vector<string> recipient_email;
	vector<string> ccrecipient_email;
	vector<string> bccrecipient_email;
	vector<string> body;
	vector<string> attachments;
	Protocol::SMTP::Server::ID Id;

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
		cout << Protocol::SMTP::Client::supported << endl;
		cout << "~" << endl;
		cout << "~\t  To choose - enter the smtp server id key: ";
		bool flag = false;
		do {
			short id;
			cin >> id;

			flag = false;
			switch (id)
			{
			case 1:
				Id = Protocol::SMTP::Server::ID::GMAIL_TLS;
				break;
			case 2:
				Id = Protocol::SMTP::Server::ID::GMAIL_SSL;
				break;
			case 3:
				Id = Protocol::SMTP::Server::ID::HOTMAIL_TSL;
				break;
			case 4:
				Id = Protocol::SMTP::Server::ID::AOL_TLS;
				break;
			case 5:
				Id = Protocol::SMTP::Server::ID::YAHOO_SSL;
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
			getline(cin, s);
			if (s != "ok")
			{
				bccrecipient_email.push_back(s);
			}
		}

		cout << "~" << endl;
		cout << "~\t  Write you letter" << endl;
		cout << "~\t 		when done press \"ok\"" << endl;
		cout << "~\t		  Letter body: " << endl;
		s.clear();
		while (s != "ok")
		{
			getline(cin, s);
			if (s != "ok")
			{
				body.push_back(s);
			}
		}

		cout << "~" << endl;
		cout << "~\t  Specify attachemnt files path	(optional)" << endl;
		cout << "~\t 		when done enter \"ok\"" << endl;
		cout << "~\t		  Attachments: " << endl;
		s.clear();
		while (s != "ok")
		{
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

	Protocol::SMTP::Client client;

	Protocol::SMTP::MAIL mail;
	mail.SetSenderName(name);
	mail.SetSenderMail(senderEmail);
	mail.SetReplyTo(replyTo);
	mail.SetSubject(title);

	try
	{
		for (const auto& path : attachments)
			mail.AddAttachment(path);

		for (const auto& r : recipient_email)
			mail.AddRecipient(r);

		for (const auto& r : ccrecipient_email)
			mail.AddCCRecipient(r);

		for (const auto& r : bccrecipient_email)
			mail.AddBCCRecipient(r);

		for (const auto& line : body)
			mail.AddMsgLine(line);

		client.SetServer(Id);
		client.SetLogin(senderEmail);
		client.SetPassword(password);
		client.Send(&mail);

		cout << "~\t 						..." << endl;

		cout << "~" << endl;
		cout << "~\t 			Letter was send successfuly!" << endl;
		cout << "~\t  Bye ..." << endl;
	}
	catch (const Exceptions::base& exc)
	{
		cerr << "[ERROR] " << exc.what() << endl
			<< "\t\t" << exc.when() << endl;
	}

	return 0;
}
