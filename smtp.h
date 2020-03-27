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
	command_CRAMMD5_PASSWORD,
	command_AUTHDIGESTMD5,
	command_DIGESTMD5_TOCKEN,
	command_DIGESTMD5_PASS,
	command_USER,
	command_PASSWORD,
	command_MAILFROM,
	command_RCPTTO,
	command_CCRCPTTO,
	command_BCCRCPTTO,
	command_DATA,
	command_DATABLOCK_HEADER,
	command_DATABLOCK_TEXT,
	command_DATABLOCK_FILE_HEADER,
	command_DATABLOCK_FILE,
	command_DATABLOCK_END,
	command_DATA_END,
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

using commandTemplate = string(*)();

struct Command_Entry
{
	SMTP_COMMAND		command;		 // command id
	commandTemplate		getCommandText;  // return command text
	int					send_timeout;	 // 0 means no send is required
	int					recv_timeout;	 // 0 means no recv is required
	int					valid_reply_code; // 0 means no recv is required, so no reply code
	ERR					error;
};

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

	RETCODE WrappedSend();

	RETCODE Connect();

	string SendBuf;
	string RecvBuf;

	SOCKET hSocket;

	RETCODE WSA_Init();
	RETCODE SocksConnect();

	RETCODE ReceiveData(const Command_Entry* pEntry);
	RETCODE SendData(int send_timeout);
	
	MAIL mail;

	string command_Ehlo();
	string command_AuthPlain();
	string command_User();
	string command_Password();
	string command_crammd5();
	string command_crammd5_password();
	string command_dgmd5();
	string command_dgmd5_tocken();
	string command_dgmd5_pass();
	string command_quit();
	string command_mailfrom();
	string command_rcptto();
	string command_ccrcptto();
	string command_bccrcptto();
	string command_data();
	string command_datablock_header();
	string command_datablock_text();
	string command_datablock_file_header();
	string command_datablock_file();
	string command_datablock_end();
	string command_data_end();
	string command_starttls();
	const vector<Command_Entry> command_list =
	{
		{command_INIT,					&command_Ehlo,						0,		 5 * 60,  220, SERVER_NOT_RESPONDING},
		{command_EHLO,					&command_Ehlo,						5 * 60,  5 * 60,  250, COMMAND_EHLO},
		{command_AUTHPLAIN,				&command_AuthPlain,					5 * 60,  5 * 60,  235, COMMAND_AUTH_PLAIN},
		{command_AUTHLOGIN,				&command_AuthPlain,					5 * 60,  5 * 60,  334, COMMAND_AUTH_LOGIN},
		{command_AUTHCRAMMD5,			&command_crammd5,					5 * 60,  5 * 60,  334, COMMAND_AUTH_CRAMMD5},
		{command_CRAMMD5_PASSWORD,      &command_crammd5_password,			5 * 60,  5 * 60,  235, BAD_LOGIN_PASS},
		{command_AUTHDIGESTMD5,			&command_dgmd5,						5 * 60,  5 * 60,  334, COMMAND_AUTH_DIGESTMD5},
		{command_DIGESTMD5_TOCKEN,		&command_dgmd5_tocken,				5 * 60,  5 * 60,  335, COMMAND_DIGESTMD5},
		{command_DIGESTMD5_PASS,		&command_dgmd5_pass,					5 * 60,  5 * 60,  335, COMMAND_DIGESTMD5},
		{command_USER,					&command_User,						5 * 60,  5 * 60,  334, UNDEF_XYZ_RESPONSE},
		{command_PASSWORD,				&command_Password,					5 * 60,  5 * 60,  235, BAD_LOGIN_PASS},
		{command_MAILFROM,				&command_mailfrom,					5 * 60,  5 * 60,  250, COMMAND_MAIL_FROM},
		{command_RCPTTO,				&command_rcptto,						5 * 60,  5 * 60,  250, COMMAND_RCPT_TO},
		{command_CCRCPTTO,				&command_ccrcptto,					5 * 60,  5 * 60,  250, COMMAND_RCPT_TO},
		{command_BCCRCPTTO,				&command_bccrcptto,					5 * 60,  5 * 60,  250, COMMAND_RCPT_TO},
		{command_DATA,					&command_data,						5 * 60,  2 * 60,  354, COMMAND_DATA},
		{command_DATABLOCK_HEADER,		&command_datablock_header,			3 * 60,  0,			0, COMMAND_DATABLOCK},	// Here the valid_reply_code is set to zero because there are no replies when sending data blocks
		{command_DATABLOCK_TEXT,		&command_datablock_text,				3 * 60,  0,			0, COMMAND_DATABLOCK},
		{command_DATABLOCK_FILE_HEADER,	&command_datablock_file_header,		3 * 60,  0,			0, COMMAND_DATABLOCK},
		{command_DATABLOCK_FILE,		&command_datablock_file,				3 * 60,  0,			0, COMMAND_DATABLOCK},
		{command_DATABLOCK_END,			&command_datablock_end,				3 * 60,  0,			0, COMMAND_DATABLOCK},
		{command_DATA_END,				&command_data_end,					3 * 60,  10 * 60, 250, MSG_BODY_ERROR},
		{command_QUIT,					&command_quit,						5 * 60,  5 * 60,  221, COMMAND_QUIT},
		{command_STARTTLS,				&command_starttls,					5 * 60,  5 * 60,  220, COMMAND_EHLO_STARTTLS}
	};

	bool IsCommandSupported(string response, string command);
	int SmtpXYZdigits();
	RETCODE Command(SMTP_COMMAND command);
	const Command_Entry* FindCommandEntry(SMTP_COMMAND command);

	SERVER server;

	vector <SUPPORTED_SMTP_SERVER> supported_servers = {
		{GMAIL,		USE_TLS,	"smtp.gmail.com",			587,	true},
		{GMAIL,		USE_SSL,	"smtp.gmail.com",			465,	true},
		{HOTMAIL,	USE_TLS,	"smtp.live.com",			25,		true},
		{AOL,		USE_TLS,	"smtp.aol.com",				587,	true},
		{YAHOO,		USE_SSL,	"plus.smtp.mail.yahoo.com", 465,	true},
	};
};


#endif // _SMTP_H_
