#include "raw.h"
#include "../core/except.h"
#include "../core/config.h"
using namespace std;
using namespace Protocol;

Raw::Raw() : Sockets() 
{
	DEBUG_LOG(3, "Initializing raw socks protocol");
}

void Raw::Connect(const std::string& host, unsigned short port)
{
	Sockets::Connect(host, port);
}

void Raw::Disconnect()
{
	Sockets::Disconnect();
}

void Raw::Send()
{
	if (!isConnected)
		Exception::CORE::connection_closed("before attempted to sending data");
	Sockets::Send(SendBuf);
	SendBuf.clear();
}

void Raw::Receive()
{
	if (!isConnected)
		Exception::CORE::connection_closed("before attempted to receive data");
	RecvBuf += Sockets::Receive();
}
