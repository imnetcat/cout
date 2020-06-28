#pragma once
#ifndef _SOCKETS_H_
#define _SOCKETS_H_

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <string>

class Sockets
{
public:
	Sockets();
	~Sockets();
	void Connect(const std::string& host, unsigned short port);
	void Disconnect();
	void Send(const std::string&);
	std::string Receive();
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

#endif