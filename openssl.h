#pragma once

#include "esmtp.h"

#include <openssl/ssl.h>
#include <openssl/err.h>

#pragma comment (lib, "crypt32")
#pragma comment (lib, "libcrypto64MTd.lib")
#pragma comment (lib, "libssl64MTd.lib")

class OpenSSL : private Socket
{
public:
	OpenSSL();
	~OpenSSL();
	string ReceiveData(int send_timeout) override;
	RETCODE SendData(const string& data, int send_timeout) override;
	RETCODE OpenSSLConnect();
protected:
	SSL_CTX*      ctx;
	SSL*          ssl;
};
