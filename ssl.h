#pragma once
#include "openssl.h"
#include "esmtp.h"

class SSL_ : public ESMTP, private OpenSSL
{
public:
	SSL_();

	void Connect() override;
	void Disconnect() override;
	void Send() override;
	void Receive() override;
};
