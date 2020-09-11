#include "server.h"
Cout::Network::Protocol::SMTP::Server::Server() : sec(),
	host(""),
	port(0) {};

Cout::Network::Protocol::SMTP::Server::Server(Secured::Type s, const char* h, unsigned short p)
	: sec(s), host(h), port(p) {};

inline const std::string Cout::Network::Protocol::SMTP::Server::GetSecurity() const noexcept
{
	return sec == Secured::Type::SSL ? "ssl" : "tls";
}
