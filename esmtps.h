#pragma once
#ifndef _ESMTPS_H_
#define _ESMTPS_H_
#include "ssl.h"
#include "esmtp.h"


class ESMTPS : public SSL_<ESMTP>
{
public:
	ESMTPS();

	void Connect() override;
	void Disconnect() override;
	void Send() override;
	void Receive() override;

protected:
	RETCODE Command(COMMAND command);

public:
	enum SMTP_SECURITY_TYPE
	{
		NO_SECURITY,
		USE_TLS,
		USE_SSL
	};

	void SetSecuriry(SMTP_SECURITY_TYPE type)
	{
		sec = type;
	}

	RETCODE SetUpSSL();
	RETCODE SetUpTLS();

protected:
	static const COMMAND STARTTLS = 9;
	RETCODE Starttls();
private:
	SMTP_SECURITY_TYPE sec;
};

#endif