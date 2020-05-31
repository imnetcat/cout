#pragma once
#ifndef _ESMTPSA_H_
#define _ESMTPSA_H_
#include "esmtp.h"
#include "OpenSSL.h"
#include "auth.h"

class ESMTPSA : public ESMTP, private OpenSSL
{
public:
	ESMTPSA(MAIL m);

	void Connect() override;
	void Disconnect() override;
	void Send() override;
	void Receive() override;

protected:
	RETCODE Command(COMMAND command);

	// ESMTPA stuff
public:
	void SetServerAuth(string login, string pass) override;
	RETCODE Auth() override;
protected:

	struct Creds
	{
		std::string login;
		std::string password;
	};
	bool isAuthRequired = true;
	Creds credentials;

	static COMMAND AUTHPLAIN = 10;
	static COMMAND AUTHLOGIN = 11;
	static COMMAND AUTHCRAMMD5 = 12;
	static COMMAND AUTHDIGESTMD5 = 13;
	RETCODE AuthLogin();
	RETCODE AuthPlain();
	RETCODE CramMD5();
	RETCODE DigestMD5();

	// ESMTPS stuff
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

	RETCODE SetUpSSL() override;
	RETCODE SetUpTLS() override;

protected:
	static COMMAND STARTTLS = 9;
	RETCODE Starttls();
private:
	SMTP_SECURITY_TYPE sec;
};

#endif