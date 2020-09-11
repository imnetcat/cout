#include "cout.hpp"
using namespace Cout::Network;

#include <iostream>
using namespace std;

int main()
{
	SMTPClient client;

	Protocol::SMTP::MAIL mail;
	mail.SetSenderName("User");
	mail.SetSenderMail("example.addr@gmail.com");
	mail.SetReplyTo("example.addr@gmail.com");
	mail.SetSubject("Testing"); //  title of mail

	try
	{
		mail.AddRecipient("example.addr@mail.com");


		mail.AddMsgLine("Hello world!");

		client.SetServer(Protocol::SMTP::Server::ID::GMAIL_TLS);
		client.SetLogin("example.addr@gmail.com");
		client.SetPassword("********************************");

		client.Send(&mail);
	}
	catch (const Cout::Exceptions::base& exc)
	{
		cerr << "[ERROR] " << exc.what() << endl
			<< "\t\t" << exc.when() << endl;
	}

	return 0;
}
