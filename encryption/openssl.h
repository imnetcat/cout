#pragma once
#ifndef _OPENSSL_H_
#define _OPENSSL_H_
#include <openssl/ssl.h>
#include <openssl/err.h>
#pragma comment (lib, "crypt32")
#pragma comment (lib, "libcrypto64MTd.lib")
#pragma comment (lib, "libssl64MTd.lib")
namespace Encryption
{
	class OpenSSL
	{
	public:
		OpenSSL();
		~OpenSSL();
	protected:
		SSL_CTX*      ctx;
		SSL*          ssl;
	};
}
#endif