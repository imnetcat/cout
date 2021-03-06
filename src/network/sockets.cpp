#include "sockets.h"
#include "../core/logging/debug_logger.h"
#include "protocol/exception.h"

Cout::Network::Sockets::Sockets() : hSocket(INVALID_SOCKET), isConnected(false)
{
	DEBUG_LOG(3, "Initializing WinSocksAPI");
	WSADATA wsaData;
	WORD wVer = MAKEWORD(2, 2);
	if (WSAStartup(wVer, &wsaData) != NO_ERROR)
		throw Cout::Network::Protocol::Exceptions::wsa::startup(WHERE, "WSA initializating");

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		throw Cout::Network::Protocol::Exceptions::wsa::version(WHERE, "WSA initializating");;
	}
}

Cout::Network::Sockets::~Sockets()
{
	WSACleanup();
}

std::string Cout::Network::Sockets::GetLocalName() const
{
	char hostname[255];
	if (gethostname((char *)&hostname, 255) == SOCKET_ERROR)
		throw Cout::Network::Protocol::Exceptions::wsa::hostname(WHERE, "get local hostname");;
	return hostname;
}

void Cout::Network::Sockets::Connect(const std::string& host, unsigned short port)
{
	if (hSocket != INVALID_SOCKET)
		throw Cout::Network::Protocol::Exceptions::wsa::already_connect(WHERE, "connect failed");
	DEBUG_LOG(3, "Sockets connect");

	unsigned short nPort = 0;
	LPSERVENT lpServEnt;
	SOCKADDR_IN sockAddr;
	unsigned long ul = 1;
	fd_set fdwrite, fdexcept;
	timeval timeout;
	int res = 0;

	timeout.tv_sec = TIMEOUT;
	timeout.tv_usec = 0;

	hSocket = INVALID_SOCKET;

	DEBUG_LOG(3, "Creating new socket");
	if ((hSocket = socket(address_family::inet, type::tcp, 0)) == INVALID_SOCKET)
		throw Cout::Network::Protocol::Exceptions::wsa::invalid_socket(WHERE, "connecting on sockets");

	DEBUG_LOG(3, "Convert the byte representation of a port to the network byte order");
	if (port != 0)
		nPort = htons(port);
	else
	{
		lpServEnt = getservbyname("mail", 0);
		if (lpServEnt == NULL)
			nPort = htons(25);
		else
			nPort = lpServEnt->s_port;
	}

	DEBUG_LOG(3, "Fill the server structure");
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = nPort;
	if ((sockAddr.sin_addr.s_addr = inet_addr(host.c_str())) == INADDR_NONE)
	{
		LPHOSTENT hostent;

		hostent = gethostbyname(host.c_str());
		if (hostent)
			memcpy(&sockAddr.sin_addr, hostent->h_addr_list[0], hostent->h_length);
		else
		{
			closesocket(hSocket);
			throw Cout::Network::Protocol::Exceptions::wsa::gethostby_name_addr(WHERE, "connecting on sockets");
		}
	}

	DEBUG_LOG(3, "Set the socket to non-blocking mode");
	if (ioctlsocket(hSocket, FIONBIO, (unsigned long*)&ul) == SOCKET_ERROR)
	{
		closesocket(hSocket);
		throw Cout::Network::Protocol::Exceptions::wsa::ioctlsocket(WHERE, "connecting on sockets");
	}

	DEBUG_LOG(3, "Connect to the server");
	if (connect(hSocket, (LPSOCKADDR)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			closesocket(hSocket);
			throw Cout::Network::Protocol::Exceptions::wsa::connect(WHERE, "connecting on sockets");
		}
	}

	DEBUG_LOG(3, "Check connection");
	while (true)
	{
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdexcept);

		FD_SET(hSocket, &fdwrite);
		FD_SET(hSocket, &fdexcept);

		if ((res = select(static_cast<int>(hSocket) + 1, NULL, &fdwrite, &fdexcept, &timeout)) == SOCKET_ERROR)
		{
			closesocket(hSocket);
			throw Cout::Network::Protocol::Exceptions::wsa::select(WHERE, "selecting sockets");;
		}

		if (!res)
		{
			closesocket(hSocket);
			throw Cout::Network::Protocol::Exceptions::wsa::select_timeout(WHERE, "connecting on sockets");
		}
		if (res && FD_ISSET(hSocket, &fdwrite))
			break;
		if (res && FD_ISSET(hSocket, &fdexcept))
		{
			closesocket(hSocket);
			throw Cout::Network::Protocol::Exceptions::wsa::select(WHERE, "connecting on sockets");
		}
	} // while

	FD_CLR(hSocket, &fdwrite);
	FD_CLR(hSocket, &fdexcept);

	isConnected = true;
	DEBUG_LOG(3, "Connection with server successfully established");
}

