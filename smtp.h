#pragma once
#ifndef _SMTP_H_
#define _SMTP_H_

#include "core.h"
#include "socket.h"

#include <vector>
#include <string>

#if _MSC_VER < 1400
#define snprintf _snprintf
#else
#define snprintf sprintf_s
#endif

#define MSG_SIZE_IN_MB	25		// the maximum size of the message with all attachments
#define COUNTER_VALUE	100		// how many times program will try to receive data

const std::string BOUNDARY_TEXT = "__MESSAGE__ID__54yg6f6h6y456345";


enum CSmptXPriority
{
	XPRIORITY_HIGH = 2,
	XPRIORITY_NORMAL = 3,
	XPRIORITY_LOW = 4
};

struct Recipient
{
	std::string Name;
	std::string Mail;
};
struct MAIL
{
	std::string senderMail;
	std::string senderName;
	std::string senderLogin;
	std::string senderPass;
	std::string subject;
	std::string charSet = "US-ASCII";
	std::string mailer;
	std::string replyTo;
	bool readReceipt = false;
	vector<Recipient> recipients;
	vector<Recipient> ccrecipients;
	vector<Recipient> bccrecipients;
	vector<string> attachments;
	vector<string> body;
	CSmptXPriority priority = XPRIORITY_NORMAL;
	std::string header;
	bool html = false;
};

enum SUPPORTED_SMTP_SERVERS {
	GMAIL,
	HOTMAIL,
	AOL,
	YAHOO
};

class SMTP : public Socket
{
public:
	SMTP();
	~SMTP();
	void DisconnectRemoteServer();
	void SetLocalHostName(const char *sLocalHostName);
	std::string GetLocalHostName();

	RETCODE SetSMTPServer(SUPPORTED_SMTP_SERVERS serv_id, SMTP_SECURITY_TYPE sec_type = NO_SECURITY);

	void SetServerAuth(std::string login, std::string pass);

	bool isAuthRequire();
	bool useSecurity = false;

	RETCODE Auth();

	std::string m_sIPAddr;
	RETCODE Send(MAIL mail);

	RETCODE SendMail();

	MAIL mail;

	enum COMMANDS
	{
		INIT,
		EHLO,
		AUTHPLAIN,
		AUTHLOGIN,
		AUTHCRAMMD5,
		AUTHDIGESTMD5,
		MAILFROM,
		RCPTTO,
		DATA,
		DATABLOCK,
		DATAEND,
		QUIT,
		STARTTLS
	};

	RETCODE Init();
	RETCODE Ehlo();
	RETCODE AuthLogin();
	RETCODE AuthPlain();
	RETCODE CramMD5();
	RETCODE DigestMD5();
	RETCODE MailFrom();
	RETCODE RCPTto();
	RETCODE Data();
	RETCODE Datablock();
	RETCODE DataEnd();
	RETCODE Quit();
	RETCODE Starttls();

	RETCODE Command(COMMANDS command);
	bool isRetCodeValid(int validCode);

	RETCODE ReceiveData(int timeout);
	RETCODE SendData(int timeout);
	bool IsCommandSupported(std::string response, std::string command);
	int SmtpXYZdigits();
	
	struct SUPPORTED_SMTP_SERVER
	{
		SUPPORTED_SMTP_SERVERS id;
		SMTP_SECURITY_TYPE required_security;
		std::string name;
		unsigned short port = 0;
		bool isAuth = false;
	};

	vector <SUPPORTED_SMTP_SERVER> supported_servers = {
		{GMAIL,		USE_TLS,	"smtp.gmail.com",			587,	true},
		{GMAIL,		USE_SSL,	"smtp.gmail.com",			465,	true},
		{HOTMAIL,	USE_TLS,	"smtp.live.com",			25,		true},
		{AOL,		USE_TLS,	"smtp.aol.com",				587,	true},
		{YAHOO,		USE_SSL,	"plus.smtp.mail.yahoo.com", 465,	true},
	};
};


#endif // _SMTP_H_
