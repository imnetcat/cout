#pragma once
#ifndef _ESMTPSA_H_
#define _ESMTPSA_H_
#include "esmtpa.h"
#include "esmtps.h"
#include <ctime>

class ESMTPSA : public ESMTPS, public ESMTPA
{
public:
	ESMTPSA(MAIL m);
	RETCODE SetUpSSL() override;
	RETCODE SetUpTLS() override;
	void SetServerAuth(string login, string pass) override;
	RETCODE Auth() override;
};

#endif