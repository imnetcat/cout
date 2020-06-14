#pragma once
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_
#include <string>

class Protocol
{
public:
	virtual void Connect(const std::string& host, unsigned short port) = 0;
	virtual void Disconnect() = 0;
	virtual void Send() = 0;
	virtual void Receive() = 0;
protected:
	bool isConnected;
	std::string host;
	unsigned short port;

	std::string SendBuf;
	std::string RecvBuf;
};

#endif