#pragma once
#ifndef _SMTPS_H_
#define _SMTPS_H_

#include "esmtp.h"
#include "OpenSSL.h"

class ESMTPS : public ESMTP, private OpenSSL
{
public:
	ESMTPS();
	~ESMTPS();

	enum SMTP_SECURITY_TYPE
	{
		NO_SECURITY,
		USE_TLS,
		USE_SSL
	};

	RETCODE SetUpSSL();
	RETCODE SetUpTLS();
	
	RETCODE SendData(int timeout);
	RETCODE ReceiveData(int timeout);
	RETCODE Send(MAIL m, SMTP_SECURITY_TYPE sec);
protected:
	static COMMAND STARTTLS = 9;
	RETCODE Command(COMMAND command);
	RETCODE Starttls();

	void CleanupOpenSSL();
	RETCODE OpenSSLConnect();
};

#endif
