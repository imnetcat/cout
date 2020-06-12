#include "mail.h"
using namespace std;

EMAIL::MAIL::MAIL() : mailer(XMAILER){ }

EMAIL::MAIL::~MAIL() { }

const string& EMAIL::MAIL::GetSenderMail() const noexcept
{
	return senderMail;
}
const string& EMAIL::MAIL::GetCharSet() const noexcept
{
	return charSet;
}

void EMAIL::MAIL::AddAttachment(const string& Path)
{
	if (Path.empty())
		throw CORE::Exception::invalid_argument("input empty path");
	attachments.insert(attachments.end(), Path);
}

void EMAIL::MAIL::AddRecipient(const string& email, const string& name)
{
	if (email.empty())
		throw CORE::Exception::invalid_argument("recipient email is empty");

	recipients[email] = name;
}

void EMAIL::MAIL::AddCCRecipient(const string& email, const string& name)
{
	if (email.empty())
		throw CORE::Exception::invalid_argument("recipient email is empty");

	ccrecipients[email] = name;
}

void EMAIL::MAIL::AddBCCRecipient(const string& email, const string& name)
{
	if (email.empty())
		throw CORE::Exception::invalid_argument("recipient email is empty");

	bccrecipients[email] = name;
}

void EMAIL::MAIL::AddMsgLine(const string& Text) noexcept
{
	body.insert(body.end(), Text);
}

void EMAIL::MAIL::DelMsgLine(unsigned int Line)
{
	if (Line >= body.size())
		throw CORE::Exception::out_of_range("deleting line of message body");
	body.erase(body.begin() + Line);
}

void EMAIL::MAIL::DelRecipients() noexcept
{
	recipients.clear();
}

void EMAIL::MAIL::DelBCCRecipients() noexcept
{
	bccrecipients.clear();
}

void EMAIL::MAIL::DelCCRecipients() noexcept
{
	ccrecipients.clear();
}

void EMAIL::MAIL::DelMsgLines() noexcept
{
	body.clear();
}

void EMAIL::MAIL::DelAttachments() noexcept
{
	attachments.clear();
}

void EMAIL::MAIL::ModMsgLine(unsigned int Line, const char* Text)
{
	if (Line >= body.size())
		throw CORE::Exception::out_of_range("modify line of message body");
	body.at(Line) = std::string(Text);
}

void EMAIL::MAIL::ClearMessage() noexcept
{
	DelRecipients();
	DelBCCRecipients();
	DelCCRecipients();
	DelAttachments();
	DelMsgLines();
}

size_t EMAIL::MAIL::GetBodySize() const noexcept
{
	return body.size();
}
const std::vector<string>& EMAIL::MAIL::GetBody() const noexcept
{
	return body;
}

size_t EMAIL::MAIL::GetAttachmentsSize() const noexcept
{
	return attachments.size();
}
const std::vector<string>& EMAIL::MAIL::GetAttachments() const noexcept
{
	return attachments;
}

const EMAIL::MAIL::Recipients& EMAIL::MAIL::GetBCCRecipient() const noexcept
{
	return bccrecipients;
}

const EMAIL::MAIL::Recipients& EMAIL::MAIL::GetCCRecipient() const noexcept
{
	return ccrecipients;
}

const EMAIL::MAIL::Recipients& EMAIL::MAIL::GetRecipient() const noexcept
{
	return recipients;
}

size_t EMAIL::MAIL::GetRecipientCount() const noexcept
{
	return recipients.size();
}

size_t EMAIL::MAIL::GetBCCRecipientCount() const noexcept
{
	return bccrecipients.size();
}

size_t EMAIL::MAIL::GetCCRecipientCount() const noexcept
{
	return ccrecipients.size();
}

const string& EMAIL::MAIL::GetReplyTo() const noexcept
{
	return replyTo;
}

const string& EMAIL::MAIL::GetMailFrom() const noexcept
{
	return senderMail;
}

const string& EMAIL::MAIL::GetSenderName() const noexcept
{
	return senderName;
}

const string& EMAIL::MAIL::GetSubject() const noexcept
{
	return subject;
}

const string& EMAIL::MAIL::GetXMailer() const noexcept
{
	return mailer;
}

EMAIL::MAIL::PRIORITY EMAIL::MAIL::GetXPriority() const noexcept
{
	return priority;
}

const char* EMAIL::MAIL::GetMsgLineText(unsigned int Line) const noexcept
{
	return body.at(Line).c_str();
}

size_t EMAIL::MAIL::GetMsgLines() const noexcept
{
	return body.size();
}

void EMAIL::MAIL::SetCharSet(const string& sCharSet) noexcept
{
	charSet = sCharSet;
}

void EMAIL::MAIL::SetXPriority(EMAIL::MAIL::PRIORITY p) noexcept
{
	priority = p;
}

void EMAIL::MAIL::SetReplyTo(const string& ReplyTo) noexcept
{
	replyTo = ReplyTo;
}

