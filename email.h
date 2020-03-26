#pragma once
#ifndef _EMAIL_H_
#define _EMAIL_H_

#include "smtps.h"

class EMAIL
{
public:
	EMAIL();
	virtual ~EMAIL();
	void useGmail();
	void useHotmail();
	void useAol();
	void useYahoo();
	void SetSecurity(SMTP_SECURITY_TYPE type);
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

	SMTP_SECURITY_TYPE security = USE_TLS;

	SUPPORTED_SMTP_SERVERS smtp_server = GMAIL;

	RETCODE createHeader();
	MAIL mail;
};


#endif
