#include "raw.h"
#include "exception.h"
#include "../../core/logging/debug_logger.h"

Cout::Network::Protocol::Raw::Raw() : Sockets()
{
	DEBUG_LOG(3, "Initializing raw socks protocol");
}

void Cout::Network::Protocol::Raw::Connect(const std::string& host, unsigned short port)
{
	Sockets::Connect(host, port);
}

void Cout::Network::Protocol::Raw::Disconnect()
{
	Sockets::Disconnect();
}

void Cout::Network::Protocol::Raw::Send()
{
	if (!isConnected)
		Exceptions::wsa::connection_closed(WHERE, "before attempted to sending data");
	Sockets::Send(SendBuf);
	SendBuf.clear();
}

void Cout::Network::Protocol::Raw::Receive()
{
	if (!isConnected)
		Exceptions::wsa::connection_closed(WHERE, "before attempted to receive data");
	RecvBuf = Sockets::Receive();
}