void EMAIL::MAIL::SetReadReceipt(bool requestReceipt) noexcept
{
	readReceipt = requestReceipt;
}

void EMAIL::MAIL::SetSenderMail(const string& SMail) noexcept
{
	senderMail = SMail;
}

void EMAIL::MAIL::SetSenderName(const string& Name) noexcept
{
	senderName = Name;
}

void EMAIL::MAIL::SetSubject(const string& Subject) noexcept
{
	subject = Subject;
}

void EMAIL::MAIL::SetXMailer(const string& XMailer) noexcept
{
	mailer = XMailer;
}


const string EMAIL::MAIL::createHeader()
{
	char month[][4] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
	bool first_elem = true;
	stringstream to;
	stringstream cc;
	stringstream bcc;
	stringstream sheader;
	time_t rawtime;
	struct tm* timeinfo = nullptr;

	// date/time check
	if (time(&rawtime) > 0)
		localtime_s(timeinfo, &rawtime);
	else
		throw Exception::TIME_ERROR("creating SMTP header");

	// check for at least one recipient
	if (recipients.size())
	{
		for (const auto& [mail, name] : recipients)
		{
			if (first_elem)
				to << ',';
			first_elem = false;
			to << name;
			to << '<';
			to << mail;
			to << '>';
		}
	}
	else
		throw Exception::UNDEF_RECIPIENTS("creating SMTP header");

	if (ccrecipients.size())
	{
		for (const auto&[mail, name] : ccrecipients)
		{
			if (first_elem)
				to << ',';
			first_elem = false;
			to << name;
			to << '<';
			to << mail;
			to << '>';
		}
	}

	if (bccrecipients.size())
	{
		for (const auto&[mail, name] : bccrecipients)
		{
			if (first_elem)
				to << ',';
			first_elem = false;
			to << name;
			to << '<';
			to << mail;
			to << '>';
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
	if (!senderMail.size())
		throw Exception::UNDEF_MAIL_FROM("creating SMTP header");

	sheader << "From: ";
	if (senderName.size()) sheader << senderName;

	sheader << " <";
	sheader << senderMail;
	sheader << ">\r\n";

	// X-Mailer: <SP> <xmailer-app> <CRLF>
	if (mailer.size())
	{
		sheader << "X-Mailer: ";
		sheader << mailer;
		sheader << "\r\n";
	}

	// Reply-To: <SP> <reverse-path> <CRLF>
	if (replyTo.size())
	{
		sheader << "Reply-To: ";
		sheader << replyTo;
		sheader << "\r\n";
	}

	// Disposition-Notification-To: <SP> <reverse-path or sender-email> <CRLF>
	if (readReceipt)
	{
		sheader << "Disposition-Notification-To: ";
		if (replyTo.size()) sheader << replyTo;
		else sheader << senderName;
		sheader << "\r\n";
	}

	// X-Priority: <SP> <number> <CRLF>
	switch (priority)
	{
	case PRIORITY::HIGH:
		sheader << "X-Priority: 2 (High)\r\n";
		break;
	case PRIORITY::NORMAL:
		sheader << "X-Priority: 3 (Normal)\r\n";
		break;
	case PRIORITY::LOW:
		sheader << "X-Priority: 4 (Low)\r\n";
		break;
	default:
		sheader << "X-Priority: 3 (Normal)\r\n";
	}

	// To: <SP> <remote-user-mail> <CRLF>
	sheader << "To: ";
	sheader << to.str();
	sheader << "\r\n";

	// Cc: <SP> <remote-user-mail> <CRLF>
	if (ccrecipients.size())
	{
		sheader << "Cc: ";
		sheader << cc.str();
		sheader << "\r\n";
	}

	if (bccrecipients.size())
	{
		sheader << "Bcc: ";
		sheader << bcc.str();
		sheader << "\r\n";
	}

	// Subject: <SP> <subject-text> <CRLF>
	if (!subject.size())
		sheader << "Subject:  ";
	else
	{
		sheader << "Subject: ";
		sheader << subject;
	}
	sheader << "\r\n";

	// MIME-Version: <SP> 1.0 <CRLF>
	sheader << "MIME-Version: 1.0\r\n";
	if (!attachments.size())
	{ // no attachments
		if (html) sheader << "Content-Type: text/html; charset=\"";
		else sheader << "Content-type: text/plain; charset=\"";
		sheader << charSet;
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
		if (html) sheader << "Content-type: text/html; charset=";
		else sheader << "Content-type: text/plain; charset=";
		sheader << charSet;
		sheader << "\r\n";
		sheader << "Content-Transfer-Encoding: 7bit\r\n";
		sheader << "\r\n";
	}

	sheader << '\0';

	return sheader.str();
}

const string EMAIL::MAIL::BOUNDARY_TEXT = "__MESSAGE__ID__54yg6f6h6y456345";