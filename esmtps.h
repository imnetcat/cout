#pragma once
#ifndef _SMTPS_H_
#define _SMTPS_H_

#include "esmtp.h"
#include "OpenSSL.h"

class ESMTPS : public ESMTP, private OpenSSL
{
public:
	ESMTPS(MAIL m);
	~ESMTPS();

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

	RETCODE SetUpSSL() override;
	RETCODE SetUpTLS() override;
		
	RETCODE SendData(int timeout) override;
	RETCODE Receive(int timeout) override;
protected:
	static COMMAND STARTTLS = 9;
	RETCODE Command(COMMAND command);
	RETCODE Starttls();
private:
	SMTP_SECURITY_TYPE sec;
};

#endif
