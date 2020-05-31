#pragma once
#include <string>

class Protocol
{
public:
	virtual void Connect() = 0;
	virtual void Disconnect() = 0;
	virtual void Send() = 0;
	virtual void Receive() = 0;
protected:
	std::string SendBuf;
	std::string RecvBuf;
};
