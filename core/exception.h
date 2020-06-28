#pragma once
#include "exception/base.h"
#include "exception/access_denied.h"
#include "exception/invalid_argument.h"
#include "exception/logic_error.h"
#include "exception/non_readable.h"
#include "exception/non_writable.h"
#include "exception/out_of_range.h"
#include "exception/undefined.h"
#include "exception/file_not_exist.h"
#include "exception/file_already_exist.h"
#include "exception/dir_not_exist.h"
#include "exception/dir_already_exist.h"
#include "exception/lack_of_memory.h"
namespace Exceptions
{
	namespace Core
	{
		class wsa_startup : virtual public base
		{
		public:
			wsa_startup(const char* when) : base(when) { };
			wsa_startup(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "WSA startup failed";
			}
		};
		class wsa_version : virtual public base
		{
		public:
			wsa_version(const char* when) : base(when) { };
			wsa_version(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "Invalid WSA version";
			}
		};
		class wsa_send : virtual public base
		{
		public:
			wsa_send(const char* when) : base(when) { };
			wsa_send(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "WSA send error";
			}
		};
		class wsa_recv : virtual public base
		{
		public:
			wsa_recv(const char* when) : base(when) { };
			wsa_recv(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "WSA recv error";
			}
		};
		class wsa_connect : virtual public base
		{
		public:
			wsa_connect(const char* when) : base(when) { };
			wsa_connect(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "WSA connect";
			}
		};
		class wsa_gethostby_name_addr : virtual public base
		{
		public:
			wsa_gethostby_name_addr(const char* when) : base(when) { };
			wsa_gethostby_name_addr(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "WSA gethost by name/addr failed";
			}
		};
		class wsa_invalid_socket : virtual public base
		{
		public:
			wsa_invalid_socket(const char* when) : base(when) { };
			wsa_invalid_socket(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "WSA invalid socket";
			}
		};
		class wsa_hostname : virtual public base
		{
		public:
			wsa_hostname(const char* when) : base(when) { };
			wsa_hostname(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "WSA invalid hostname";
			}
		};
		class wsa_ioctlsocket : virtual public base
		{
		public:
			wsa_ioctlsocket(const char* when) : base(when) { };
			wsa_ioctlsocket(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "WSA ioctlsocket filed";
			}
		};
		class bad_ipv4_addr : virtual public base
		{
		public:
			bad_ipv4_addr(const char* when) : base(when) { };
			bad_ipv4_addr(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "bad ipv4 addr";
			}
		};
		class select_timeout : virtual public base
		{
		public:
			select_timeout(const char* when) : base(when) { };
			select_timeout(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "WSA select timeout";
			}
		};
		class wsa_select : virtual public base
		{
		public:
			wsa_select(const char* when) : base(when) { };
			wsa_select(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "WSA select failed";
			}
		};
		class server_not_responding : virtual public base
		{
		public:
			server_not_responding(const char* when) : base(when) { };
			server_not_responding(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "Server not responding";
			}
		};
		class connect_failed : virtual public base
		{
		public:
			connect_failed(const char* when) : base(when) { };
			connect_failed(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "Failed connect to server";
			}
		};
		class already_connect : virtual public base
		{
		public:
			already_connect(const char* when) : base(when) { };
			already_connect(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "Connection already exist";
			}
		};
		class connection_closed : virtual public base
		{
		public:
			connection_closed(const char* when) : base(when) { };
			connection_closed(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "Connection closed";
			}
		};
		class sendbuf_is_empty : virtual public base
		{
		public:
			sendbuf_is_empty(const char* when) : base(when) { };
			sendbuf_is_empty(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "Send buffer is empty";
			}
		};
		class recvbuf_is_empty : virtual public base
		{
		public:
			recvbuf_is_empty(const char* when) : base(when) { };
			recvbuf_is_empty(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "Recv buffer is empty";
			}
		};

		class openssl_problem : virtual public base
		{
		public:
			openssl_problem(const char* when) : base(when) { };
			openssl_problem(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "OpenSSL error";
			}
		};

		class BAD_LOGIN_PASSWORD : virtual public base
		{
		public:
			BAD_LOGIN_PASSWORD(const char* when) : base(when) { };
			BAD_LOGIN_PASSWORD(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "Invalid user login or password";
			}
		};
		class BAD_DIGEST_RESPONSE : virtual public base
		{
		public:
			BAD_DIGEST_RESPONSE(const char* when) : base(when) { };
			BAD_DIGEST_RESPONSE(const std::string&when) : base(when) { };
			const char* what() const noexcept override
			{
				return "Server returned a bad digest MD5 response";
			}
		};
	}
}
