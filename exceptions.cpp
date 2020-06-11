#include"exceptions.h"

const char* EMAIL::Exception::UNDEF_MSG_HEADER::what() const noexcept
{
	return "Undefined message header";
}
const char* EMAIL::Exception::UNDEF_MAIL_FROM::what() const noexcept
{
	return "Undefined mail sender";
}
const char* EMAIL::Exception::UNDEF_SUBJECT::what() const noexcept
{
	return "Undefined message subject";
}
const char* EMAIL::Exception::UNDEF_RECIPIENTS::what() const noexcept
{
	return "Undefined at least one reciepent";
}
const char* EMAIL::Exception::UNDEF_RECIPIENT_MAIL::what() const noexcept
{
	return "Undefined recipent mail";
}
const char* EMAIL::Exception::UNDEF_LOGIN::what() const noexcept
{
	return "Undefined user login";
}
const char* EMAIL::Exception::UNDEF_PASSWORD::what() const noexcept
{
	return "Undefined user password";
}
const char* EMAIL::Exception::BAD_SERVER_NAME::what() const noexcept
{
	return "Unable to determine server name for digest MD5 response";
}
const char* EMAIL::Exception::INIT_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending INIT command";
}
const char* EMAIL::Exception::MAIL_FROM_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending MAIL FROM command";
}
const char* EMAIL::Exception::EHLO_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending EHLO command";
}
const char* EMAIL::Exception::HELO_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending HELO command";
}
const char* EMAIL::Exception::AUTH_PLAIN_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH PLAIN command";
}
const char* EMAIL::Exception::AUTH_LOGIN_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH LOGIN command";
}
const char* EMAIL::Exception::AUTH_CRAMMD5_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH CRAMMD5 command";
}
const char* EMAIL::Exception::AUTH_DIGESTMD5_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH DIGESTMD5 command";
}
const char* EMAIL::Exception::DIGESTMD5_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending MD5 DIGEST command";
}
const char* EMAIL::Exception::DATA_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending DATA command";
}
const char* EMAIL::Exception::QUIT_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending QUIT command";
}
const char* EMAIL::Exception::RCPT_TO_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending RCPT TO command";
}
const char* EMAIL::Exception::STARTTLS_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending STARTTLS command";
}
const char* EMAIL::Exception::DATABLOCK_FAILED::what() const noexcept
{
	return "SMTP Failed to send data block";
}
const char* EMAIL::Exception::MSG_BODY_ERROR::what() const noexcept
{
	return "SMTP Error in message body";
}
const char* EMAIL::Exception::MSG_TOO_BIG::what() const noexcept
{
	return "SMTP letter cannot be more than 25 megabytes";
}
const char* EMAIL::Exception::BAD_LOGIN_PASS::what() const noexcept
{
	return "SMTP Bad login or password";
}
const char* EMAIL::Exception::UNDEF_XYZ_RESPONSE::what() const noexcept
{
	return "SMTP Undefined xyz SMTP response";
}
const char* EMAIL::Exception::TIME_ERROR::what() const noexcept
{
	return "SMTP time() error";
}
const char* EMAIL::Exception::STARTTLS_NOT_SUPPORTED::what() const noexcept
{
	return "SMTP The STARTTLS command is not supported by the server";
}
const char* EMAIL::Exception::AUTH_NOT_SUPPORTED::what() const noexcept
{
	return "SMTP AUTH LOGIN is not supported by the server";
}
const char* EMAIL::Exception::STMP_CONNECT::what() const noexcept
{
	return "SMTP connect failed";
}
const char* EMAIL::Exception::SMTP_COMM::what() const noexcept
{
	return "SMTP server return error";
}
const char* EMAIL::Exception::SMTP_AUTH::what() const noexcept
{
	return "SMTP authentication failed";
}
const char* EMAIL::Exception::SMTP_SEND_MAIL::what() const noexcept
{
	return "SMTP send mail failed";
}
const char* EMAIL::Exception::SMTP_SEND::what() const noexcept
{
	return "SMTP send failed";
}
const char* EMAIL::Exception::SMTP_SEND_DATA::what() const noexcept
{
	return "SMTP send data failed";
}
const char* EMAIL::Exception::SMTP_RECV_DATA::what() const noexcept
{
	return "SMTP recv data failed";
}
const char* EMAIL::Exception::SMTP_SEND_DATA_NOSEC::what() const noexcept
{
	return "SMTP send data with no secure failed";
}
const char* EMAIL::Exception::SMTP_RECV_DATA_NOSEC::what() const noexcept
{
	return "SMTP recv data with no secure failed";
}
const char* EMAIL::Exception::SMTP_SEND_DATA_SEC::what() const noexcept
{
	return "SMTP send data with secure failed";
}
const char* EMAIL::Exception::SMTP_RECV_DATA_SEC::what() const noexcept
{
	return "SMTP recv data with secure failed";
}
const char* EMAIL::Exception::SMTP_CREATE_HEADER::what() const noexcept
{
	return "SMTP create header failed";
}
const char* EMAIL::Exception::SMTP_UNDEF_COMM::what() const noexcept
{
	return "SMTP undefined command specified";
}
const char* EMAIL::Exception::EMAIL_SEND::what() const noexcept
{
	return "EMAIL send failed";
}
const char* EMAIL::Exception::EMAIL_UNDEF_SENDER::what() const noexcept
{
	return "EMAIL undefined sender";
}
const char* EMAIL::Exception::EMAIL_UNDEF_RECEIVER::what() const noexcept
{
	return "EMAIL undefined receiver";
}
