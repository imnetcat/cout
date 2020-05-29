#pragma once
#ifndef _SMTP_H_
#define _SMTP_H_

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


class SMTP : protected Socket
{

public:
	SMTP(MAIL m);
	~SMTP();
	void DisconnectRemoteServer();
	void SetLocalHostName(const char *sLocalHostName);
	std::string GetLocalHostName();

	RETCODE SetSMTPServer(unsigned short int port, const string & name);
	
	std::string m_sIPAddr;

	RETCODE Send(MAIL mail);
	
	RETCODE Handshake();

	bool isRetCodeValid(int validCode);

	virtual RETCODE SetUpSSL() = 0;
	virtual RETCODE SetUpTLS() = 0;
	virtual void SetServerAuth(string login, string pass) = 0;
	virtual RETCODE Auth() = 0;

protected:
	
	bool IsCommandSupported(std::string response, std::string command);
	int SmtpXYZdigits();

	virtual RETCODE Receive(int timeout);
	virtual RETCODE SendData(int timeout);

	std::string SendBuf;
	std::string RecvBuf;

	MAIL mail;

	RETCODE Init();
	RETCODE Helo();
	RETCODE MailFrom();
	RETCODE RCPTto();
	RETCODE Data();
	RETCODE Datablock();
	RETCODE DataEnd();
	RETCODE Quit();

	using COMMAND = const unsigned short int;
	RETCODE Command(COMMAND command);
	static COMMAND INIT = 1;
	static COMMAND HELO = 2;
	static COMMAND MAILFROM = 3;
	static COMMAND RCPTTO = 4;
	static COMMAND DATA = 5;
	static COMMAND DATABLOCK = 6;
	static COMMAND DATAEND = 7;
	static COMMAND QUIT = 8;
};

#endif
