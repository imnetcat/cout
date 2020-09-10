#include "aes-256-gcm.h"

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include "../../core/config.h"
#include "../exception.h"
#include "../../core/exception.h"
using namespace std;
using namespace Cout::Encryption::Exceptions;
using namespace Cout::Encryption::Algorithm;

AES256gcm::AES256gcm() :
	_tag(nullptr), _tag_length(16),
	_aad(nullptr), _aad_length(0),
	_iv(nullptr), _iv_length(0),
	_key(nullptr) {}

AES256gcm& AES256gcm::Tag(const Cout::UnsignedBinary& tag)
{
	_tag = const_cast<unsigned char*>(tag.data());
	_tag_length = (int)tag.size();
	return *this;
}
AES256gcm& AES256gcm::Aad(const Cout::UnsignedBinary& aad)
{
	_aad = const_cast<unsigned char*>(aad.data());
	_aad_length = (int)aad.size();
	return *this;
}
AES256gcm& AES256gcm::Iv(const Cout::UnsignedBinary& iv)
{
	_iv = const_cast<unsigned char*>(iv.data());
	_iv_length = (int)iv.size();
	return *this;
}
AES256gcm& AES256gcm::Key(const Cout::UnsignedBinary& key)
{
	_key = const_cast<unsigned char*>(key.data());
	return *this;
}

Cout::UnsignedBinary AES256gcm::Encode(const Cout::UnsignedBinary& data_to_encode)
{
	if(!_key)
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "missing key for aes encrypting");
	if (!_iv)
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "missing IV for aes encrypting");

	EVP_CIPHER_CTX *ctx;
	int len;
	int ciphertext_len;

	/* Create and initialise the context */
	if (!(ctx = EVP_CIPHER_CTX_new()))
		throw aes_256_gcm_context(WHERE, "encrypting");

	/* Initialise the encryption operation. */
	if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL))
		throw aes_256_gcm_init(WHERE, "encrypting");

	/*
	 * Set IV length if default 12 bytes (96 bits) is not appropriate
	 */
	if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, _iv_length, NULL))
		throw aes_256_gcm_problem(WHERE, "encrypting setting up IV length");

	/* Initialise key and IV */
	if (1 != EVP_EncryptInit_ex(ctx, NULL, NULL, _key, _iv))
		throw aes_256_gcm_problem(WHERE, "encrypting setting up key and IV");

	/*
	 * Provide any AAD data. This can be called zero or more times as
	 * required
	 */
	if (1 != EVP_EncryptUpdate(ctx, NULL, &len, _aad, _aad_length))
		throw aes_256_gcm_problem(WHERE, "encrypting setting up aad");

	/*
	 * Provide the message to be encrypted, and obtain the encrypted output.
	 * EVP_EncryptUpdate can be called multiple times if necessary
	 */
	unsigned char* ciphertext = new unsigned char[data_to_encode.size()];
	if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, data_to_encode.data(), (int)data_to_encode.size()))
		throw aes_256_gcm_problem(WHERE, "encrypting encrypting update");

	ciphertext_len = len;

	/*
	 * Finalise the encryption. Normally ciphertext bytes may be written at
	 * this stage, but this does not occur in GCM mode
	 */
	if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
		throw aes_256_gcm_problem(WHERE, "encrypting finalize");

	ciphertext_len += len;

	if (!_tag)
		_tag = new unsigned char[16];

	// Get the tag 
	if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, _tag))
		throw aes_256_gcm_problem(WHERE, "encrypting getting tag");

	// Clean up
	EVP_CIPHER_CTX_free(ctx);

	// Fetch result
	Cout::UnsignedBinary result;
	for (int i = 0; i < ciphertext_len; i++)
	{
		result.push_back(ciphertext[i]);
	}
	return result;
}

Cout::UnsignedBinary AES256gcm::Decode(const Cout::UnsignedBinary& ciphertext)
{
	if (!_key)
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "missing key for aes decrypting");
	if (!_aad)
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "missing AAD for aes decrypting");
	if (!_iv)
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "missing IV for aes decrypting");
	if (!_tag)
		throw Cout::Exceptions::Core::invalid_argument(WHERE, "missing tag for aes decrypting");

	EVP_CIPHER_CTX *ctx;
	int len;
	int plaintext_len;
	int ret;

	/* Create and initialise the context */
	if (!(ctx = EVP_CIPHER_CTX_new()))
		throw aes_256_gcm_context(WHERE, "decrypting");

	/* Initialise the decryption operation. */
	if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL))
		throw aes_256_gcm_init(WHERE, "decrypting");

	/* Set IV length. Not necessary if this is 12 bytes (96 bits) */
	if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, _iv_length, NULL))
		throw aes_256_gcm_problem(WHERE, "decrypting setting up IV length");

	/* Initialise key and IV */
	if (!EVP_DecryptInit_ex(ctx, NULL, NULL, _key, _iv))
		throw aes_256_gcm_problem(WHERE, "decrypting setting up key and IV");

	/*
	 * Provide any AAD data. This can be called zero or more times as
	 * required
	 */
	if (!EVP_DecryptUpdate(ctx, NULL, &len, _aad, _aad_length))
		throw aes_256_gcm_problem(WHERE, "decrypting update aad");

	/*
	 * Provide the message to be decrypted, and obtain the plaintext output.
	 * EVP_DecryptUpdate can be called multiple times if necessary
	 */
	unsigned char* plaintext = new unsigned char[ciphertext.size()];

	if (ciphertext.size())
	{
		if (!EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext.data(), (int)ciphertext.size()))
			throw aes_256_gcm_problem(WHERE, "decrypting update chiperdata");
	}

	plaintext_len = len;

	/* Set expected tag value. Works in OpenSSL 1.0.1d and later */
	if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, _tag))
		throw aes_256_gcm_problem(WHERE, "decrypting setting up tag");

	/*
	 * Finalise the decryption. A positive return value indicates success,
	 * anything else is a failure - the plaintext is not trustworthy.
	 */
	ret = EVP_DecryptFinal_ex(ctx, plaintext + len, &len);

	/* Clean up */
	EVP_CIPHER_CTX_free(ctx);

	if (ret < 0) 
	{
		throw aes_256_gcm_problem(WHERE, "finalise and verify");
	}

	/* Success */
	plaintext_len += len;

	Cout::UnsignedBinary result;
	for (int i = 0; i < plaintext_len; i++)
	{
		result.push_back(plaintext[i]);
	}
	return result;
}
