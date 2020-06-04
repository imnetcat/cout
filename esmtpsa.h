#pragma once
#ifndef _ESMTPSA_H_
#define _ESMTPSA_H_
#include "auth.h"
#include "esmtps.h"

class ESMTPSA : public ESMTPS
{
public:
	ESMTPSA();

	void Connect() override;
	void Disconnect() override;
	void Send() override;
	void Receive() override;

protected:
	RETCODE Command(COMMAND command);

public:
	void SetServerAuth(const string& login, const string& pass);
	RETCODE Auth();
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
};

#endif