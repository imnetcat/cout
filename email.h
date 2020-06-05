#pragma once
#ifndef _EMAIL_H_
#define _EMAIL_H_

#include "esmtpsa.h"

#include <map>
#include <memory>

class EMAIL
{
public:
	EMAIL();
	virtual ~EMAIL();
	void SetSecurity(ESMTPSA::SMTP_SECURITY_TYPE type) noexcept;
	void SetAuth(const string& login, const string& pass) noexcept;
	void AddRecipient(const string& email, const string& name = "");
	void AddBCCRecipient(const string& email, const string& name = "");
	void AddCCRecipient(const string& email, const string& name = "");
	void AddAttachment(const string& path) noexcept;
	void AddMsgLine(const string& text) noexcept;
	void ClearMessage() noexcept;
	void DelRecipients(void) noexcept;
	void DelBCCRecipients(void) noexcept;
	void DelCCRecipients(void) noexcept;
	void DelAttachments(void) noexcept;
	void DelMsgLines(void) noexcept;
	void DelMsgLine(unsigned int line);
	void ModMsgLine(unsigned int line, const char* text);
	size_t GetBCCRecipientCount() const noexcept;
	size_t GetCCRecipientCount() const noexcept;
	size_t GetRecipientCount() const noexcept;
	const char* GetMsgLineText(unsigned int line) const noexcept;
	size_t GetMsgLines(void) const noexcept;
	const char* GetReplyTo() const noexcept;
	const char* GetMailFrom() const noexcept;
	const char* GetSenderName() const noexcept;
	const char* GetSubject() const noexcept;
	const char* GetXMailer() const noexcept;
	SMTP::MAIL::PRIORITY GetXPriority() const noexcept;

	void SetCharSet(const string&) noexcept;
	void SetSubject(const string&) noexcept;
	void SetSenderName(const string&) noexcept;
	void SetSenderMail(const string&) noexcept;
	void SetReplyTo(const string&) noexcept;
	void SetReadReceipt(bool requestReceipt = true) noexcept;
	void SetXPriority(SMTP::MAIL::PRIORITY) noexcept;
	void SetXMailer(const string&) noexcept;

	void send() const;

	bool IsAuthRequired() const noexcept;
	bool IsExtRequired() const noexcept;
	bool IsEncrypRequired() const noexcept;

	enum SERVER_ID {
		UNDEFINED = 0,
		GMAIL_TLS = 1,
		GMAIL_SSL,
		HOTMAIL_TSL,
		AOL_TLS,
		YAHOO_SSL
	};
	struct SUPPORTED_SERVER
	{
		const std::string name;
		ESMTPS::SMTP_SECURITY_TYPE sec;
		inline const string GetSecurity() const noexcept
		{
			return sec == ESMTPS::NO_SECURITY ? "no security" 
				: sec == ESMTPS::USE_SSL ? "ssl" : "tls";
		}
		const std::string address;
		const unsigned short port;
		const bool isAuth;
		bool reqExt;
	};
	const std::map<SERVER_ID, SUPPORTED_SERVER>& GetSupportedServers() const noexcept;
	void SetServer(SERVER_ID id) noexcept;

private:

	std::shared_ptr<SMTP> getOptimalProtocol() const noexcept;
		
	std::map<SERVER_ID, SUPPORTED_SERVER> supported_servers = {
		{
			GMAIL_TLS,
			{
				"Gmail",	ESMTPSA::SMTP_SECURITY_TYPE::USE_TLS,	"smtp.gmail.com",			587,	true, true
			}
		},
		{
			GMAIL_SSL,
			{
				"Gmail",	ESMTPSA::SMTP_SECURITY_TYPE::USE_SSL,	"smtp.gmail.com",			465,	true, true
			}
		},
		{
			HOTMAIL_TSL,
			{
				"HotMail",	ESMTPSA::SMTP_SECURITY_TYPE::USE_TLS,	"smtp.live.com",			25,		true, true
			}
		},
		{
			AOL_TLS,
			{
				"Aol",		ESMTPSA::SMTP_SECURITY_TYPE::USE_TLS,	"smtp.aol.com",				587,	true, true
			}
		},
		{
			YAHOO_SSL,
			{
				"Yahoo",	ESMTPSA::SMTP_SECURITY_TYPE::USE_SSL,	"plus.smtp.mail.yahoo.com",	465,	true, true
			}
		}
	};

	bool reqAuth;
	bool reqSecure;
	bool reqExt;

	ESMTPSA::SMTP_SECURITY_TYPE security = ESMTPSA::SMTP_SECURITY_TYPE::NO_SECURITY;

	SERVER_ID smtp_server;

	SMTP::MAIL mail;
};


#endif
