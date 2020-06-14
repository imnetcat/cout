#pragma once
#ifndef _CORE_EXCEPTIONS_H_
#define _CORE_EXCEPTIONS_H_
#include "exception_base.h"
namespace CORE
{
	namespace Exception
	{
		class undefined : virtual public base
		{
		public:
			undefined(const char* when) : base(when) { };
			undefined(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		}; 
		class lack_of_memory : virtual public base
		{
		public:
			lack_of_memory(const char* when) : base(when) { };
			lack_of_memory(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class invalid_argument : virtual public base
		{
		public:
			invalid_argument(const char* when) : base(when) { };
			invalid_argument(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class out_of_range : virtual public base
		{
		public:
			out_of_range(const char* when) : base(when) { };
			out_of_range(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class logic_error : virtual public base
		{
		public:
			logic_error(const char* when) : base(when) { };
			logic_error(const std::string&when) : base(when) { 

			};
			const char* what() const noexcept override;
		};
		class file_not_exist : virtual public base
		{
		public:
			file_not_exist(const char* when) : base(when) { };
			file_not_exist(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};

		class wsa_startup : virtual public base
		{
		public:
			wsa_startup(const char* when) : base(when) { };
			wsa_startup(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class wsa_version : virtual public base
		{
		public:
			wsa_version(const char* when) : base(when) { };
			wsa_version(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class wsa_send : virtual public base
		{
		public:
			wsa_send(const char* when) : base(when) { };
			wsa_send(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class wsa_recv : virtual public base
		{
		public:
			wsa_recv(const char* when) : base(when) { };
			wsa_recv(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class wsa_connect : virtual public base
		{
		public:
			wsa_connect(const char* when) : base(when) { };
			wsa_connect(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class wsa_gethostby_name_addr : virtual public base
		{
		public:
			wsa_gethostby_name_addr(const char* when) : base(when) { };
			wsa_gethostby_name_addr(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class wsa_invalid_socket : virtual public base
		{
		public:
			wsa_invalid_socket(const char* when) : base(when) { };
			wsa_invalid_socket(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class wsa_hostname : virtual public base
		{
		public:
			wsa_hostname(const char* when) : base(when) { };
			wsa_hostname(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class wsa_ioctlsocket : virtual public base
		{
		public:
			wsa_ioctlsocket(const char* when) : base(when) { };
			wsa_ioctlsocket(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class bad_ipv4_addr : virtual public base
		{
		public:
			bad_ipv4_addr(const char* when) : base(when) { };
			bad_ipv4_addr(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class select_timeout : virtual public base
		{
		public:
			select_timeout(const char* when) : base(when) { };
			select_timeout(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class wsa_select : virtual public base
		{
		public:
			wsa_select(const char* when) : base(when) { };
			wsa_select(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class server_not_responding : virtual public base
		{
		public:
			server_not_responding(const char* when) : base(when) { };
			server_not_responding(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class connect_failed : virtual public base
		{
		public:
			connect_failed(const char* when) : base(when) { };
			connect_failed(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class already_connect : virtual public base
		{
		public:
			already_connect(const char* when) : base(when) { };
			already_connect(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class connection_closed : virtual public base
		{
		public:
			connection_closed(const char* when) : base(when) { };
			connection_closed(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class sendbuf_is_empty : virtual public base
		{
		public:
			sendbuf_is_empty(const char* when) : base(when) { };
			sendbuf_is_empty(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class recvbuf_is_empty : virtual public base
		{
		public:
			recvbuf_is_empty(const char* when) : base(when) { };
			recvbuf_is_empty(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};

		class openssl_problem : virtual public base
		{
		public:
			openssl_problem(const char* when) : base(when) { };
			openssl_problem(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};

		class BAD_LOGIN_PASSWORD : virtual public CORE::Exception::base
		{
		public:
			BAD_LOGIN_PASSWORD(const char* when) : base(when) { };
			BAD_LOGIN_PASSWORD(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class BAD_DIGEST_RESPONSE : virtual public CORE::Exception::base
		{
		public:
			BAD_DIGEST_RESPONSE(const char* when) : base(when) { };
			BAD_DIGEST_RESPONSE(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
	}
}
#endif