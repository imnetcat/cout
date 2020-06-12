#include "except.h"
const char* CORE::Exception::invalid_argument::what() const noexcept
{
	return "Invalid argument or variable not specified";
}
const char* CORE::Exception::undefined::what() const noexcept
{
	return "Undefined error";
}
const char* CORE::Exception::out_of_range::what() const noexcept
{
	return "Out of range";
}
const char* CORE::Exception::logic_error::what() const noexcept
{
	return "Logic error";
}
const char* CORE::Exception::file_not_exist::what() const noexcept
{
	return "File not exist";
}
const char* CORE::Exception::wsa_startup::what() const noexcept
{
	return "WSA startup failed";
}
const char* CORE::Exception::wsa_version::what() const noexcept
{
	return "Invalid WSA version";
}
const char* CORE::Exception::wsa_send::what() const noexcept
{
	return "WSA send error";
}
const char* CORE::Exception::wsa_recv::what() const noexcept
{
	return "WSA recv error";
}
const char* CORE::Exception::wsa_connect::what() const noexcept
{
	return "WSA connect";
}
const char* CORE::Exception::wsa_gethostby_name_addr::what() const noexcept
{
	return "WSA gethost by name\addr failed";
}
const char* CORE::Exception::wsa_invalid_socket::what() const noexcept
{
	return "WSA invalid socket";
}
const char* CORE::Exception::wsa_hostname::what() const noexcept
{
	return "WSA invalid hostname";
}
const char* CORE::Exception::wsa_ioctlsocket::what() const noexcept
{
	return "WSA ioctlsocket filed";
}
const char* CORE::Exception::bad_ipv4_addr::what() const noexcept
{
	return "bad ipv4 addr";
}
const char* CORE::Exception::select_timeout::what() const noexcept
{
	return "WSA select timeout";
}
const char* CORE::Exception::wsa_select::what() const noexcept
{
	return "WSA select failed";
}
const char* CORE::Exception::server_not_responding::what() const noexcept
{
	return "Server not responding";
}
const char* CORE::Exception::already_connect::what() const noexcept
{
	return "Connection already exist";
}
const char* CORE::Exception::connect_failed::what() const noexcept
{
	return "Failed connect to server";
}
const char* CORE::Exception::connection_closed::what() const noexcept
{
	return "Connection closed";
}
const char* CORE::Exception::sendbuf_is_empty::what() const noexcept
{
	return "Send buffer is empty";
}
const char* CORE::Exception::recvbuf_is_empty::what() const noexcept
{
	return "Recv buffer is empty";
}
const char* CORE::Exception::openssl_problem::what() const noexcept
{
	return "OpenSSL error";
}
const char* CORE::Exception::BAD_LOGIN_PASSWORD::what() const noexcept
{
	return "Invalid user login or password";
}
const char* CORE::Exception::BAD_DIGEST_RESPONSE::what() const noexcept
{
	return "Server returned a bad digest MD5 response";
}