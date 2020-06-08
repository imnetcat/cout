﻿#include "tests.h"
using namespace std;

const string TESTS::AUTH::email = EMAIL_SENDER_USERNAME;
const string TESTS::AUTH::password = EMAIL_SENDER_PASSWORD;
const string TESTS::recipient_email = EMAIL_RECEIVER_USERNAME;

void TESTS::text(EMAIL::MAIL &mail)
{
	mail.SetSenderName("User");
	mail.SetSenderMail(AUTH::email);
	mail.SetReplyTo(AUTH::email);
	mail.SetSubject("Test");
	mail.AddRecipient(recipient_email);
	mail.SetXPriority(EMAIL::MAIL::PRIORITY::NORMAL);
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

void TESTS::attachments(EMAIL::MAIL &mail)
{
	mail.SetSenderName("User");
	mail.SetSenderMail(AUTH::email);
	mail.SetReplyTo(AUTH::email);
	mail.SetSubject("Test cats");
	mail.AddRecipient(recipient_email);
	mail.SetXPriority(EMAIL::MAIL::PRIORITY::NORMAL);
	mail.SetXMailer("My email client");

	mail.AddMsgLine("Вам пришли котики");

	mail.AddAttachment("./test-files/1.jpg");
	mail.AddAttachment("./test-files/2.jpeg");
	mail.AddAttachment("./test-files/3.png");
	mail.AddAttachment("./test-files/4.jpg");
	mail.AddAttachment("./test-files/5.jpg");
	mail.AddAttachment("./test-files/6.jpg");
	mail.AddAttachment("./test-files/7.jpg");
	mail.AddAttachment("./test-files/8.jpg");
	mail.AddAttachment("./test-files/9.png");
	mail.AddAttachment("./test-files/10.jpg");
	mail.AddAttachment("./test-files/11.jpg");
	mail.AddAttachment("./test-files/12.jpg");
	mail.AddAttachment("./test-files/13.jpg");
	mail.AddAttachment("./test-files/14.jpg");
	mail.AddAttachment("./test-files/15.jpg");
	mail.AddAttachment("./test-files/16.jpg");
	mail.AddAttachment("./test-files/17.jpg");
	mail.AddAttachment("./test-files/18.jpg");
	mail.AddAttachment("./test-files/19_23.rar");
	mail.AddAttachment("./test-files/19_23.zip");
	mail.AddAttachment("./test-files/24.txt");
}

void TESTS::GMAIL::tls_test_attachments()
{
	cout << "tls_test_attachments" << endl;
	EMAIL::MAIL mail;
	EMAIL::Client client;
	client.SetServer(EMAIL::Client::GMAIL_SSL);
	client.SetAuth(AUTH::email, AUTH::password);
	client.SetSecurity(EMAIL::ESMTPS::SMTP_SECURITY_TYPE::USE_TLS);

	attachments(mail);

	client.send(mail);
}

void TESTS::GMAIL::tls_test_text()
{
	cout << "tls_test_text" << endl;
	EMAIL::MAIL mail;
	EMAIL::Client client;
	client.SetServer(EMAIL::Client::GMAIL_TLS);
	client.SetAuth(AUTH::email, AUTH::password);
	client.SetSecurity(EMAIL::ESMTPS::SMTP_SECURITY_TYPE::USE_TLS);

	text(mail);

	client.send(mail);
}

void TESTS::GMAIL::ssl_test_text()
{
	cout << "ssl_test_text" << endl;
	EMAIL::MAIL mail;
	EMAIL::Client client;
	client.SetServer(EMAIL::Client::GMAIL_SSL);
	client.SetAuth(AUTH::email, AUTH::password);
	client.SetSecurity(EMAIL::ESMTPS::SMTP_SECURITY_TYPE::USE_SSL);

	text(mail);

	client.send(mail);
}

void TESTS::GMAIL::ssl_test_attachments()
{
	cout << "ssl_test_attachments" << endl;
	EMAIL::MAIL mail;
	EMAIL::Client client;
	client.SetServer(EMAIL::Client::GMAIL_SSL);
	client.SetAuth(AUTH::email, AUTH::password);
	client.SetSecurity(EMAIL::ESMTPS::SMTP_SECURITY_TYPE::USE_SSL);

	attachments(mail);

	client.send(mail);
}