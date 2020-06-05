#include "raw.h"

Raw::Raw() : m_sLocalHostName(GetLocalName()) { }

void Raw::Connect()
{
	if (hSocket == INVALID_SOCKET)
	{
		try
		{
			SocksConnect(server.name, server.port);
		}
		catch(...)
		{
			DEBUG_LOG(1, "Ошибка при соеденении");
			server.isConnected = false;
			Disconnect();
			throw FAIL(WSA_INVALID_SOCKET);
		}
	}
}

void Raw::Disconnect()
{
	Socket::Disconnect();
}

void Raw::Send()
{
	Socket::Input(SendBuf.c_str(), SendBuf.size());
	SendBuf.clear();
}
void Raw::Receive()
{
	RecvBuf += Socket::Output();
}