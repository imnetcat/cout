#pragma once

#ifndef WINAPI
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#endif

#pragma comment(lib, "ws2_32.lib")

#include <string>
#include "../core/types/binary.h"

class Sockets
{
public:
	Sockets();
	~Sockets();
	void Connect(const std::string& host, unsigned short port);
	void Disconnect();
	void Send(const Binary&);
	Binary Receive();
protected:
	enum type
	{
		tcp = SOCK_STREAM,
		udp = SOCK_DGRAM,
		raw = SOCK_RAW
	};
	enum address_family
	{
		inet = AF_INET,
		local = AF_UNIX
	};
	bool isConnected;
	static const int BUFFER_SIZE = 10240;
	static const int TIMEOUT = 3 * 60;
	std::string GetLocalName() const;
	SOCKET hSocket;
};
