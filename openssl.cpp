#include "openssl.h"

OpenSSL::OpenSSL()
{
	ctx = NULL;
	DEBUG_LOG(2, "������������� openssl");
	SSL_library_init();
	SSL_load_error_strings();
	ctx = SSL_CTX_new(SSLv23_client_method());
	if (ctx == NULL)
		throw CORE::Exception::openssl_problem("initialize OpenSSL");
}

OpenSSL::~OpenSSL()
{
	if (ssl != NULL)
	{
		SSL_shutdown(ssl);  // send SSL/TLS close_notify
		SSL_free(ssl);
		ssl = NULL;
	}
	if (ctx != NULL)
	{
		SSL_CTX_free(ctx);
		ctx = NULL;
		ERR_remove_state(0);
		ERR_free_strings();
		EVP_cleanup();
		CRYPTO_cleanup_all_ex_data();
	}
}