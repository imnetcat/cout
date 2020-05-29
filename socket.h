#pragma once
#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "core.h"

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define TIME_IN_SEC		3*60	// how long client will wait for server response in non-blocking mode
#define BUFFER_SIZE		10240	// SendData and RecvData buffers sizes

class Socket
{
public:

	Socket();

	~Socket();

	RETCODE SocksConnect();

	void Disconnect();

	RETCODE Connect();

	RETCODE SendData_NoSec(int send_timeout);

	RETCODE ReceiveData_NoSec(int recv_timeout);

protected:

	struct SERVER
	{
		bool isConnected = false;
		unsigned short port = 0;
		std::string name;
	};
	SERVER server;
	std::string SendBuf;
	std::string RecvBuf;
	SOCKET hSocket;
	std::string m_sLocalHostName;
};

#endif