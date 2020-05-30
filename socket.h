#pragma once
#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "core.h"
#include "protocol.h"

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define TIME_IN_SEC		3*60	// how long client will wait for server response in non-blocking mode
#define BUFFER_SIZE		10240	// sockets buffers sizes

class Socket : Protocol
{
public:

	Socket();

	~Socket();
	
	void Disconnect() override;

	void Connect() override;

	virtual void Send(const string& data, int send_timeout) override;

	virtual string Receive(int recv_timeout) override;

private:
	
	RETCODE SocksConnect();

protected:
	
	struct SERVER
	{
		bool isConnected = false;
		unsigned short port = 0;
		std::string name;
	};
	SERVER server;
	SOCKET hSocket;
	std::string m_sLocalHostName;
};

#endif