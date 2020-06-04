#include "email.h"
using namespace std;

EMAIL::EMAIL()
{
	mail = {};
}

EMAIL::~EMAIL()
{
	
}

void EMAIL::AddAttachment(const char *Path)
{
	mail.attachments.insert(mail.attachments.end(), Path);
}

RETCODE EMAIL::AddRecipient(const string& email, const string& name)
{
	if (email.empty())
		return FAIL(UNDEF_RECIPIENT_MAIL);

	SMTP::MAIL::Recipient recipient;
	recipient.Mail = email;
	if (!name.empty()) 
		recipient.Name = name;

	mail.recipients.insert(mail.recipients.end(), recipient);

	return SUCCESS;
}

RETCODE EMAIL::AddCCRecipient(const string& email, const string& name)
{
	if (email.empty())
		return FAIL(UNDEF_RECIPIENT_MAIL);

	SMTP::MAIL::Recipient recipient;
	recipient.Mail = email;
	if (!name.empty()) 
		recipient.Name = name;

	mail.ccrecipients.insert(mail.ccrecipients.end(), recipient);

	return SUCCESS;
}

RETCODE EMAIL::AddBCCRecipient(const string& email, const string& name)
{
	if (email.empty())
		return FAIL(UNDEF_RECIPIENT_MAIL);

	SMTP::MAIL::Recipient recipient;
	recipient.Mail = email;
	if (!name.empty()) 
		recipient.Name = name;

	mail.bccrecipients.insert(mail.bccrecipients.end(), recipient);

	return SUCCESS;
}

void EMAIL::AddMsgLine(const char* Text)
{
	mail.body.insert(mail.body.end(), Text);
}

RETCODE EMAIL::DelMsgLine(unsigned int Line)
{
	if (Line >= mail.body.size())
		return FAIL(OUT_OF_VECTOR_RANGE);
	mail.body.erase(mail.body.begin() + Line);

	return SUCCESS;
}

void EMAIL::DelRecipients()
{
	mail.recipients.clear();
}

void EMAIL::DelBCCRecipients()
{
	mail.bccrecipients.clear();
}

void EMAIL::DelCCRecipients()
{
	mail.ccrecipients.clear();
}

void EMAIL::DelMsgLines()
{
	mail.body.clear();
}

void EMAIL::DelAttachments()
{
	mail.attachments.clear();
}

RETCODE EMAIL::ModMsgLine(unsigned int Line, const char* Text)
{
	if (Text)
	{
		if (Line >= mail.body.size())
			return FAIL(OUT_OF_VECTOR_RANGE);
		mail.body.at(Line) = std::string(Text);
	}

	return SUCCESS;
}

void EMAIL::ClearMessage()
{
	DelRecipients();
	DelBCCRecipients();
	DelCCRecipients();
	DelAttachments();
	DelMsgLines();
}


size_t EMAIL::GetRecipientCount() const
{
	return mail.recipients.size();
}

size_t EMAIL::GetBCCRecipientCount() const
{
	return mail.bccrecipients.size();
}

size_t EMAIL::GetCCRecipientCount() const
{
	return mail.ccrecipients.size();
}

const char* EMAIL::GetReplyTo() const
{
	return mail.replyTo.c_str();
}

const char* EMAIL::GetMailFrom() const
{
	return mail.senderMail.c_str();
}

const char* EMAIL::GetSenderName() const
{
	return mail.senderName.c_str();
}

const char* EMAIL::GetSubject() const
{
	return mail.subject.c_str();
}

const char* EMAIL::GetXMailer() const
{
	return mail.mailer.c_str();
}

SMTP::MAIL::CSmptXPriority EMAIL::GetXPriority() const
{
	return mail.priority;
}

const char* EMAIL::GetMsgLineText(unsigned int Line) const
{
	return mail.body.at(Line).c_str();
}

size_t EMAIL::GetMsgLines() const
{
	return mail.body.size();
}

void EMAIL::SetCharSet(const string& sCharSet)
{
	mail.charSet = sCharSet;
}


void EMAIL::SetXPriority(SMTP::MAIL::CSmptXPriority priority)
{
	mail.priority = priority;
}

void EMAIL::SetReplyTo(const string& ReplyTo)
{
	mail.replyTo = ReplyTo;
}

void EMAIL::SetReadReceipt(bool requestReceipt/*=true*/)
{
	mail.readReceipt = requestReceipt;
}

void EMAIL::SetSenderMail(const string& SMail)
{
	mail.senderMail = SMail;
}

void EMAIL::SetSenderName(const string& Name)
{
	mail.senderName = Name;
}

void EMAIL::SetSubject(const string& Subject)
{
	mail.subject = Subject;
}

void EMAIL::SetXMailer(const string& XMailer)
{
	mail.mailer = XMailer;
}

void EMAIL::SetAuth(const string& login, const string& pass)
{
	mail.senderLogin = login;
	mail.senderPass = pass;
}

void EMAIL::SetSecurity(ESMTPSA::SMTP_SECURITY_TYPE type)
{
	security = type;
}

void EMAIL::useGmail()
{
	smtp_server = GMAIL;
	reqExt = true;
	reqSecure = true;
	reqAuth = true;
}
void EMAIL::useHotmail()
{
	smtp_server = HOTMAIL;
	reqExt = true;
	reqSecure = true;
	reqAuth = true;
}
void EMAIL::useAol()
{
	smtp_server = AOL;
	reqExt = true;
	reqSecure = true;
	reqAuth = true;
}
void EMAIL::useYahoo()
{
	smtp_server = YAHOO;
	reqExt = true;
	reqSecure = true;
	reqAuth = true;
}

shared_ptr<SMTP> EMAIL::getOptimalProtocol() const
{
	if (!reqExt)
	{
		return make_shared<SMTP>();
	}

	if (!reqAuth && reqSecure)
	{
		return make_shared<ESMTPS>();
	}
	else if (reqAuth && reqSecure)
	{
		return make_shared<ESMTPSA>();
	}

	return make_shared<ESMTP>();

}

RETCODE EMAIL::send() const
{
	if (mail.senderMail.empty())
		return FAIL(EMAIL_UNDEF_SENDER);
	if (mail.recipients.empty())
		return FAIL(EMAIL_UNDEF_RECEIVER);
	
	if (reqSecure && security == ESMTPSA::NO_SECURITY)
		return FAIL(SMTP_CREATE_HEADER); // TODO: another error name
	if (reqAuth && !mail.senderLogin.size())
		return FAIL(SMTP_CREATE_HEADER); // TODO: another error name

	const SUPPORTED_SERVERS_ADDR server = supported_servers.at(smtp_server).at(security);
	
	shared_ptr<SMTP> mailer = getOptimalProtocol();
	
	mailer->Connect();
	
	mailer->SetSMTPServer(server.port, server.name);

	mailer->SendMail(mail);
	
	return SUCCESS;
}
