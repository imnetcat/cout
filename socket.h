#pragma once
#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "core.h"

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define TIME_IN_SEC		3*60	// how long client will wait for server response in non-blocking mode
#define BUFFER_SIZE		10240	// sockets buffers sizes

class Socket
{
public:

	Socket();

	~Socket();
	
	void Disconnect();

	RETCODE Connect();

	virtual RETCODE SendData(const string& data, int send_timeout);

	virtual string ReceiveData(int recv_timeout);

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