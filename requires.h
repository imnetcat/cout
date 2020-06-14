#pragma once
#ifndef _REQUIRES_H_
#define _REQUIRES_H_
#include "server.h"
#include <map>
namespace EMAIL
{
	class Requires : public Server
	{
	public:
		Requires() {};
		Requires(Server::ID id) : Server(supported.at(id)) {};
		Requires(Server server) : Server(server) {};

		static const std::map<Server::ID, Server>& GetSupported() noexcept;

		bool Auth() const noexcept;
		bool Extentions() const noexcept;
		bool Security() const noexcept;

	private:
		static const std::map<Server::ID, Server> supported;
	};
};
#endif