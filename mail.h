#pragma once
#ifndef _MAIL_H_
#define _MAIL_H_
#include "core.h"
#include <map>
#include <vector>
namespace EMAIL
{
	using string = std::string;

	class MAIL
	{
	public:
		MAIL();
		virtual ~MAIL();
		const string createHeader();
		void AddRecipient(const string& email, const string& name = "");
		void AddBCCRecipient(const string& email, const string& name = "");
		void AddCCRecipient(const string& email, const string& name = "");
		void AddAttachment(const string& path);
		void AddMsgLine(const string& text) noexcept;
		void ClearMessage() noexcept;
		void DelRecipients(void) noexcept;
		void DelBCCRecipients(void) noexcept;
		void DelCCRecipients(void) noexcept;
		void DelAttachments(void) noexcept;
		void DelMsgLines(void) noexcept;
		void DelMsgLine(unsigned int line);
		void ModMsgLine(unsigned int line, const char* text);
		const char* GetMsgLineText(unsigned int line) const noexcept;
		size_t GetMsgLines(void) const noexcept;
		const string& GetReplyTo() const noexcept;
		const string& GetMailFrom() const noexcept;
		const string& GetSenderName() const noexcept;
		const string& GetSubject() const noexcept;
		const string& GetXMailer() const noexcept;
		size_t GetBodySize() const noexcept;
		const std::vector<string>& GetBody() const noexcept;
		size_t GetAttachmentsSize() const noexcept;
		const std::vector<string>& GetAttachments() const noexcept;
		void SetCharSet(const string&) noexcept;
		void SetSubject(const string&) noexcept;
		void SetSenderName(const string&) noexcept;
		void SetSenderMail(const string&) noexcept;
		void SetReplyTo(const string&) noexcept;
		void SetReadReceipt(bool requestReceipt = true) noexcept;
		void SetXMailer(const string&) noexcept;

		struct Recipient
		{
			string Name;
			string Mail;
		};
		size_t GetBCCRecipientCount() const noexcept;
		size_t GetCCRecipientCount() const noexcept;
		size_t GetRecipientCount() const noexcept;
		const std::vector<Recipient>& GetBCCRecipient() const noexcept;
		const std::vector<Recipient>& GetCCRecipient() const noexcept;
		const std::vector<Recipient>& GetRecipient() const noexcept;

		enum PRIORITY
		{
			HIGH = 2,
			NORMAL = 3,
			LOW = 4
		};
		static const string BOUNDARY_TEXT;
		PRIORITY GetXPriority() const noexcept;
		void SetXPriority(PRIORITY) noexcept;
	private:
		string senderMail;
		string senderName;
		string subject;
		string charSet = "US-ASCII";
		string mailer;
		string replyTo;
		bool readReceipt = false;
		std::vector<Recipient> recipients;
		std::vector<Recipient> ccrecipients;
		std::vector<Recipient> bccrecipients;
		std::vector<string> attachments;
		std::vector<string> body;
		PRIORITY priority = NORMAL;
		bool html = false;
	};
}
#endif
