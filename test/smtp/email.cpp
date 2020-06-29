#include "email.h"
using namespace std;
void TEST::Client::DefAuth()
{
	Protocol::SMTP::Client client;
	return AssertEqual(client.GetLogin(), "", "empty by default");
	return AssertEqual(client.GetPassword(), "", "empty by default");
}
void TEST::Client::SetAuth()
{
	Protocol::SMTP::Client client;
	client.SetLogin("qwerty");
	client.SetPassword("password___");
	return AssertEqual(client.GetLogin(), "qwerty", "set up login is incorrect");
	return AssertEqual(client.GetPassword(), "password___", "set up password is incorrect");
}
void TEST::Client::SendExceptionss()
{
	Protocol::SMTP::MAIL mail;
	Protocol::SMTP::Client client;

	AssertExceptions<Exceptions::Core::invalid_argument>("client send", "sender mail is not specified", "empty sender mail", TEST::Utils::ClientSend, client, mail);

	mail.SetSenderMail("qwerty");

	AssertExceptions<Exceptions::Core::invalid_argument>("client send", "recipient mail is not specified", "empty receiver mail", TEST::Utils::ClientSend, client, mail);
}
