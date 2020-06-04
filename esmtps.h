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

	enum SMTP_SECURITY_TYPE
	{
		NO_SECURITY,
		USE_TLS,
		USE_SSL
	};

	void SetSecuriry(SMTP_SECURITY_TYPE type);

	RETCODE SetUpSSL();
	RETCODE SetUpTLS();
protected:
	RETCODE Command(COMMAND command);
private:
	static const COMMAND STARTTLS = 10;
	RETCODE Starttls();
	SMTP_SECURITY_TYPE sec;
};

#endif