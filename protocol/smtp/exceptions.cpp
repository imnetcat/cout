#include"exceptions.h"
const char* Exceptions::SMTP::command_not_recognized::what() const noexcept
{
	return "Command not recognized";
}
const char* Exceptions::SMTP::UNDEF_MSG_HEADER::what() const noexcept
{
	return "Undefined message header";
}
const char* Exceptions::SMTP::UNDEF_MAIL_FROM::what() const noexcept
{
	return "Undefined mail sender";
}
const char* Exceptions::SMTP::UNDEF_SUBJECT::what() const noexcept
{
	return "Undefined message subject";
}
const char* Exceptions::SMTP::UNDEF_RECIPIENTS::what() const noexcept
{
	return "Undefined at least one reciepent";
}
const char* Exceptions::SMTP::UNDEF_RECIPIENT_MAIL::what() const noexcept
{
	return "Undefined recipent mail";
}
const char* Exceptions::SMTP::UNDEF_LOGIN::what() const noexcept
{
	return "Undefined user login";
}
const char* Exceptions::SMTP::UNDEF_PASSWORD::what() const noexcept
{
	return "Undefined user password";
}
const char* Exceptions::SMTP::BAD_SERVER_NAME::what() const noexcept
{
	return "Unable to determine server name for digest MD5 response";
}
const char* Exceptions::SMTP::INIT_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending INIT command";
}
const char* Exceptions::SMTP::MAIL_FROM_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending MAIL FROM command";
}
const char* Exceptions::SMTP::EHLO_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending EHLO command";
}
const char* Exceptions::SMTP::HELO_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending HELO command";
}
const char* Exceptions::SMTP::AUTH_PLAIN_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH PLAIN command";
}
const char* Exceptions::SMTP::AUTH_LOGIN_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH LOGIN command";
}
const char* Exceptions::SMTP::AUTH_CRAMMD5_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH CRAMMD5 command";
}
const char* Exceptions::SMTP::AUTH_DIGESTMD5_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH DIGESTMD5 command";
}
const char* Exceptions::SMTP::DIGESTMD5_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending MD5 DIGEST command";
}
const char* Exceptions::SMTP::DATA_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending DATA command";
}
const char* Exceptions::SMTP::QUIT_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending QUIT command";
}
const char* Exceptions::SMTP::RCPT_TO_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending RCPT TO command";
}
const char* Exceptions::SMTP::STARTTLS_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending STARTTLS command";
}
const char* Exceptions::SMTP::DATABLOCK_FAILED::what() const noexcept
{
	return "SMTP Failed to send data block";
}
const char* Exceptions::SMTP::MSG_BODY_ERROR::what() const noexcept
{
	return "SMTP Error in message body";
}
const char* Exceptions::SMTP::MSG_TOO_BIG::what() const noexcept
{
	return "SMTP letter cannot be more than 25 megabytes";
}
const char* Exceptions::SMTP::BAD_LOGIN_PASS::what() const noexcept
{
	return "SMTP Invalid password/login or access denied from insecure applications";
}
const char* Exceptions::SMTP::UNDEF_XYZ_RESPONSE::what() const noexcept
{
	return "SMTP Undefined xyz SMTP response";
}
const char* Exceptions::SMTP::TIME_ERROR::what() const noexcept
{
	return "SMTP time() error";
}
const char* Exceptions::SMTP::STARTTLS_NOT_SUPPORTED::what() const noexcept
{
	return "SMTP The STARTTLS command is not supported by the server";
}
const char* Exceptions::SMTP::AUTH_NOT_SUPPORTED::what() const noexcept
{
	return "SMTP AUTH LOGIN is not supported by the server";
}
const char* Exceptions::SMTP::STMP_CONNECT::what() const noexcept
{
	return "SMTP connect failed";
}
const char* Exceptions::SMTP::SMTP_COMM::what() const noexcept
{
	return "SMTP server return error";
}
const char* Exceptions::SMTP::SMTP_AUTH::what() const noexcept
{
	return "SMTP authentication failed";
}
const char* Exceptions::SMTP::SMTP_SEND_MAIL::what() const noexcept
{
	return "SMTP send mail failed";
}
const char* Exceptions::SMTP::SMTP_SEND::what() const noexcept
{
	return "SMTP send failed";
}
const char* Exceptions::SMTP::SMTP_SEND_DATA::what() const noexcept
{
	return "SMTP send data failed";
}
const char* Exceptions::SMTP::SMTP_RECV_DATA::what() const noexcept
{
	return "SMTP recv data failed";
}
const char* Exceptions::SMTP::SMTP_SEND_DATA_NOSEC::what() const noexcept
{
	return "SMTP send data with no secure failed";
}
const char* Exceptions::SMTP::SMTP_RECV_DATA_NOSEC::what() const noexcept
{
	return "SMTP recv data with no secure failed";
}
const char* Exceptions::SMTP::SMTP_SEND_DATA_SEC::what() const noexcept
{
	return "SMTP send data with secure failed";
}
const char* Exceptions::SMTP::SMTP_RECV_DATA_SEC::what() const noexcept
{
	return "SMTP recv data with secure failed";
}
const char* Exceptions::SMTP::SMTP_CREATE_HEADER::what() const noexcept
{
	return "SMTP create header failed";
}
const char* Exceptions::SMTP::SMTP_UNDEF_COMM::what() const noexcept
{
	return "SMTP undefined command specified";
}
const char* Exceptions::SMTP::EMAIL_SEND::what() const noexcept
{
	return "EMAIL send failed";
}
const char* Exceptions::SMTP::EMAIL_UNDEF_SENDER::what() const noexcept
{
	return "EMAIL undefined sender";
}
const char* Exceptions::SMTP::EMAIL_UNDEF_RECEIVER::what() const noexcept
{
	return "EMAIL undefined receiver";
}
