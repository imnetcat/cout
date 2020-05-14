#pragma once
#ifndef _ESMTP_H_
#define _ESMTP_H_

#include "smtp.h"

class ESMTP : public SMTP
{
public:
	ESMTP();
	~ESMTP();

	RETCODE Send(MAIL mail);

	RETCODE Handshake();

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
