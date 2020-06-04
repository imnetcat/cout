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
	void useGmail();
	void useHotmail();
	void useAol();
	void useYahoo();
	void SetSecurity(ESMTPSA::SMTP_SECURITY_TYPE type);
	void SetAuth(const string& login, const string& pass);
	RETCODE AddRecipient(const string& email, const string& name = "");
	RETCODE AddBCCRecipient(const string& email, const string& name = "");
	RETCODE AddCCRecipient(const string& email, const string& name = "");
	void AddAttachment(const char *path);
	void AddMsgLine(const char* text);
	void ClearMessage();
	void DelRecipients(void);
	void DelBCCRecipients(void);
	void DelCCRecipients(void);
	void DelAttachments(void);
	void DelMsgLines(void);
	RETCODE DelMsgLine(unsigned int line);
	RETCODE ModMsgLine(unsigned int line, const char* text);
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
	SMTP::MAIL::CSmptXPriority GetXPriority() const;

	void SetCharSet(const string&);
	void SetSubject(const string&);
	void SetSenderName(const string&);
	void SetSenderMail(const string&);
	void SetReplyTo(const string&);
	void SetReadReceipt(bool requestReceipt = true);
	void SetXPriority(SMTP::MAIL::CSmptXPriority);
	void SetXMailer(const string&);

	RETCODE send();

private:

	std::shared_ptr<SMTP> getOptimalProtocol();

	enum SUPPORTED_SERVERS {
		GMAIL,
		HOTMAIL,
		AOL,
		YAHOO
	};

	struct SUPPORTED_SERVERS_ADDR
	{
		std::string name;
		unsigned short port;
		bool isAuth;
	};
	
	std::map<SUPPORTED_SERVERS, std::map<ESMTPSA::SMTP_SECURITY_TYPE, SUPPORTED_SERVERS_ADDR>>supported_servers = {
		{
			GMAIL,	
			{
				{ ESMTPSA::SMTP_SECURITY_TYPE::USE_TLS,	{	"smtp.gmail.com",	587,	true	} },
				{ ESMTPSA::SMTP_SECURITY_TYPE::USE_SSL,	{	"smtp.gmail.com",	465,	true	} }
			}
		},
		{
			HOTMAIL,
			{
				{ ESMTPSA::SMTP_SECURITY_TYPE::USE_TLS, {	"smtp.live.com",	25,		true	} }
			}
		},
		{
			AOL,
			{
				{ ESMTPSA::SMTP_SECURITY_TYPE::USE_TLS,	{	"smtp.aol.com",		587,	true	} }
			}
		},
		{
			YAHOO,
			{
				{ ESMTPSA::SMTP_SECURITY_TYPE::USE_SSL,	{	"plus.smtp.mail.yahoo.com",	465,	true	} }
			}
		}
	};

	bool reqAuth;
	bool reqSecure;
	bool reqExt;

	ESMTPSA::SMTP_SECURITY_TYPE security = ESMTPSA::SMTP_SECURITY_TYPE::NO_SECURITY;

	SUPPORTED_SERVERS smtp_server = GMAIL;

	RETCODE createHeader();
	SMTP::MAIL mail;
};


#endif
