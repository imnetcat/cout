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
	void SetSecurity(ESMTPSA::SMTP_SECURITY_TYPE type);
	void SetAuth(const string& login, const string& pass);
	void AddRecipient(const string& email, const string& name = "");
	void AddBCCRecipient(const string& email, const string& name = "");
	void AddCCRecipient(const string& email, const string& name = "");
	void AddAttachment(const string& path);
	void AddMsgLine(const string& text);
	void ClearMessage();
	void DelRecipients(void);
	void DelBCCRecipients(void);
	void DelCCRecipients(void);
	void DelAttachments(void);
	void DelMsgLines(void);
	void DelMsgLine(unsigned int line);
	void ModMsgLine(unsigned int line, const char* text);
	size_t GetBCCRecipientCount() const;
	size_t GetCCRecipientCount() const;
	size_t GetRecipientCount() const;
	const char* GetMsgLineText(unsigned int line) const;
	size_t GetMsgLines(void) const;
	const char* GetReplyTo() const;
	const char* GetMailFrom() const;
	const char* GetSenderName() const;
	const char* GetSubject() const;
	const char* GetXMailer() const;
	SMTP::MAIL::PRIORITY GetXPriority() const;

	void SetCharSet(const string&);
	void SetSubject(const string&);
	void SetSenderName(const string&);
	void SetSenderMail(const string&);
	void SetReplyTo(const string&);
	void SetReadReceipt(bool requestReceipt = true);
	void SetXPriority(SMTP::MAIL::PRIORITY);
	void SetXMailer(const string&);

	void send() const;

	bool IsAuthRequired() const;
	bool IsExtRequired() const;
	bool IsEncrypRequired() const;

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
		const string GetSecurity() const
		{
			return sec == ESMTPS::NO_SECURITY ? "no security" 
				: sec == ESMTPS::USE_SSL ? "ssl" : "tls";
		}
		const std::string address;
		const unsigned short port;
		const bool isAuth;
		bool reqExt;
	};
	const std::map<SERVER_ID, SUPPORTED_SERVER>& GetSupportedServers() const;
	void SetServer(SERVER_ID id);

private:

	std::shared_ptr<SMTP> getOptimalProtocol() const;
		
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
