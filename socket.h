#pragma once
#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "core.h"

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

constexpr int BUFFER_SIZE = 10240;
constexpr int TIMEOUT = 3 * 60;

class Socket
{
public:

	Socket();

	~Socket();
	
	void Disconnect();

	void Input(const char* data, size_t size);

	const char* Output();

private:
	
protected:
	string GetLocalName();
	RETCODE SocksConnect(string szServer, const unsigned short nPort_);
	SOCKET hSocket;
};

#endif