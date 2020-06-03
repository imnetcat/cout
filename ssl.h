#pragma once
#include "openssl.h"

template<class Proto>
class SSL_ : public Proto, private OpenSSL
{
public:
	SSL_();

	void Connect() override;
	void Disconnect() override;
	void Send() override;
	void Receive() override;
};
