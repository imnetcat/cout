#pragma once
#ifndef _ESMTPA_H_
#define _ESMTPA_H_
#include "esmtp.h"
#include <ctime>

class ESMTPA : ESMTP
{
protected:
	enum COMMANDS
	{
		AUTHPLAIN,
		AUTHLOGIN,
		AUTHCRAMMD5,
		AUTHDIGESTMD5
	};
	RETCODE AuthLogin();
	RETCODE AuthPlain();
	RETCODE CramMD5();
	RETCODE DigestMD5();
	RETCODE Command(COMMANDS command);
};

#endif