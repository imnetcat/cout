#include "email.h"

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

RETCODE EMAIL::AddRecipient(const string email, const string name)
{
	if (email.empty())
		return FAIL(UNDEF_RECIPIENT_MAIL);

	Recipient recipient;
	recipient.Mail = email;
	if (!name.empty()) recipient.Name = name;
	else recipient.Name.empty();

	mail.recipients.insert(mail.recipients.end(), recipient);

	return SUCCESS;
}

RETCODE EMAIL::AddCCRecipient(const string email, const string name)
{
	if (email.empty())
		return FAIL(UNDEF_RECIPIENT_MAIL);

	Recipient recipient;
	recipient.Mail = email;
	if (!name.empty()) recipient.Name = name;
	else recipient.Name.empty();

	mail.ccrecipients.insert(mail.ccrecipients.end(), recipient);

	return SUCCESS;
}

RETCODE EMAIL::AddBCCRecipient(const string email, const string name)
{
	if (email.empty())
		return FAIL(UNDEF_RECIPIENT_MAIL);

	Recipient recipient;
	recipient.Mail = email;
	if (!name.empty()) recipient.Name = name;
	else recipient.Name.empty();

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


unsigned int EMAIL::GetRecipientCount() const
{
	return mail.recipients.size();
}

unsigned int EMAIL::GetBCCRecipientCount() const
{
	return mail.bccrecipients.size();
}

unsigned int EMAIL::GetCCRecipientCount() const
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

CSmptXPriority EMAIL::GetXPriority() const
{
	return mail.priority;
}

const char* EMAIL::GetMsgLineText(unsigned int Line) const
{
	return mail.body.at(Line).c_str();
}

unsigned int EMAIL::GetMsgLines() const
{
	return mail.body.size();
}

void EMAIL::SetCharSet(const string sCharSet)
{
	mail.charSet = sCharSet;
}


void EMAIL::SetXPriority(CSmptXPriority priority)
{
	mail.priority = priority;
}

void EMAIL::SetReplyTo(const string ReplyTo)
{
	mail.replyTo = ReplyTo;
}

void EMAIL::SetReadReceipt(bool requestReceipt/*=true*/)
{
	mail.readReceipt = requestReceipt;
}

void EMAIL::SetSenderMail(const string SMail)
{
	mail.senderMail = SMail;
}

void EMAIL::SetSenderName(const string Name)
{
	mail.senderName = Name;
}

void EMAIL::SetSubject(const string Subject)
{
	mail.subject = Subject;
}

void EMAIL::SetXMailer(const string XMailer)
{
	mail.mailer = XMailer;
}

RETCODE EMAIL::createHeader()
{
	char month[][4] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
	size_t i;
	string to;
	string cc;
	string bcc;
	stringstream sheader;
	time_t rawtime;
	struct tm* timeinfo = nullptr;

	// date/time check
	if (time(&rawtime) > 0)
		localtime_s(timeinfo, &rawtime);
	else
		return FAIL(TIME_ERROR);

	// check for at least one recipient
	if (mail.recipients.size())
	{
		for (i = 0; i < mail.recipients.size(); i++)
		{
			if (i > 0)
				to.append(",");
			to += mail.recipients[i].Name;
			to.append("<");
			to += mail.recipients[i].Mail;
			to.append(">");
		}
	}
	else
		return FAIL(UNDEF_RECIPIENTS);

	if (mail.ccrecipients.size())
	{
		for (i = 0; i < mail.ccrecipients.size(); i++)
		{
			if (i > 0)
				cc.append(",");
			cc += mail.ccrecipients[i].Name;
			cc.append("<");
			cc += mail.ccrecipients[i].Mail;
			cc.append(">");
		}
	}

	// Date: <SP> <dd> <SP> <mon> <SP> <yy> <SP> <hh> ":" <mm> ":" <ss> <SP> <zone> <CRLF>
	sheader << "Date: " <<
		timeinfo->tm_mday << " " <<
		month[timeinfo->tm_mon] << " " <<
		timeinfo->tm_year + 1900 << " " <<
		timeinfo->tm_hour << ":" <<
		timeinfo->tm_min << ":" <<
		timeinfo->tm_sec << "\r\n";
	// From: <SP> <sender>  <SP> "<" <sender-email> ">" <CRLF>
	if (!mail.senderMail.size()) return FAIL(UNDEF_MAIL_FROM);

	sheader << "From: ";
	if (mail.senderName.size()) sheader << mail.senderName;

	sheader << " <";
	sheader << mail.senderMail;
	sheader << ">\r\n";

	// X-Mailer: <SP> <xmailer-app> <CRLF>
	if (mail.mailer.size())
	{
		sheader << "X-Mailer: ";
		sheader << mail.mailer;
		sheader << "\r\n";
	}

	// Reply-To: <SP> <reverse-path> <CRLF>
	if (mail.replyTo.size())
	{
		sheader << "Reply-To: ";
		sheader << mail.replyTo;
		sheader << "\r\n";
	}

	// Disposition-Notification-To: <SP> <reverse-path or sender-email> <CRLF>
	if (mail.readReceipt)
	{
		sheader << "Disposition-Notification-To: ";
		if (mail.replyTo.size()) sheader << mail.replyTo;
		else sheader << mail.senderName;
		sheader << "\r\n";
	}

	// X-Priority: <SP> <number> <CRLF>
	switch (mail.priority)
	{
	case XPRIORITY_HIGH:
		sheader << "X-Priority: 2 (High)\r\n";
		break;
	case XPRIORITY_NORMAL:
		sheader << "X-Priority: 3 (Normal)\r\n";
		break;
	case XPRIORITY_LOW:
		sheader << "X-Priority: 4 (Low)\r\n";
		break;
	default:
		sheader << "X-Priority: 3 (Normal)\r\n";
	}

	// To: <SP> <remote-user-mail> <CRLF>
	sheader << "To: ";
	sheader << to;
	sheader << "\r\n";

	// Cc: <SP> <remote-user-mail> <CRLF>
	if (mail.ccrecipients.size())
	{
		sheader << "Cc: ";
		sheader << cc;
		sheader << "\r\n";
	}

	if (mail.bccrecipients.size())
	{
		sheader << "Bcc: ";
		sheader << bcc;
		sheader << "\r\n";
	}

	// Subject: <SP> <subject-text> <CRLF>
	if (!mail.subject.size())
		sheader << "Subject:  ";
	else
	{
		sheader << "Subject: ";
		sheader << mail.subject;
	}
	sheader << "\r\n";

	// MIME-Version: <SP> 1.0 <CRLF>
	sheader << "MIME-Version: 1.0\r\n";
	if (!mail.attachments.size())
	{ // no attachments
		if (mail.html) sheader << "Content-Type: text/html; charset=\"";
		else sheader << "Content-type: text/plain; charset=\"";
		sheader << mail.charSet;
		sheader << "\"\r\n";
		sheader << "Content-Transfer-Encoding: 7bit\r\n";
		sheader << "\r\n";
	}
	else
	{ // there is one or more attachments
		sheader << "Content-Type: multipart/mixed; boundary=\"";
		sheader << BOUNDARY_TEXT;
		sheader << "\"\r\n";
		sheader << "\r\n";
		// first goes text message
		sheader << "--";
		sheader << BOUNDARY_TEXT;
		sheader << "\r\n";
		if (mail.html) sheader << "Content-type: text/html; charset=";
		else sheader << "Content-type: text/plain; charset=";
		sheader << mail.charSet;
		sheader << "\r\n";
		sheader << "Content-Transfer-Encoding: 7bit\r\n";
		sheader << "\r\n";
	}

	sheader << '\0';

	mail.header = sheader.str();
	return SUCCESS;
}

void EMAIL::SetAuth(string login, string pass)
{
	mail.senderLogin = login;
	mail.senderPass = pass;
}

void EMAIL::SetSecurity(ESMTPS::SMTP_SECURITY_TYPE type)
{
	security = type;
}

void EMAIL::useGmail()
{
	smtp_server = GMAIL;
}
void EMAIL::useHotmail()
{
	smtp_server = HOTMAIL;
}
void EMAIL::useAol()
{
	smtp_server = AOL;
}
void EMAIL::useYahoo()
{
	smtp_server = YAHOO;
}

RETCODE EMAIL::send() {
	if (mail.senderMail.empty())
		return FAIL(EMAIL_UNDEF_SENDER);
	if (mail.recipients.empty())
		return FAIL(EMAIL_UNDEF_RECEIVER);
	if (createHeader())
		return FAIL(SMTP_CREATE_HEADER);
	
	const SUPPORTED_SERVERS_ADDR server = supported_servers[smtp_server][security];

	if (security == ESMTPS::SMTP_SECURITY_TYPE::NO_SECURITY)
	{
		if(mail.senderLogin.size() && mail.senderPass.size())
		{
			ESMTPA mailer;

			mailer.SetSMTPServer(server.port, server.name);
			mailer.SetServerAuth(mail.senderLogin, mail.senderPass);
			

			if (mailer.Send(mail))
				return FAIL(SMTP_SEND);
		}
		else
		{
			ESMTP mailer;

			mailer.SetSMTPServer(server.port, server.name);
			
			if (mailer.Send(mail))
				return FAIL(SMTP_SEND);
		}
	} 
	else
	{
		if (mail.senderLogin.size() && mail.senderPass.size())
		{
			/* TODO: ESMTPSA
			
			ESMTPSA mailer;

			mailer.SetSMTPServer(server.port, server.name);

			if (mailer.isAuthRequire())
			{
				mailer.SetServerAuth(mail.senderLogin, mail.senderPass);
			}

			if (mailer.Send(mail, security))
				return FAIL(SMTP_SEND);
			*/
		}
		else
		{
			ESMTPS mailer;

			mailer.SetSMTPServer(server.port, server.name);
		
			if (mailer.Send(mail, security))
				return FAIL(SMTP_SEND);
		}
	}

	return SUCCESS;
}
