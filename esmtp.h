#pragma once
#ifndef _ESMTP_H_
#define _ESMTP_H_

#include "core.h"
#include "socket.h"

#include <vector>
#include <string>

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

class ESMTP : public Socket
{
public:
	ESMTP();
	~ESMTP();
	void DisconnectRemoteServer();
	void SetLocalHostName(const char *sLocalHostName);
	std::string GetLocalHostName();

	RETCODE SetSMTPServer(unsigned short int port, const string & name, bool isAuth);

	void SetServerAuth(std::string login, std::string pass);

	bool isAuthRequire();

	RETCODE Auth();

	std::string m_sIPAddr;
	RETCODE Send(MAIL mail);

	RETCODE SendMail();
	
	bool isRetCodeValid(int validCode);

	RETCODE ReceiveData(int timeout);
	RETCODE SendData(int timeout);
	bool IsCommandSupported(std::string response, std::string command);
	int SmtpXYZdigits();
protected:

	MAIL mail;

	RETCODE Init();
	RETCODE Ehlo();
	RETCODE MailFrom();
	RETCODE RCPTto();
	RETCODE Data();
	RETCODE Datablock();
	RETCODE DataEnd();
	RETCODE Quit();

	using COMMAND = const unsigned short int;
	RETCODE Command(COMMAND command);
	static COMMAND INIT = 1;
	static COMMAND EHLO = 2;
	static COMMAND MAILFROM = 3;
	static COMMAND RCPTTO = 4;
	static COMMAND DATA = 5;
	static COMMAND DATABLOCK = 6;
	static COMMAND DATAEND = 7;
	static COMMAND QUIT = 8;
};


#endif // _ESMTP_H_
