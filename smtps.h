#pragma once
#ifndef _SMTPS_H_
#define _SMTPS_H_

#include "smtp.h"

#include <openssl/ssl.h>
#include <openssl/err.h>

#pragma comment (lib, "crypt32")
#pragma comment (lib, "libcrypto64MTd.lib")
#pragma comment (lib, "libssl64MTd.lib")

class SMTPS : public SMTP
{
public:
	SMTPS();
	virtual ~SMTPS();

	RETCODE send(MAIL mail);

	RETCODE SecHandshakeTls();
	RETCODE InitSecurity();

	SSL_CTX*      m_ctx;
	SSL*          m_ssl;

	RETCODE InitOpenSSL();
	RETCODE OpenSSLConnect();
	void CleanupOpenSSL();
	RETCODE ReceiveData_SSL(SSL* ssl, int recv_timeout);
	RETCODE SendData_SSL(SSL* ssl, int send_timeout);
	RETCODE StartTls();
};


#endif // __CSMTP_H__
