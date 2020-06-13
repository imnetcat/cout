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
		Requires(Server::ID id) : Server(supported.at(id)) {};
		static const std::map<Server::ID, Server>& GetSupported() noexcept;

		bool Auth() const noexcept;
		bool Extentions() const noexcept;
		bool Security() const noexcept;

	private:
		static const std::map<Server::ID, Server> supported;
	};
};
#endif