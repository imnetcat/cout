#pragma once
#include "../../../core/exception/base.h"
namespace Exceptions
{
	namespace smtp
	{
		class command_not_recognized : virtual public base
		{
		public:
			command_not_recognized(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "Command not recognized";
			}
		};
		class undef_mail_from : virtual public base
		{
		public:
			undef_mail_from(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "Undefined mail sender";
			}
		};
		class undef_recipients : virtual public base
		{
		public:
			undef_recipients(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "Undefined at least one reciepent";
			}
		};
		class undef_login : virtual public base
		{
		public:
			undef_login(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "Undefined user login";
			}
		};
		class undef_password : virtual public base
		{
		public:
			undef_password(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "Undefined user password";
			}
		};

		class auth_failed : virtual public base
		{
		public:
			auth_failed(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "SMTP authentication failed";
			}
		};
		class command_failed : virtual public base
		{
		public:
			command_failed(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "SMTP Server returned an error in response to the command";
			}
		};
		class msg_body_error : virtual public base
		{
		public:
			msg_body_error(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "SMTP Error in message body";
			}
		};

		class msg_too_big : virtual public base
		{
		public:
			msg_too_big(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "SMTP letter cannot be more than 25 megabytes";
			}
		};
		class bad_credentials : virtual public base
		{
		public:
			bad_credentials(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "SMTP Invalid password/login or access denied from insecure applications";
			}
		};
		class undef_response : virtual public base
		{
		public:
			undef_response(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "SMTP Undefined xyz SMTP response";
			}
		};
		class time_error : virtual public base
		{
		public:
			time_error(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "SMTP time() error";
			}
		};
		class tls_not_supported : virtual public base
		{
		public:
			tls_not_supported(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "SMTP The STARTTLS command is not supported by the server";
			}
		};
		class auth_not_supported : virtual public base
		{
		public:
			auth_not_supported(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "SMTP AUTH LOGIN is not supported by the server";
			}
		};

		class undef_command : virtual public base
		{
		public:
			undef_command(const std::string& whre, const std::string& when) : base(whre, when) { };
			const std::string what() const noexcept override
			{
				return "SMTP undefined command specified";
			}
		};
	}
}