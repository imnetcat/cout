#pragma once
#ifndef _SMTP_H_
#define _SMTP_H_

#include "core.h"
#include "raw.h"

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
	std::vector<Recipient> recipients;
	std::vector<Recipient> ccrecipients;
	std::vector<Recipient> bccrecipients;
	std::vector<std::string> attachments;
	std::vector<std::string> body;
	CSmptXPriority priority = XPRIORITY_NORMAL;
	std::string header;
	bool html = false;
};


class SMTP : public Raw
{

public:
	SMTP();
	~SMTP();

	RETCODE SetSMTPServer(unsigned short int port, const std::string & name);

	void Connect() override;
	void Disconnect() override;
	void Send() override;
	void Receive() override;

	void SendMail(MAIL m);

protected:

	RETCODE Handshake();

	bool isRetCodeValid(int validCode);
	bool IsCommandSupported(std::string response, std::string command);
	int SmtpXYZdigits();

	MAIL mail;

	RETCODE Init();
	RETCODE Helo();
	RETCODE MailFrom();
	RETCODE RCPTto();
	RETCODE Data();
	void Datablock();
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
