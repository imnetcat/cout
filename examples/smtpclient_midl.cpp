#include "../release/cout.hpp"
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
		mail.AddAttachment("../some/path/to/file.txt");
		mail.AddAttachment("../some/path/to/file.jpg");
		mail.AddAttachment("../some/path/to/file.pdf");
		mail.AddAttachment("../some/path/to/file.zip");

		mail.AddRecipient("example.addr2@gmail.com");
		mail.AddRecipient("example.addr3@gmail.com");
		mail.AddRecipient("example.addr4@gmail.com");
		mail.AddRecipient("example.addr5@gmail.com");

		mail.AddCCRecipient("example.addr6@gmail.com");
		mail.AddCCRecipient("example.addr7@gmail.com");
		mail.AddCCRecipient("example.addr8@gmail.com");

		mail.AddBCCRecipient("example.addr9@gmail.com");
		mail.AddBCCRecipient("example.addr10@gmail.com");
		mail.AddBCCRecipient("example.addr11@gmail.com");
		mail.AddBCCRecipient("example.addr12@gmail.com");


		mail.AddMsgLine("Hello world!");
		mail.AddMsgLine("...");
		mail.AddMsgLine("This is worked!");
		mail.AddMsgLine("...");

		// edit the mail msb body
		mail.ModMsgLine(1, ""); // line indexed from 0
		mail.ModMsgLine(3, "Regargs");

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
