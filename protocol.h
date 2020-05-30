#pragma once

#include <string>

class Protocol
{
public:
	virtual void Connect() = 0;
	virtual void Disconnect() = 0;
	virtual void Send(const std::string& data, int timeout) = 0;
	virtual std::string Receive(int timeout) = 0;
};
