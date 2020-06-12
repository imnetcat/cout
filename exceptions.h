#pragma once
#ifndef _EMAIL_EXCEPTIONS_H_
#define _EMAIL_EXCEPTIONS_H_
#include "core/except.h"
namespace EMAIL
{
	namespace Exception
	{
		class server_not_specified : virtual public CORE::Exception::base
		{
		public:
			server_not_specified(const char* when) : base(when) { };
			server_not_specified(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class UNDEF_MSG_HEADER : virtual public CORE::Exception::base
		{
		public:
			UNDEF_MSG_HEADER(const char* when) : base(when) { };
			UNDEF_MSG_HEADER(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class UNDEF_MAIL_FROM : virtual public CORE::Exception::base
		{
		public:
			UNDEF_MAIL_FROM(const char* when) : base(when) { };
			UNDEF_MAIL_FROM(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class UNDEF_SUBJECT : virtual public CORE::Exception::base
		{
		public:
			UNDEF_SUBJECT(const char* when) : base(when) { };
			UNDEF_SUBJECT(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class UNDEF_RECIPIENTS : virtual public CORE::Exception::base
		{
		public:
			UNDEF_RECIPIENTS(const char* when) : base(when) { };
			UNDEF_RECIPIENTS(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class UNDEF_RECIPIENT_MAIL : virtual public CORE::Exception::base
		{
		public:
			UNDEF_RECIPIENT_MAIL(const char* when) : base(when) { };
			UNDEF_RECIPIENT_MAIL(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class UNDEF_LOGIN : virtual public CORE::Exception::base
		{
		public:
			UNDEF_LOGIN(const char* when) : base(when) { };
			UNDEF_LOGIN(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class UNDEF_PASSWORD : virtual public CORE::Exception::base
		{
		public:
			UNDEF_PASSWORD(const char* when) : base(when) { };
			UNDEF_PASSWORD(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class BAD_SERVER_NAME : virtual public CORE::Exception::base
		{
		public:
			BAD_SERVER_NAME(const char* when) : base(when) { };
			BAD_SERVER_NAME(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};

		class INIT_FAILED : virtual public CORE::Exception::base
		{
		public:
			INIT_FAILED(const char* when) : base(when) { };
			INIT_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class MAIL_FROM_FAILED : virtual public CORE::Exception::base
		{
		public:
			MAIL_FROM_FAILED(const char* when) : base(when) { };
			MAIL_FROM_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class EHLO_FAILED : virtual public CORE::Exception::base
		{
		public:
			EHLO_FAILED(const char* when) : base(when) { };
			EHLO_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class HELO_FAILED : virtual public CORE::Exception::base
		{
		public:
			HELO_FAILED(const char* when) : base(when) { };
			HELO_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class AUTH_PLAIN_FAILED : virtual public CORE::Exception::base
		{
		public:
			AUTH_PLAIN_FAILED(const char* when) : base(when) { };
			AUTH_PLAIN_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class AUTH_LOGIN_FAILED : virtual public CORE::Exception::base
		{
		public:
			AUTH_LOGIN_FAILED(const char* when) : base(when) { };
			AUTH_LOGIN_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class AUTH_CRAMMD5_FAILED : virtual public CORE::Exception::base
		{
		public:
			AUTH_CRAMMD5_FAILED(const char* when) : base(when) { };
			AUTH_CRAMMD5_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class AUTH_DIGESTMD5_FAILED : virtual public CORE::Exception::base
		{
		public:
			AUTH_DIGESTMD5_FAILED(const char* when) : base(when) { };
			AUTH_DIGESTMD5_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class DIGESTMD5_FAILED : virtual public CORE::Exception::base
		{
		public:
			DIGESTMD5_FAILED(const char* when) : base(when) { };
			DIGESTMD5_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class DATA_FAILED : virtual public CORE::Exception::base
		{
		public:
			DATA_FAILED(const char* when) : base(when) { };
			DATA_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class QUIT_FAILED : virtual public CORE::Exception::base
		{
		public:
			QUIT_FAILED(const char* when) : base(when) { };
			QUIT_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class RCPT_TO_FAILED : virtual public CORE::Exception::base
		{
		public:
			RCPT_TO_FAILED(const char* when) : base(when) { };
			RCPT_TO_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class STARTTLS_FAILED : virtual public CORE::Exception::base
		{
		public:
			STARTTLS_FAILED(const char* when) : base(when) { };
			STARTTLS_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class DATABLOCK_FAILED : virtual public CORE::Exception::base
		{
		public:
			DATABLOCK_FAILED(const char* when) : base(when) { };
			DATABLOCK_FAILED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class MSG_BODY_ERROR : virtual public CORE::Exception::base
		{
		public:
			MSG_BODY_ERROR(const char* when) : base(when) { };
			MSG_BODY_ERROR(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};

		class MSG_TOO_BIG : virtual public CORE::Exception::base
		{
		public:
			MSG_TOO_BIG(const char* when) : base(when) { };
			MSG_TOO_BIG(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class BAD_LOGIN_PASS : virtual public CORE::Exception::base
		{
		public:
			BAD_LOGIN_PASS(const char* when) : base(when) { };
			BAD_LOGIN_PASS(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class UNDEF_XYZ_RESPONSE : virtual public CORE::Exception::base
		{
		public:
			UNDEF_XYZ_RESPONSE(const char* when) : base(when) { };
			UNDEF_XYZ_RESPONSE(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class TIME_ERROR : virtual public CORE::Exception::base
		{
		public:
			TIME_ERROR(const char* when) : base(when) { };
			TIME_ERROR(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class STARTTLS_NOT_SUPPORTED : virtual public CORE::Exception::base
		{
		public:
			STARTTLS_NOT_SUPPORTED(const char* when) : base(when) { };
			STARTTLS_NOT_SUPPORTED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class AUTH_NOT_SUPPORTED : virtual public CORE::Exception::base
		{
		public:
			AUTH_NOT_SUPPORTED(const char* when) : base(when) { };
			AUTH_NOT_SUPPORTED(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};

		class STMP_CONNECT : virtual public CORE::Exception::base
		{
		public:
			STMP_CONNECT(const char* when) : base(when) { };
			STMP_CONNECT(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class SMTP_COMM : virtual public CORE::Exception::base
		{
		public:
			SMTP_COMM(const char* when) : base(when) { };
			SMTP_COMM(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class SMTP_AUTH : virtual public CORE::Exception::base
		{
		public:
			SMTP_AUTH(const char* when) : base(when) { };
			SMTP_AUTH(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class SMTP_SEND_MAIL : virtual public CORE::Exception::base
		{
		public:
			SMTP_SEND_MAIL(const char* when) : base(when) { };
			SMTP_SEND_MAIL(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class SMTP_SEND : virtual public CORE::Exception::base
		{
		public:
			SMTP_SEND(const char* when) : base(when) { };
			SMTP_SEND(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class SMTP_SEND_DATA : virtual public CORE::Exception::base
		{
		public:
			SMTP_SEND_DATA(const char* when) : base(when) { };
			SMTP_SEND_DATA(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class SMTP_RECV_DATA : virtual public CORE::Exception::base
		{
		public:
			SMTP_RECV_DATA(const char* when) : base(when) { };
			SMTP_RECV_DATA(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class SMTP_SEND_DATA_NOSEC : virtual public CORE::Exception::base
		{
		public:
			SMTP_SEND_DATA_NOSEC(const char* when) : base(when) { };
			SMTP_SEND_DATA_NOSEC(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class SMTP_RECV_DATA_NOSEC : virtual public CORE::Exception::base
		{
		public:
			SMTP_RECV_DATA_NOSEC(const char* when) : base(when) { };
			SMTP_RECV_DATA_NOSEC(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class SMTP_SEND_DATA_SEC : virtual public CORE::Exception::base
		{
		public:
			SMTP_SEND_DATA_SEC(const char* when) : base(when) { };
			SMTP_SEND_DATA_SEC(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class SMTP_RECV_DATA_SEC : virtual public CORE::Exception::base
		{
		public:
			SMTP_RECV_DATA_SEC(const char* when) : base(when) { };
			SMTP_RECV_DATA_SEC(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class SMTP_CREATE_HEADER : virtual public CORE::Exception::base
		{
		public:
			SMTP_CREATE_HEADER(const char* when) : base(when) { };
			SMTP_CREATE_HEADER(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class SMTP_UNDEF_COMM : virtual public CORE::Exception::base
		{
		public:
			SMTP_UNDEF_COMM(const char* when) : base(when) { };
			SMTP_UNDEF_COMM(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};

		class EMAIL_SEND : virtual public CORE::Exception::base
		{
		public:
			EMAIL_SEND(const char* when) : base(when) { };
			EMAIL_SEND(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class EMAIL_UNDEF_SENDER : virtual public CORE::Exception::base
		{
		public:
			EMAIL_UNDEF_SENDER(const char* when) : base(when) { };
			EMAIL_UNDEF_SENDER(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
		class EMAIL_UNDEF_RECEIVER : virtual public CORE::Exception::base
		{
		public:
			EMAIL_UNDEF_RECEIVER(const char* when) : base(when) { };
			EMAIL_UNDEF_RECEIVER(const std::string&when) : base(when) { };
			const char* what() const noexcept override;
		};
	}
}
#endif
