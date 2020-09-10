#pragma once
#include <openssl/ssl.h>
#include <openssl/err.h>

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#pragma comment (lib, "crypt32")

#include "../core/config.h"
#ifdef INDEBUG
#pragma comment (lib, "libcrypto64MTd.lib")
#pragma comment (lib, "libssl64MTd.lib")
#else
#pragma comment (lib, "libcrypto64MT.lib")
#pragma comment (lib, "libssl64MT.lib")
#endif

namespace Cout
{
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
}