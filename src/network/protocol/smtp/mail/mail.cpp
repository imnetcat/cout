#include "mail.h"
#include "../../../../core/filesystem/context_menu.h"
#include "../../../../core/exception.h"
#include "../../exception.h"
#include "../exception.h"
#include <sstream>
using namespace std;

Protocol::SMTP::MAIL::MAIL() : mailer(XMAILER){ }

Protocol::SMTP::MAIL::~MAIL() { }

const string& Protocol::SMTP::MAIL::GetSenderMail() const noexcept
{
	return senderMail;
}
const string& Protocol::SMTP::MAIL::GetCharSet() const noexcept
{
	return charSet;
}

void Protocol::SMTP::MAIL::AddAttachment(const string& Path)
{
	if (Path.empty())
		throw Exceptions::Core::invalid_argument(WHERE, "input empty path");
	if (!Core::Filesystem::ContextMenu::exist(Core::Filesystem::Descryptor(Path)))
		throw Exceptions::Core::file_not_exist(WHERE, "SMTP attachment file not found");
	attachments.insert(attachments.end(), Path);
}

void Protocol::SMTP::MAIL::AddRecipient(const string& email, const string& name)
{
	if (email.empty())
		throw Exceptions::Core::invalid_argument(WHERE, "recipient email is empty");

	recipients[email] = name;
}

void Protocol::SMTP::MAIL::AddCCRecipient(const string& email, const string& name)
{
	if (email.empty())
		throw Exceptions::Core::invalid_argument(WHERE, "recipient email is empty");

	ccrecipients[email] = name;
}

void Protocol::SMTP::MAIL::AddBCCRecipient(const string& email, const string& name)
{
	if (email.empty())
		throw Exceptions::Core::invalid_argument(WHERE, "recipient email is empty");

	bccrecipients[email] = name;
}

void Protocol::SMTP::MAIL::AddMsgLine(const string& Text) noexcept
{
	body.insert(body.end(), Text);
}

void Protocol::SMTP::MAIL::DelMsgLine(unsigned int Line)
{
	if (Line >= body.size())
		throw Exceptions::Core::out_of_range(WHERE, "deleting line of message body");
	body.erase(body.begin() + Line);
}

void Protocol::SMTP::MAIL::DelRecipients() noexcept
{
	recipients.clear();
}

void Protocol::SMTP::MAIL::DelBCCRecipients() noexcept
{
	bccrecipients.clear();
}

void Protocol::SMTP::MAIL::DelCCRecipients() noexcept
{
	ccrecipients.clear();
}

void Protocol::SMTP::MAIL::DelMsgLines() noexcept
{
	body.clear();
}

void Protocol::SMTP::MAIL::DelAttachments() noexcept
{
	attachments.clear();
}

void Protocol::SMTP::MAIL::ModMsgLine(unsigned int Line, const char* Text)
{
	if (Line >= body.size())
		throw Exceptions::Core::out_of_range(WHERE, "modify line of message body");
	body.at(Line) = std::string(Text);
}

void Protocol::SMTP::MAIL::ClearMessage() noexcept
{
	DelRecipients();
	DelBCCRecipients();
	DelCCRecipients();
	DelAttachments();
	DelMsgLines();
}

size_t Protocol::SMTP::MAIL::GetBodySize() const noexcept
{
	return body.size();
}
const std::vector<string>& Protocol::SMTP::MAIL::GetBody() const noexcept
{
	return body;
}

size_t Protocol::SMTP::MAIL::GetAttachmentsSize() const noexcept
{
	return attachments.size();
}
const std::vector<string>& Protocol::SMTP::MAIL::GetAttachments() const noexcept
{
	return attachments;
}

const Protocol::SMTP::MAIL::Recipients& Protocol::SMTP::MAIL::GetBCCRecipient() const noexcept
{
	return bccrecipients;
}

const Protocol::SMTP::MAIL::Recipients& Protocol::SMTP::MAIL::GetCCRecipient() const noexcept
{
	return ccrecipients;
}

const Protocol::SMTP::MAIL::Recipients& Protocol::SMTP::MAIL::GetRecipient() const noexcept
{
	return recipients;
}

size_t Protocol::SMTP::MAIL::GetRecipientCount() const noexcept
{
	return recipients.size();
}

size_t Protocol::SMTP::MAIL::GetBCCRecipientCount() const noexcept
{
	return bccrecipients.size();
}

size_t Protocol::SMTP::MAIL::GetCCRecipientCount() const noexcept
{
	return ccrecipients.size();
}

const string& Protocol::SMTP::MAIL::GetReplyTo() const noexcept
{
	return replyTo;
}

const string& Protocol::SMTP::MAIL::GetMailFrom() const noexcept
{
	return senderMail;
}

const string& Protocol::SMTP::MAIL::GetSenderName() const noexcept
{
	return senderName;
}

const string& Protocol::SMTP::MAIL::GetSubject() const noexcept
{
	return subject;
}

const string& Protocol::SMTP::MAIL::GetXMailer() const noexcept
{
	return mailer;
}

Protocol::SMTP::MAIL::PRIORITY Protocol::SMTP::MAIL::GetXPriority() const noexcept
{
	return priority;
}

const char* Protocol::SMTP::MAIL::GetMsgLineText(unsigned int Line) const noexcept
{
	return body.at(Line).c_str();
}

size_t Protocol::SMTP::MAIL::GetMsgLines() const noexcept
{
	return body.size();
}

void Protocol::SMTP::MAIL::SetCharSet(const string& sCharSet) noexcept
{
	charSet = sCharSet;
}

void Protocol::SMTP::MAIL::SetXPriority(Protocol::SMTP::MAIL::PRIORITY p) noexcept
{
	priority = p;
}

void Protocol::SMTP::MAIL::SetReplyTo(const string& ReplyTo) noexcept
{
	replyTo = ReplyTo;
}

void Protocol::SMTP::MAIL::SetReadReceipt(bool requestReceipt) noexcept
{
	readReceipt = requestReceipt;
}

void Protocol::SMTP::MAIL::SetSenderMail(const string& SMail) noexcept
{
	senderMail = SMail;
}

void Protocol::SMTP::MAIL::SetSenderName(const string& Name) noexcept
{
	senderName = Name;
}

void Protocol::SMTP::MAIL::SetSubject(const string& Subject) noexcept
{
	subject = Subject;
}

void Protocol::SMTP::MAIL::SetXMailer(const string& XMailer) noexcept
{
	mailer = XMailer;
}


const string Protocol::SMTP::MAIL::createHeader()
{
	char month[][4] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
	bool first_elem = true;
	stringstream to;
	stringstream cc;
	stringstream bcc;
	stringstream sheader;
	time_t rawtime;
	struct tm* timeinfo = new tm[sizeof(tm)];

	// date/time check
	if (time(&rawtime) > 0)
		localtime_s(timeinfo, &rawtime);
	else
		throw Exceptions::smtp::time_error(WHERE, "creating SMTP header");

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
		throw Exceptions::smtp::undef_recipients(WHERE, "creating SMTP header");

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

	delete[] timeinfo;
	// From: <SP> <sender>  <SP> "<" <sender-email> ">" <CRLF>
	if (!senderMail.size())
		throw Exceptions::smtp::undef_mail_from(WHERE, "creating SMTP header");

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

const string Protocol::SMTP::MAIL::BOUNDARY_TEXT = "__MESSAGE__ID__54yg6f6h6y456345";
