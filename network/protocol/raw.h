#pragma once
#ifndef _SOCKET_H_
#define _SOCKET_H_
#include "interface.h"
#include "sockets.h"
namespace Protocol
{
	class Raw : public Sockets, public Interface
	{
	public:
		Raw();
		virtual ~Raw()
		{
			if (isConnected)
				Disconnect();
		}
		void Connect(const std::string& host, unsigned short port) override;
		void Disconnect() override;
		void Send() override;
		void Receive() override;
	};
}
#endif