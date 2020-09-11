#include "raw.h"
#include "exception.h"
#include "../../core/logging/debug_logger.h"
using namespace std;
using namespace Cout::Network::Protocol;

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
		Exceptions::wsa::connection_closed(WHERE, "before attempted to sending data");
	Sockets::Send(SendBuf);
	SendBuf.clear();
}

void Raw::Receive()
{
	if (!isConnected)
		Exceptions::wsa::connection_closed(WHERE, "before attempted to receive data");
	RecvBuf = Sockets::Receive();
}