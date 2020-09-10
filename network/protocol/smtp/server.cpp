#include "server.h"

Protocol::SMTP::Server::Server() : sec(),
	host(""),
	port(0) {};

Protocol::SMTP::Server::Server(Secured::Type s, const char* h, unsigned short p)
	: sec(s), host(h), port(p) {};

inline const std::string Protocol::SMTP::Server::GetSecurity() const noexcept
{
	return sec == Secured::Type::SSL ? "ssl" : "tls";
}
