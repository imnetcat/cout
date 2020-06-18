#include "except.h"
const char* Exception::CORE::invalid_argument::what() const noexcept
{
	return "Invalid argument or variable not specified";
}
const char* Exception::CORE::undefined::what() const noexcept
{
	return "Undefined error";
}
const char* Exception::CORE::lack_of_memory::what() const noexcept
{
	return "Lack of memory";
}
const char* Exception::CORE::out_of_range::what() const noexcept
{
	return "Out of range";
}
const char* Exception::CORE::logic_error::what() const noexcept
{
	return "Logic error";
}
const char* Exception::CORE::file_not_exist::what() const noexcept
{
	return "File not exist";
}
const char* Exception::CORE::wsa_startup::what() const noexcept
{
	return "WSA startup failed";
}
const char* Exception::CORE::wsa_version::what() const noexcept
{
	return "Invalid WSA version";
}
const char* Exception::CORE::wsa_send::what() const noexcept
{
	return "WSA send error";
}
const char* Exception::CORE::wsa_recv::what() const noexcept
{
	return "WSA recv error";
}
const char* Exception::CORE::wsa_connect::what() const noexcept
{
	return "WSA connect";
}
const char* Exception::CORE::wsa_gethostby_name_addr::what() const noexcept
{
	return "WSA gethost by name\addr failed";
}
const char* Exception::CORE::wsa_invalid_socket::what() const noexcept
{
	return "WSA invalid socket";
}
const char* Exception::CORE::wsa_hostname::what() const noexcept
{
	return "WSA invalid hostname";
}
const char* Exception::CORE::wsa_ioctlsocket::what() const noexcept
{
	return "WSA ioctlsocket filed";
}
const char* Exception::CORE::bad_ipv4_addr::what() const noexcept
{
	return "bad ipv4 addr";
}
const char* Exception::CORE::select_timeout::what() const noexcept
{
	return "WSA select timeout";
}
const char* Exception::CORE::wsa_select::what() const noexcept
{
	return "WSA select failed";
}
const char* Exception::CORE::server_not_responding::what() const noexcept
{
	return "Server not responding";
}
const char* Exception::CORE::already_connect::what() const noexcept
{
	return "Connection already exist";
}
const char* Exception::CORE::connect_failed::what() const noexcept
{
	return "Failed connect to server";
}
const char* Exception::CORE::connection_closed::what() const noexcept
{
	return "Connection closed";
}
const char* Exception::CORE::sendbuf_is_empty::what() const noexcept
{
	return "Send buffer is empty";
}
const char* Exception::CORE::recvbuf_is_empty::what() const noexcept
{
	return "Recv buffer is empty";
}
const char* Exception::CORE::openssl_problem::what() const noexcept
{
	return "OpenSSL error";
}
const char* Exception::CORE::BAD_LOGIN_PASSWORD::what() const noexcept
{
	return "Invalid user login or password";
}
const char* Exception::CORE::BAD_DIGEST_RESPONSE::what() const noexcept
{
	return "Server returned a bad digest MD5 response";
}