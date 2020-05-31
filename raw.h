#pragma once
#include "protocol.h"
#include "socket.h"

class Raw : public Protocol, private Socket
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
			if (SocksConnect())
			{
				DEBUG_LOG(1, "Ошибка при соеденении");
				server.isConnected = false;
				Disconnect();
				throw FAIL(WSA_INVALID_SOCKET);
			}
		}
	}

	virtual void Disconnect() = 0;
	virtual void Send() = 0;
	virtual void Receive() = 0;

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