void Cout::Network::Sockets::Disconnect()
{
	DEBUG_LOG(3, "Sockets disconnected");
	if (hSocket)
	{
		closesocket(hSocket);
	}
	isConnected = false;
	hSocket = INVALID_SOCKET;
}

#include <iostream>
void Cout::Network::Sockets::Send(const Cout::Binary& SendBuf)
{
	int res;
	fd_set fdwrite;
	timeval time;

	time.tv_sec = TIMEOUT;
	time.tv_usec = 0;

	if (!SendBuf.size())
		throw Cout::Network::Protocol::Exceptions::wsa::sendbuf_is_empty(WHERE, "send by sockets");

	if (hSocket == INVALID_SOCKET)
		throw Cout::Network::Protocol::Exceptions::wsa::connection_closed(WHERE, "send by sockets");

	FD_ZERO(&fdwrite);

	FD_SET(hSocket, &fdwrite);

	if ((res = select(static_cast<int>(hSocket) + 1, NULL, &fdwrite, NULL, &time)) == SOCKET_ERROR)
	{
		FD_CLR(hSocket, &fdwrite);
		throw Cout::Network::Protocol::Exceptions::wsa::select(WHERE, "send by sockets");
	}

	if (!res)
	{
		//timeout
		FD_CLR(hSocket, &fdwrite);
		throw Cout::Network::Protocol::Exceptions::wsa::server_not_responding(WHERE, "send by sockets");
	}

	if (res && FD_ISSET(hSocket, &fdwrite))
	{
		res = send(hSocket, SendBuf.data(), static_cast<int>(SendBuf.size()), 0);
		if (res == SOCKET_ERROR || res == 0)
		{
			FD_CLR(hSocket, &fdwrite);
			throw Cout::Network::Protocol::Exceptions::wsa::send(WHERE, "send by sockets");
		}
	}

	FD_CLR(hSocket, &fdwrite);
}

Cout::Binary Cout::Network::Sockets::Receive()
{
	DEBUG_LOG(3, "Receiving data using sockets");
	SignedByte buffer[BUFFER_SIZE];
	std::string RecvBuf;
	int res = 0;
	fd_set fdread;
	timeval time;

	time.tv_sec = TIMEOUT;
	time.tv_usec = 0;

	FD_ZERO(&fdread);

	FD_SET(hSocket, &fdread);

	if ((res = select(static_cast<int>(hSocket) + 1, &fdread, NULL, NULL, &time)) == SOCKET_ERROR)
	{
		FD_CLR(hSocket, &fdread);
		throw Cout::Network::Protocol::Exceptions::wsa::select(WHERE, "sockets select");
	}

	if (!res)
	{
		//timeout
		FD_CLR(hSocket, &fdread);
		throw Cout::Network::Protocol::Exceptions::wsa::server_not_responding(WHERE, "sockets select");
	}

	if (FD_ISSET(hSocket, &fdread))
	{
		res = recv(hSocket, buffer, BUFFER_SIZE, 0);
		if (res == SOCKET_ERROR)
		{
			FD_CLR(hSocket, &fdread);
			throw Cout::Network::Protocol::Exceptions::wsa::recv(WHERE, "receiving data over sockets failed");
		}
	}

	FD_CLR(hSocket, &fdread);
	if (res == 0)
	{
		isConnected = false;
		throw Cout::Network::Protocol::Exceptions::wsa::connection_closed(WHERE, "receiving data over sockets");
	}

	return { buffer, static_cast<size_t>(res) };
}
