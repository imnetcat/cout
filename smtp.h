#pragma once
#ifndef _SMTP_H_
#define _SMTP_H_

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <vector>
#include <string.h>
#include <assert.h>

#include <winsock2.h>
#include <time.h>
#pragma comment(lib, "ws2_32.lib")

#if _MSC_VER < 1400
#define snprintf _snprintf
#else
#define snprintf sprintf_s
#endif

#include "base64.h"
#include "md5.h"

#define TIME_IN_SEC		3*60	// how long client will wait for server response in non-blocking mode
#define BUFFER_SIZE		10240	// SendData and RecvData buffers sizes
#define MSG_SIZE_IN_MB	25		// the maximum size of the message with all attachments
#define COUNTER_VALUE	100		// how many times program will try to receive data

const string BOUNDARY_TEXT = "__MESSAGE__ID__54yg6f6h6y456345";

using namespace std;

#include "errors.h"

enum CSmptXPriority
{
	XPRIORITY_HIGH = 2,
	XPRIORITY_NORMAL = 3,
	XPRIORITY_LOW = 4
};

enum SMTP_COMMAND
{
	command_INIT,
	command_EHLO,
	command_AUTHPLAIN,
	command_AUTHLOGIN,
	command_AUTHCRAMMD5,
	command_AUTHDIGESTMD5,
	command_DIGESTMD5,
	command_USER,
	command_PASSWORD,
	command_MAILFROM,
	command_RCPTTO,
	command_DATA,
	command_DATABLOCK,
	command_DATAEND,
	command_QUIT,
	command_STARTTLS
};

// TLS/SSL extension
enum SMTP_SECURITY_TYPE
{
	NO_SECURITY,
	USE_TLS,
	USE_SSL,
	DO_NOT_SET
};

typedef struct tagCommand_Entry
{
	SMTP_COMMAND		command;
	int					send_timeout;	 // 0 means no send is required
	int					recv_timeout;	 // 0 means no recv is required
	int					valid_reply_code; // 0 means no recv is required, so no reply code
	ERR					error;
}Command_Entry;

struct Recipient
{
	string Name;
	string Mail;
};
struct Auth
{
	string login;
	string password;
};
struct MAIL
{
	string senderMail;
	string senderName;
	string senderLogin;
	string senderPass;
	string subject;
	string charSet = "US-ASCII";
	string mailer;
	string replyTo;
	bool readReceipt = false;
	vector<Recipient> recipients;
	vector<Recipient> ccrecipients;
	vector<Recipient> bccrecipients;
	vector<string> attachments;
	vector<string> body;
	CSmptXPriority priority = XPRIORITY_NORMAL;
	string header;
	bool html = false;
};
struct SERVER
{
	SMTP_SECURITY_TYPE security = NO_SECURITY;
	bool isConnected = false;
	unsigned short port = 0;
	string name;
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
	string name;
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
	string GetLocalHostName();

	SMTP_SECURITY_TYPE GetSecurityType() const;
	void SetSecurityType(SMTP_SECURITY_TYPE type);
	RETCODE SetSMTPServer(SUPPORTED_SMTP_SERVERS serv_id, SMTP_SECURITY_TYPE sec_type = NO_SECURITY);

	void SetServerAuth(string login, string pass);

	bool isAuthRequire();

	RETCODE InitHandshake();
	RETCODE Handshake();

	string m_sLocalHostName;
	string m_sIPAddr;
	RETCODE Send(MAIL mail);

	RETCODE WrappedSend(MAIL mail);

	RETCODE Connect();

	string SendBuf;
	char *RecvBuf;

	SOCKET hSocket;

	RETCODE Buf_Init();
	RETCODE WSA_Init();
	RETCODE SocksConnect();

	RETCODE ReceiveData(int recv_timeout);
	RETCODE SendData(int send_timeout);

	bool IsCommandSupported(const char* response, const char* command);
	int SmtpXYZdigits();
	void SayHello();
	void SayQuit();
	Command_Entry* FindCommandEntry(SMTP_COMMAND command);

	SERVER server;

	RETCODE ReceiveResponse(Command_Entry* pEntry);

	vector <SUPPORTED_SMTP_SERVER> supported_servers = {
		{GMAIL,		USE_TLS,	"smtp.gmail.com",			587,	true},
		{GMAIL,		USE_SSL,	"smtp.gmail.com",			465,	true},
		{HOTMAIL,	USE_TLS,	"smtp.live.com",			25,		true},
		{AOL,		USE_TLS,	"smtp.aol.com",				587,	true},
		{YAHOO,		USE_SSL,	"plus.smtp.mail.yahoo.com", 465,	true},
	};
};


#endif // __CSMTP_H__
