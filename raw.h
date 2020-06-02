#pragma once
#include "protocol.h"
#include "socket.h"

class Raw : public Protocol, protected Socket
{
public:
	Raw()
	{
		m_sLocalHostName = GetLocalName();
	}

	void Connect() override
	{
		if (hSocket == INVALID_SOCKET)
		{
			if (SocksConnect(server.name, server.port))
			{
				DEBUG_LOG(1, "Ошибка при соеденении");
				server.isConnected = false;
				Disconnect();
				throw FAIL(WSA_INVALID_SOCKET);
			}
		}
	}

	void Disconnect() override
	{
		Socket::Disconnect();
	}

	void Send() override
	{
		Socket::Input(SendBuf.c_str(), SendBuf.size());
		SendBuf.clear();
	}
	void Receive() override
	{
		RecvBuf += Socket::Output();
	}

protected:
	struct SERVER
	{
		bool isConnected = false;
		unsigned short port = 0;
		std::string name;
	};
	SERVER server;
	std::string m_sLocalHostName;
};
