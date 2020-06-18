#include"exceptions.h"
const char* Exception::SMTP::command_not_recognized::what() const noexcept
{
	return "Command not recognized";
}
const char* Exception::SMTP::UNDEF_MSG_HEADER::what() const noexcept
{
	return "Undefined message header";
}
const char* Exception::SMTP::UNDEF_MAIL_FROM::what() const noexcept
{
	return "Undefined mail sender";
}
const char* Exception::SMTP::UNDEF_SUBJECT::what() const noexcept
{
	return "Undefined message subject";
}
const char* Exception::SMTP::UNDEF_RECIPIENTS::what() const noexcept
{
	return "Undefined at least one reciepent";
}
const char* Exception::SMTP::UNDEF_RECIPIENT_MAIL::what() const noexcept
{
	return "Undefined recipent mail";
}
const char* Exception::SMTP::UNDEF_LOGIN::what() const noexcept
{
	return "Undefined user login";
}
const char* Exception::SMTP::UNDEF_PASSWORD::what() const noexcept
{
	return "Undefined user password";
}
const char* Exception::SMTP::BAD_SERVER_NAME::what() const noexcept
{
	return "Unable to determine server name for digest MD5 response";
}
const char* Exception::SMTP::INIT_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending INIT command";
}
const char* Exception::SMTP::MAIL_FROM_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending MAIL FROM command";
}
const char* Exception::SMTP::EHLO_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending EHLO command";
}
const char* Exception::SMTP::HELO_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending HELO command";
}
const char* Exception::SMTP::AUTH_PLAIN_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH PLAIN command";
}
const char* Exception::SMTP::AUTH_LOGIN_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH LOGIN command";
}
const char* Exception::SMTP::AUTH_CRAMMD5_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH CRAMMD5 command";
}
const char* Exception::SMTP::AUTH_DIGESTMD5_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending AUTH DIGESTMD5 command";
}
const char* Exception::SMTP::DIGESTMD5_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending MD5 DIGEST command";
}
const char* Exception::SMTP::DATA_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending DATA command";
}
const char* Exception::SMTP::QUIT_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending QUIT command";
}
const char* Exception::SMTP::RCPT_TO_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending RCPT TO command";
}
const char* Exception::SMTP::STARTTLS_FAILED::what() const noexcept
{
	return "SMTP Server returned error after sending STARTTLS command";
}
const char* Exception::SMTP::DATABLOCK_FAILED::what() const noexcept
{
	return "SMTP Failed to send data block";
}
const char* Exception::SMTP::MSG_BODY_ERROR::what() const noexcept
{
	return "SMTP Error in message body";
}
const char* Exception::SMTP::MSG_TOO_BIG::what() const noexcept
{
	return "SMTP letter cannot be more than 25 megabytes";
}
const char* Exception::SMTP::BAD_LOGIN_PASS::what() const noexcept
{
	return "SMTP Invalid password/login or access denied from insecure applications";
}
const char* Exception::SMTP::UNDEF_XYZ_RESPONSE::what() const noexcept
{
	return "SMTP Undefined xyz SMTP response";
}
const char* Exception::SMTP::TIME_ERROR::what() const noexcept
{
	return "SMTP time() error";
}
const char* Exception::SMTP::STARTTLS_NOT_SUPPORTED::what() const noexcept
{
	return "SMTP The STARTTLS command is not supported by the server";
}
const char* Exception::SMTP::AUTH_NOT_SUPPORTED::what() const noexcept
{
	return "SMTP AUTH LOGIN is not supported by the server";
}
const char* Exception::SMTP::STMP_CONNECT::what() const noexcept
{
	return "SMTP connect failed";
}
const char* Exception::SMTP::SMTP_COMM::what() const noexcept
{
	return "SMTP server return error";
}
const char* Exception::SMTP::SMTP_AUTH::what() const noexcept
{
	return "SMTP authentication failed";
}
const char* Exception::SMTP::SMTP_SEND_MAIL::what() const noexcept
{
	return "SMTP send mail failed";
}
const char* Exception::SMTP::SMTP_SEND::what() const noexcept
{
	return "SMTP send failed";
}
const char* Exception::SMTP::SMTP_SEND_DATA::what() const noexcept
{
	return "SMTP send data failed";
}
const char* Exception::SMTP::SMTP_RECV_DATA::what() const noexcept
{
	return "SMTP recv data failed";
}
const char* Exception::SMTP::SMTP_SEND_DATA_NOSEC::what() const noexcept
{
	return "SMTP send data with no secure failed";
}
const char* Exception::SMTP::SMTP_RECV_DATA_NOSEC::what() const noexcept
{
	return "SMTP recv data with no secure failed";
}
const char* Exception::SMTP::SMTP_SEND_DATA_SEC::what() const noexcept
{
	return "SMTP send data with secure failed";
}
const char* Exception::SMTP::SMTP_RECV_DATA_SEC::what() const noexcept
{
	return "SMTP recv data with secure failed";
}
const char* Exception::SMTP::SMTP_CREATE_HEADER::what() const noexcept
{
	return "SMTP create header failed";
}
const char* Exception::SMTP::SMTP_UNDEF_COMM::what() const noexcept
{
	return "SMTP undefined command specified";
}
const char* Exception::SMTP::EMAIL_SEND::what() const noexcept
{
	return "EMAIL send failed";
}
const char* Exception::SMTP::EMAIL_UNDEF_SENDER::what() const noexcept
{
	return "EMAIL undefined sender";
}
const char* Exception::SMTP::EMAIL_UNDEF_RECEIVER::what() const noexcept
{
	return "EMAIL undefined receiver";
}
