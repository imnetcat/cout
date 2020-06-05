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

private:
	void Command(COMMAND command);

	void SetServerAuth(const string& login, const string& pass);
	void Auth();

	struct Creds
	{
		std::string login;
		std::string password;
	};
	bool isAuthRequired = true;
	Creds credentials;

	static const COMMAND AUTHPLAIN = 11;
	static const COMMAND AUTHLOGIN = 12;
	static const COMMAND AUTHCRAMMD5 = 13;
	static const COMMAND AUTHDIGESTMD5 = 14;
	void AuthLogin();
	void AuthPlain();
	void CramMD5();
	void DigestMD5();
};

#endif