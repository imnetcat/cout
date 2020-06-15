#pragma once
#ifndef _SOCKET_H_
#define _SOCKET_H_
#include "protocol.h"

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <string>

class Raw : public Protocol
{
public:
	Raw();
	~Raw();
	void Connect(const std::string& host, unsigned short port) override;
	void Disconnect() override;
	void Send() override;
	void Receive() override;
protected:
	static const int BUFFER_SIZE = 10240;
	static const int TIMEOUT = 3 * 60;
	std::string GetLocalName() const;
	SOCKET hSocket;
};

#endif