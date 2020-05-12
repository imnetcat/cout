#pragma once
#ifndef _EMAIL_H_
#define _EMAIL_H_

#include "smtps.h"

#include <map>

class EMAIL
{
public:
	EMAIL();
	virtual ~EMAIL();
	void useGmail();
	void useHotmail();
	void useAol();
	void useYahoo();
	void SetSecurity(SMTPS::SMTP_SECURITY_TYPE type);
	void SetAuth(string login, string pass);
	RETCODE AddRecipient(const string email, const string name = "");
	RETCODE AddBCCRecipient(const string email, const string name = "");
	RETCODE AddCCRecipient(const string email, const string name = "");
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
	unsigned int GetBCCRecipientCount() const;
	unsigned int GetCCRecipientCount() const;
	unsigned int GetRecipientCount() const;
	const char* GetMsgLineText(unsigned int line) const;
	unsigned int GetMsgLines(void) const;
	const char* GetReplyTo() const;
	const char* GetMailFrom() const;
	const char* GetSenderName() const;
	const char* GetSubject() const;
	const char* GetXMailer() const;
	CSmptXPriority GetXPriority() const;

	void SetCharSet(const string sCharSet);
	void SetSubject(const string);
	void SetSenderName(const string);
	void SetSenderMail(const string);
	void SetReplyTo(const string);
	void SetReadReceipt(bool requestReceipt = true);
	void SetXPriority(CSmptXPriority);
	void SetXMailer(const string);

	RETCODE send();

private:

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
	
	map<SUPPORTED_SERVERS, map<SMTPS::SMTP_SECURITY_TYPE, SUPPORTED_SERVERS_ADDR>>supported_servers = {
		{
			GMAIL,	
			{
				{ SMTPS::SMTP_SECURITY_TYPE::USE_TLS,	{	"smtp.gmail.com",	587,	true	} },
				{ SMTPS::SMTP_SECURITY_TYPE::USE_SSL,	{	"smtp.gmail.com",	465,	true	} }
			}
		},
		{
			HOTMAIL,
			{
				{ SMTPS::SMTP_SECURITY_TYPE::USE_TLS, {	"smtp.live.com",	25,		true	} }
			}
		},
		{
			AOL,
			{
				{ SMTPS::SMTP_SECURITY_TYPE::USE_TLS,	{	"smtp.aol.com",		587,	true	} }
			}
		},
		{
			YAHOO,
			{
				{ SMTPS::SMTP_SECURITY_TYPE::USE_SSL,	{	"plus.smtp.mail.yahoo.com",	465,	true	} }
			}
		}
	};

	SMTPS::SMTP_SECURITY_TYPE security = SMTPS::SMTP_SECURITY_TYPE::NO_SECURITY;

	SUPPORTED_SERVERS smtp_server = GMAIL;

	RETCODE createHeader();
	MAIL mail;
};


#endif
