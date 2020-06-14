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
	if (!required.Extentions())
	{
		return make_shared<SMTP>();
	}

	if (!required.Auth() && required.Security())
	{
		return make_shared<EMAIL::ESMTPS>();
	}
	else if (required.Auth() && required.Security())
	{
		return make_shared<EMAIL::ESMTPSA>();
	}

	return make_shared<ESMTP>();

}

void EMAIL::Client::Use(Server::ID id)
{
	required = Requires(id);
}
void EMAIL::Client::Use(Server id)
{
	required = Requires(id);
}

void EMAIL::Client::send() const
{
	if (GetMailFrom().empty())
		throw CORE::Exception::invalid_argument("empty sender mail");
	if (!GetRecipientCount())
		throw CORE::Exception::invalid_argument("empty receiver mail");

	shared_ptr<SMTP> mailer = getOptimalProtocol();
	
	mailer->Connect(required.host, required.port);
	
	mailer->SendMail(*this);

	mailer->Disconnect();
}
