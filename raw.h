#pragma once
#ifndef _RAW_H_
#define _RAW_H_
#include "protocol.h"
#include "socket.h"

class Raw : public Protocol, protected Socket
{
public:
	Raw();
	void Connect() override;
	void Disconnect() override;
	void Send() override;
	void Receive() override;
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

#endif