#pragma once
#ifndef _ESMTPSA_H_
#define _ESMTPSA_H_
#include "esmtpa.h"
#include "esmtps.h"
#include <ctime>

class ESMTPSA : ESMTPS, ESMTPA
{
protected:
	RETCODE Send(MAIL m, SMTP_SECURITY_TYPE sec);
	RETCODE Command(COMMAND command);
};

#endif