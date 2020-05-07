#pragma once
#ifndef _SMTP_H_
#define _SMTP_H_

#include "core.h"
#include "socket.h"

#include <vector>
#include <string.h>
#include <time.h>

#if _MSC_VER < 1400
#define snprintf _snprintf
#else
#define snprintf sprintf_s
#endif

#define TIME_IN_SEC		3*60	// how long client will wait for server response in non-blocking mode
#define BUFFER_SIZE		10240	// SendData and RecvData buffers sizes
#define MSG_SIZE_IN_MB	25		// the maximum size of the message with all attachments
#define COUNTER_VALUE	100		// how many times program will try to receive data

const std::string BOUNDARY_TEXT = "__MESSAGE__ID__54yg6f6h6y456345";

#include <openssl/ssl.h>
#include <openssl/err.h>

#pragma comment (lib, "crypt32")
#pragma comment (lib, "libcrypto64MTd.lib")
#pragma comment (lib, "libssl64MTd.lib")

enum CSmptXPriority
{
	XPRIORITY_HIGH = 2,
	XPRIORITY_NORMAL = 3,
	XPRIORITY_LOW = 4
};

// TLS/SSL extension
enum SMTP_SECURITY_TYPE
{
	NO_SECURITY,
	USE_TLS,
	USE_SSL,
	DO_NOT_SET
};

struct Recipient
{
	std::string Name;
	std::string Mail;
};
struct Auth
{
	std::string login;
	std::string password;
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
struct SERVER
{
	SMTP_SECURITY_TYPE security = NO_SECURITY;
	bool isConnected = false;
	unsigned short port = 0;
	std::string name;
	bool isAuth = true;
	Auth auth;
};

enum SUPPORTED_SMTP_SERVERS {
	GMAIL,
	HOTMAIL,
	AOL,
	YAHOO
};

struct SUPPORTED_SMTP_SERVER
{
	SUPPORTED_SMTP_SERVERS id;
	SMTP_SECURITY_TYPE required_security;
	std::string name;
	unsigned short port = 0;
	bool isAuth = false;
};

class SMTP
{
public:
	SMTP();
	virtual ~SMTP();
	void DisconnectRemoteServer();
	void SetLocalHostName(const char *sLocalHostName);
	std::string GetLocalHostName();

	SMTP_SECURITY_TYPE GetSecurityType() const;
	void SetSecurityType(SMTP_SECURITY_TYPE type);
	RETCODE SetSMTPServer(SUPPORTED_SMTP_SERVERS serv_id, SMTP_SECURITY_TYPE sec_type = NO_SECURITY);

	void SetServerAuth(std::string login, std::string pass);

	bool isAuthRequire();
	bool useSecurity = false;

	RETCODE Auth();

	std::string m_sLocalHostName;
	std::string m_sIPAddr;
	RETCODE Send(MAIL mail);

	RETCODE SendMail();

	RETCODE Connect();

	std::string SendBuf;
	std::string RecvBuf;
	
	RETCODE WSA_Init();
	RETCODE SocksConnect();

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
	RETCODE ReceiveData_NoSec(int recv_timeout);
	RETCODE SendData_NoSec(int send_timeout);
	bool IsCommandSupported(std::string response, std::string command);
	int SmtpXYZdigits();

	SERVER server;
	RETCODE ReceiveData_SSL(int send_timeout);
	RETCODE SendData_SSL(int send_timeout);
	void CleanupOpenSSL();
	RETCODE OpenSSLConnect();
	RETCODE InitOpenSSL();
	SSL_CTX*      ctx;
	SSL*          ssl;

	vector <SUPPORTED_SMTP_SERVER> supported_servers = {
		{GMAIL,		USE_TLS,	"smtp.gmail.com",			587,	true},
		{GMAIL,		USE_SSL,	"smtp.gmail.com",			465,	true},
		{HOTMAIL,	USE_TLS,	"smtp.live.com",			25,		true},
		{AOL,		USE_TLS,	"smtp.aol.com",				587,	true},
		{YAHOO,		USE_SSL,	"plus.smtp.mail.yahoo.com", 465,	true},
	};
};


#endif // _SMTP_H_
