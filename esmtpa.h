#pragma once
#ifndef _ESMTPA_H_
#define _ESMTPA_H_
#include "esmtp.h"
#include <ctime>

class ESMTPA : public ESMTP
{
public:
	void SetServerAuth(string login, string pass);
	RETCODE Send(MAIL m);
protected:

	struct Auth
	{
		std::string login;
		std::string password;
	};
	bool isAuthRequired = true;
	Auth credentials;

	static COMMAND AUTHPLAIN = 10;
	static COMMAND AUTHLOGIN = 11;
	static COMMAND AUTHCRAMMD5 = 12;
	static COMMAND AUTHDIGESTMD5 = 13;
	RETCODE Auth();
	RETCODE AuthLogin();
	RETCODE AuthPlain();
	RETCODE CramMD5();
	RETCODE DigestMD5();
	RETCODE Command(COMMAND command);
};

#endif