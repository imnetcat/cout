#pragma once
#ifndef _MAIL_H_
#define _MAIL_H_
#include "core.h"
#include <map>
#include <vector>
namespace EMAIL
{
	static const std::string XMAILER = "Mailer";
	
	class MAIL
	{
	public:
		MAIL();
		virtual ~MAIL();
		const std::string createHeader();
		void AddRecipient(const std::string& email, const std::string& name = "");
		void AddBCCRecipient(const std::string& email, const std::string& name = "");
		void AddCCRecipient(const std::string& email, const std::string& name = "");
		void AddAttachment(const std::string& path);
		void AddMsgLine(const std::string& text) noexcept;
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
		size_t GetBodySize() const noexcept;
		const std::vector<std::string>& GetBody() const noexcept;
		size_t GetAttachmentsSize() const noexcept;
		const std::vector<std::string>& GetAttachments() const noexcept;
		void SetCharSet(const std::string&) noexcept;
		void SetSubject(const std::string&) noexcept;
		void SetSenderName(const std::string&) noexcept;
		void SetSenderMail(const std::string&) noexcept;
		void SetReplyTo(const std::string&) noexcept;
		void SetReadReceipt(bool requestReceipt = true) noexcept;
		void SetXMailer(const std::string&) noexcept;

		const std::string& GetReplyTo() const noexcept;
		const std::string& GetMailFrom() const noexcept;
		const std::string& GetSenderName() const noexcept;
		const std::string& GetSubject() const noexcept;
		const std::string& GetXMailer() const noexcept;
		const std::string& GetSenderMail() const noexcept;
		const std::string& GetCharSet() const noexcept;

		using Recipients = std::map<std::string, std::string>;

		size_t GetBCCRecipientCount() const noexcept;
		size_t GetCCRecipientCount() const noexcept;
		size_t GetRecipientCount() const noexcept;
		const Recipients& GetBCCRecipient() const noexcept;
		const Recipients& GetCCRecipient() const noexcept;
		const Recipients& GetRecipient() const noexcept;

		enum PRIORITY
		{
			HIGH = 2,
			NORMAL = 3,
			LOW = 4
		};
		static const std::string BOUNDARY_TEXT;
		PRIORITY GetXPriority() const noexcept;
		void SetXPriority(PRIORITY priority = PRIORITY::NORMAL) noexcept;
	private:
		std::string senderMail;
		std::string senderName;
		std::string subject;
		std::string charSet = "US-ASCII";
		std::string mailer;
		std::string replyTo;
		bool readReceipt = false;
		Recipients recipients;
		Recipients ccrecipients;
		Recipients bccrecipients;
		std::vector<std::string> attachments;
		std::vector<std::string> body;
		PRIORITY priority = NORMAL;
		bool html = false;
	};
}
#endif
