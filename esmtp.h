#pragma once
#ifndef _ESMTP_H_
#define _ESMTP_H_

#include "smtp.h"

class ESMTP : public SMTP
{
public:
	ESMTP();
	~ESMTP();

	void Connect() override;
	void Disconnect() override;
	void Send() override;
	void Receive() override;

	RETCODE Handshake();

protected:

	RETCODE Ehlo();

	RETCODE Command(COMMAND command);
	static const COMMAND INIT = 1;
	static const COMMAND EHLO = 2;
	static const COMMAND MAILFROM = 3;
	static const COMMAND RCPTTO = 4;
	static const COMMAND DATA = 5;
	static const COMMAND DATABLOCK = 6;
	static const COMMAND DATAEND = 7;
	static const COMMAND QUIT = 8;
};


#endif // _ESMTP_H_
