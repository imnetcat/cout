#pragma once
#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "core.h"

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class Socket
{
public:

	Socket();

	~Socket();
	
	void Disconnect();

	void Input(const char* data, size_t size);

	const char* Output();
protected:

	static const int BUFFER_SIZE = 10240;
	static const int TIMEOUT = 3 * 60;

	std::string GetLocalName();
	RETCODE SocksConnect(std::string szServer, const unsigned short nPort_);
	SOCKET hSocket;
private:
	char OutputBuf[BUFFER_SIZE];
};

#endif