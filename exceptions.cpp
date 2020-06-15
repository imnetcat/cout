#include"exceptions.h"
const char* SMTP::Exception::UNDEF_MSG_HEADER::what() const noexcept
{
	return "Undefined message header";
}
const char* SMTP::Exception::UNDEF_MAIL_FROM::what() const noexcept
{
	return "Undefined mail sender";
}
const char* SMTP::Exception::UNDEF_SUBJECT::what() const noexcept
{
	return "Undefined message subject";
}
const char* SMTP::Exception::UNDEF_RECIPIENTS::what() const noexcept
{
	return "Undefined at least one reciepent";
}
const char* SMTP::Exception::UNDEF_RECIPIENT_MAIL::what() const noexcept
{
	return "Undefined recipent mail";
}
const char* SMTP::Exception::UNDEF_LOGIN::what() const noexcept
{
	return "Undefined user login";
}
const char* SMTP::Exception::UNDEF_PASSWORD::what() const noexcept
{
	return "Undefined user password";
}
const char* SMTP::Exception::BAD_SERVER_NAME::what() const noexcept
{
	return "Unable to determine server name for digest MD5 response";
}
const char* SMTP::Exception::INIT_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending INIT command";
}
const char* SMTP::Exception::MAIL_FROM_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending MAIL FROM command";
}
const char* SMTP::Exception::EHLO_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending EHLO command";
}
const char* SMTP::Exception::HELO_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending HELO command";
}
const char* SMTP::Exception::AUTH_PLAIN_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH PLAIN command";
}
const char* SMTP::Exception::AUTH_LOGIN_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH LOGIN command";
}
const char* SMTP::Exception::AUTH_CRAMMD5_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH CRAMMD5 command";
}
const char* SMTP::Exception::AUTH_DIGESTMD5_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH DIGESTMD5 command";
}
const char* SMTP::Exception::DIGESTMD5_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending MD5 DIGEST command";
}
const char* SMTP::Exception::DATA_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending DATA command";
}
const char* SMTP::Exception::QUIT_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending QUIT command";
}
const char* SMTP::Exception::RCPT_TO_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending RCPT TO command";
}
const char* SMTP::Exception::STARTTLS_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending STARTTLS command";
}
const char* SMTP::Exception::DATABLOCK_FAILED::what() const noexcept
{
	return "SMTP Failed to send data block";
}
const char* SMTP::Exception::MSG_BODY_ERROR::what() const noexcept
{
	return "SMTP Error in message body";
}
const char* SMTP::Exception::MSG_TOO_BIG::what() const noexcept
{
	return "SMTP letter cannot be more than 25 megabytes";
}
const char* SMTP::Exception::BAD_LOGIN_PASS::what() const noexcept
{
	return "SMTP Invalid password/login or access denied from insecure applications";
}
const char* SMTP::Exception::UNDEF_XYZ_RESPONSE::what() const noexcept
{
	return "SMTP Undefined xyz SMTP response";
}
const char* SMTP::Exception::TIME_ERROR::what() const noexcept
{
	return "SMTP time() error";
}
const char* SMTP::Exception::STARTTLS_NOT_SUPPORTED::what() const noexcept
{
	return "SMTP The STARTTLS command is not supported by the server";
}
const char* SMTP::Exception::AUTH_NOT_SUPPORTED::what() const noexcept
{
	return "SMTP AUTH LOGIN is not supported by the server";
}
const char* SMTP::Exception::STMP_CONNECT::what() const noexcept
{
	return "SMTP connect failed";
}
const char* SMTP::Exception::SMTP_COMM::what() const noexcept
{
	return "SMTP server return error";
}
const char* SMTP::Exception::SMTP_AUTH::what() const noexcept
{
	return "SMTP authentication failed";
}
const char* SMTP::Exception::SMTP_SEND_MAIL::what() const noexcept
{
	return "SMTP send mail failed";
}
const char* SMTP::Exception::SMTP_SEND::what() const noexcept
{
	return "SMTP send failed";
}
const char* SMTP::Exception::SMTP_SEND_DATA::what() const noexcept
{
	return "SMTP send data failed";
}
const char* SMTP::Exception::SMTP_RECV_DATA::what() const noexcept
{
	return "SMTP recv data failed";
}
const char* SMTP::Exception::SMTP_SEND_DATA_NOSEC::what() const noexcept
{
	return "SMTP send data with no secure failed";
}
const char* SMTP::Exception::SMTP_RECV_DATA_NOSEC::what() const noexcept
{
	return "SMTP recv data with no secure failed";
}
const char* SMTP::Exception::SMTP_SEND_DATA_SEC::what() const noexcept
{
	return "SMTP send data with secure failed";
}
const char* SMTP::Exception::SMTP_RECV_DATA_SEC::what() const noexcept
{
	return "SMTP recv data with secure failed";
}
const char* SMTP::Exception::SMTP_CREATE_HEADER::what() const noexcept
{
	return "SMTP create header failed";
}
const char* SMTP::Exception::SMTP_UNDEF_COMM::what() const noexcept
{
	return "SMTP undefined command specified";
}
const char* SMTP::Exception::EMAIL_SEND::what() const noexcept
{
	return "EMAIL send failed";
}
const char* SMTP::Exception::EMAIL_UNDEF_SENDER::what() const noexcept
{
	return "EMAIL undefined sender";
}
const char* SMTP::Exception::EMAIL_UNDEF_RECEIVER::what() const noexcept
{
	return "EMAIL undefined receiver";
}
