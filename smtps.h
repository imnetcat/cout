#pragma once
#ifndef _SMTPS_H_
#define _SMTPS_H_

#include "smtp.h"

#include <openssl/ssl.h>
#include <openssl/err.h>

#pragma comment (lib, "crypt32")
#pragma comment (lib, "libcrypto64MTd.lib")
#pragma comment (lib, "libssl64MTd.lib")

class SMTPS : public ESMTP
{
public:
	SMTPS();
	~SMTPS();

	// TLS/SSL extension
	enum SMTP_SECURITY_TYPE
	{
		NO_SECURITY,
		USE_TLS,
		USE_SSL
	};
	RETCODE SendData(int timeout);
	RETCODE ReceiveData(int timeout);
	RETCODE Send(MAIL m, SMTP_SECURITY_TYPE sec);
	RETCODE ReceiveData_SSL(int send_timeout);
	RETCODE SendData_SSL(int send_timeout);
protected:
	void CleanupOpenSSL();
	RETCODE OpenSSLConnect();
	RETCODE InitOpenSSL();
	SSL_CTX*      ctx;
	SSL*          ssl;
};

#endif
