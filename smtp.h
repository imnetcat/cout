#pragma once
#ifndef _SMTP_H_
#define _SMTP_H_

#include "core.h"
#include "raw.h"

#include <vector>
#include <string>

#define MSG_SIZE_IN_MB	25		// the maximum size of the message with all attachments
#define COUNTER_VALUE	100		// how many times program will try to receive data

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
	
	static const std::string BOUNDARY_TEXT;

	struct MAIL
	{
		struct Recipient
		{
			std::string Name;
			std::string Mail;
		};
		enum CSmptXPriority
		{
			XPRIORITY_HIGH = 2,
			XPRIORITY_NORMAL = 3,
			XPRIORITY_LOW = 4
		};
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

	void SendMail(MAIL m);
protected:
		
	RETCODE Handshake();

	bool isRetCodeValid(int validCode) const;
	bool IsCommandSupported(const std::string& response, const std::string& command) const;
	int SmtpXYZdigits() const;

	using COMMAND = const unsigned short int;
	RETCODE Command(COMMAND command);
	static const COMMAND INIT = 1;
private:
	MAIL mail;
	RETCODE createHeader();
	static const COMMAND HELO = 2;
	static const COMMAND MAILFROM = 3;
	static const COMMAND RCPTTO = 4;
	static const COMMAND DATA = 5;
	static const COMMAND DATABLOCK = 6;
	static const COMMAND DATAEND = 7;
	static const COMMAND QUIT = 8;
	RETCODE Init();
	RETCODE Helo();
	RETCODE MailFrom();
	RETCODE RCPTto();
	RETCODE Data();
	void Datablock();
	RETCODE DataEnd();
	RETCODE Quit();
};

#endif
