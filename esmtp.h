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
protected:
	void Command(COMMAND command);
	void Ehlo();
	void Handshake();
	static const COMMAND EHLO = 9;
};


#endif // _ESMTP_H_
