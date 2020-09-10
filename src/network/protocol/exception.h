#pragma once
#include "../../core/exception/base.h"
namespace Exceptions
{
	namespace wsa
	{
		class startup : virtual public base
		{
		public:
			startup(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "WSA startup failed";
			}
		};
		class version : virtual public base
		{
		public:
			version(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "Invalid WSA version";
			}
		};
		class send : virtual public base
		{
		public:
			send(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "WSA send error";
			}
		};
		class recv : virtual public base
		{
		public:
			recv(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "WSA recv error";
			}
		};
		class connect : virtual public base
		{
		public:
			connect(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "WSA connect";
			}
		};
		class gethostby_name_addr : virtual public base
		{
		public:
			gethostby_name_addr(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "WSA gethost by name/addr failed";
			}
		};
		class invalid_socket : virtual public base
		{
		public:
			invalid_socket(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "WSA invalid socket";
			}
		};
		class hostname : virtual public base
		{
		public:
			hostname(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "WSA invalid hostname";
			}
		};
		class ioctlsocket : virtual public base
		{
		public:
			ioctlsocket(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "WSA ioctlsocket filed";
			}
		};
		class bad_ipv4_addr : virtual public base
		{
		public:
			bad_ipv4_addr(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "bad ipv4 addr";
			}
		};
		class select_timeout : virtual public base
		{
		public:
			select_timeout(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "WSA select timeout";
			}
		};
		class select : virtual public base
		{
		public:
			select(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "WSA select failed";
			}
		};
		class server_not_responding : virtual public base
		{
		public:
			server_not_responding(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "Server not responding";
			}
		};
		class connect_failed : virtual public base
		{
		public:
			connect_failed(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "Failed connect to server";
			}
		};
		class already_connect : virtual public base
		{
		public:
			already_connect(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "Connection already exist";
			}
		};
		class connection_closed : virtual public base
		{
		public:
			connection_closed(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "Connection closed";
			}
		};
		class sendbuf_is_empty : virtual public base
		{
		public:
			sendbuf_is_empty(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "Send buffer is empty";
			}
		};
		class recvbuf_is_empty : virtual public base
		{
		public:
			recvbuf_is_empty(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "Recv buffer is empty";
			}
		};
	}
}
