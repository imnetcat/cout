#include "test.h"

const string TEST::AUTH::email = "hey.vasap@gmaail.com";
const string TEST::AUTH::password = "6275924Y";
const string TEST::recipient_email = "crazyhero019@gmail.com";

void TEST::text(EMAIL &mail)
{
	mail.SetSenderName("User");
	mail.SetSenderMail(AUTH::email);
	mail.SetReplyTo(AUTH::email);
	mail.SetSubject("Test");
	mail.AddRecipient(recipient_email);
	mail.SetXPriority(XPRIORITY_NORMAL);
	mail.SetXMailer("My email client");

	mail.AddMsgLine("Hello,");
	mail.AddMsgLine("");
	mail.AddMsgLine("...");
	mail.AddMsgLine("How are you today?");
	mail.AddMsgLine("");
	mail.AddMsgLine("Regards");
	mail.ModMsgLine(5, "regards");
	mail.DelMsgLine(2);
	mail.AddMsgLine("User");
}

void TEST::attachments(EMAIL &mail)
{
	mail.SetSenderName("User");
	mail.SetSenderMail(AUTH::email);
	mail.SetReplyTo(AUTH::email);
	mail.SetSubject("Test");
	mail.AddRecipient(recipient_email);
	mail.SetXPriority(XPRIORITY_NORMAL);
	mail.SetXMailer("My email client");

	mail.AddMsgLine("Вам пришли мемы с котами");

	mail.AddAttachment("test-files/1.jpg");
	mail.AddAttachment("test-files/2.jpg");
	mail.AddAttachment("test-files/3.jpg");
	mail.AddAttachment("test-files/4.jpg");
	mail.AddAttachment("test-files/5.jpg");
	mail.AddAttachment("test-files/6.jpg");
	mail.AddAttachment("test-files/7.jpg");
	mail.AddAttachment("test-files/8.jpg");
	mail.AddAttachment("./test-files/9.jpg");
	mail.AddAttachment("./test-files/10.jpg");
	mail.AddAttachment("./test-files/11jpg");
	mail.AddAttachment("./test-files/12.jpg");
	mail.AddAttachment("./test-files/13.jpg");
	mail.AddAttachment("./test-files/14.jpg");
	mail.AddAttachment("./test-files/15.jpg");
	mail.AddAttachment("./test-files/16.jpg");
	mail.AddAttachment("./test-files/17.jpg");
	mail.AddAttachment("./test-files/18.jpg");
	mail.AddAttachment("test-files/19_23.rar");
	mail.AddAttachment("test-files/19_23.zip");
	mail.AddAttachment("test-files/24.txt");
}

RETCODE TEST::GMAIL::tls_test_attachments()
{
	cout << "tls_test_attachments" << endl;
	EMAIL mail;

	mail.useGmail();
	mail.SetAuth(TEST::AUTH::email, TEST::AUTH::password);
	mail.SetSecurity(USE_TLS);

	attachments(mail);

	if(mail.send())
		return FAIL(EMAIL_SEND);

	cout << "successfully" << endl;
	return SUCCESS;
}

RETCODE TEST::GMAIL::tls_test_text()
{
	cout << "tls_test_text" << endl;
	EMAIL mail;

	mail.useGmail();
	mail.SetAuth(TEST::AUTH::email, TEST::AUTH::password);
	mail.SetSecurity(USE_TLS);

	text(mail);

	if (mail.send())
		return FAIL(EMAIL_SEND);

	cout << "successfully" << endl;
	return SUCCESS;
}

RETCODE TEST::GMAIL::ssl_test_text()
{
	cout << "ssl_test_text" << endl;
	EMAIL mail;

	mail.useGmail();
	mail.SetAuth(TEST::AUTH::email, TEST::AUTH::password);
	mail.SetSecurity(USE_SSL);

	text(mail);

	if (mail.send())
		return FAIL(EMAIL_SEND);

	cout << "successfully" << endl;
	return SUCCESS;
}

RETCODE TEST::GMAIL::ssl_test_attachments()
{
	cout << "ssl_test_attachments" << endl;
	EMAIL mail;

	mail.useGmail();
	mail.SetAuth(TEST::AUTH::email, TEST::AUTH::password);
	mail.SetSecurity(USE_SSL);

	attachments(mail);

	if (mail.send())
		return FAIL(EMAIL_SEND);

	cout << "successfully" << endl;
	return SUCCESS;
}