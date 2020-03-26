#include "email.h"
#include <iostream>

int test()
{
	EMAIL mail;

	mail.useGmail();
	mail.SetAuth("my.gmail@gmail.com", "my_password");
	mail.SetSecurity(USE_TLS);

	mail.SetSenderName("User");
	mail.SetSenderMail("my.gmail@gmail.com");
	mail.SetReplyTo("my.gmail@gmail.com");
	mail.SetSubject("Test");
	mail.AddRecipient("friend.mail@gmail.com");
	mail.SetXPriority(XPRIORITY_NORMAL);
	mail.SetXMailer("The Bat! (v3.02) Professional");
	mail.AddMsgLine("Hello,");
	mail.AddMsgLine("");
	mail.AddMsgLine("...");
	mail.AddMsgLine("How are you today?");
	mail.AddMsgLine("");
	mail.AddMsgLine("Regards");
	mail.ModMsgLine(5, "regards");
	mail.DelMsgLine(2);
	mail.AddMsgLine("User");

	//mail.AddAttachment("../test1.jpg");
	//mail.AddAttachment("c:\\test2.exe");
	//mail.AddAttachment("c:\\test3.txt");
	mail.send();

	std::cout << "Mail was send successfully.\n";
	return 0;
}