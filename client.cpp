#include "client.h"
using namespace std;

const string& EMAIL::Client::GetLogin() const noexcept
{
	return senderLogin;
}
const string& EMAIL::Client::GetPassword() const noexcept
{
	return senderPass;
}

void EMAIL::Client::SetAuth(const string& login, const string& pass)
{
	senderLogin = login;
	senderPass = pass;
}

shared_ptr<EMAIL::SMTP> EMAIL::Client::getOptimalProtocol() const noexcept
{
	if (!Extentions())
	{
		return make_shared<SMTP>();
	}

	if (!Auth() && Security())
	{
		return make_shared<EMAIL::ESMTPS>();
	}
	else if (Auth() && Security())
	{
		return make_shared<EMAIL::ESMTPSA>();
	}

	return make_shared<ESMTP>();

}

void EMAIL::Client::send(MAIL mail) const
{
	if (mail.GetMailFrom().empty())
		throw CORE::Exception::invalid_argument("empty sender mail");
	if (!mail.GetRecipientCount())
		throw CORE::Exception::invalid_argument("empty receiver mail");

	shared_ptr<SMTP> mailer = getOptimalProtocol();

	mailer->SetSMTPServer(port, address);

	mailer->Connect();
	
	mailer->SendMail(mail);

	mailer->Disconnect();
}
