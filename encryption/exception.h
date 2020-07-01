#pragma once
#include "../core/exception/base.h"
namespace Exceptions
{
	namespace Encryption
	{
		class openssl_problem : virtual public base
		{
		public:
			openssl_problem(const char* when) : base(when) { };
			openssl_problem(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "OpenSSL undefined error";
			}
		};
		class openssl_zero_return : virtual public base
		{
		public:
			openssl_zero_return(const char* when) : base(when) { };
			openssl_zero_return(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "The TLS/SSL peer has closed the connection for writing by sending the close_notify alert";
			}
		};
		class openssl_syscall : virtual public base
		{
		public:
			openssl_syscall(const char* when) : base(when) { };
			openssl_syscall(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "Some non-recoverable, fatal I/O error occurred";
			}
		};
		class openssl_want_async : virtual public base
		{
		public:
			openssl_want_async(const char* when) : base(when) { };
			openssl_want_async(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "The operation did not complete because an asynchronous engine is still processing data";
			}
		};
		class openssl_want_lookup : virtual public base
		{
		public:
			openssl_want_lookup(const char* when) : base(when) { };
			openssl_want_lookup(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "The operation did not complete because an application callback set by \
						SSL_CTX_set_client_cert_cb() has asked to be called again";
			}
		};
		class openssl_want_accept : virtual public base
		{
		public:
			openssl_want_accept(const char* when) : base(when) { };
			openssl_want_accept(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "The underlying BIO was not connected yet to the peer \
						and the call would block in accept()";
			}
		};
		class openssl_want_connect : virtual public base
		{
		public:
			openssl_want_connect(const char* when) : base(when) { };
			openssl_want_connect(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "The underlying BIO was not connected yet to the peer \
						and the call would block in connect()";
			}
		};
	}
}
