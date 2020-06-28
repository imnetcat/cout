#include "sockets.h"
#include "../core/config.h"
#include "../core/except.h"
using namespace std;

Sockets::Sockets() : hSocket(INVALID_SOCKET), isConnected(false)
{
	DEBUG_LOG(3, "Initializing WinSocksAPI");
	WSADATA wsaData;
	WORD wVer = MAKEWORD(2, 2);
	if (WSAStartup(wVer, &wsaData) != NO_ERROR)
		throw Exception::CORE::wsa_startup("WSA initializating");

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		throw Exception::CORE::wsa_version("WSA initializating");;
	}
}

Sockets::~Sockets()
{
	WSACleanup();
}

string Sockets::GetLocalName() const
{
	char hostname[255];
	if (gethostname((char *)&hostname, 255) == SOCKET_ERROR)
		throw Exception::CORE::wsa_hostname("get local hostname");;
	return hostname;
}

void Sockets::Connect(const std::string& host, unsigned short port)
{
	if (hSocket != INVALID_SOCKET)
		throw Exception::CORE::already_connect("connect failed");
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
		throw Exception::CORE::wsa_invalid_socket("connecting on sockets");

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
			throw Exception::CORE::wsa_gethostby_name_addr("connecting on sockets");
		}
	}

	DEBUG_LOG(3, "Set the socket to non-blocking mode");
	if (ioctlsocket(hSocket, FIONBIO, (unsigned long*)&ul) == SOCKET_ERROR)
	{
		closesocket(hSocket);
		throw Exception::CORE::wsa_ioctlsocket("connecting on sockets");;
	}

	DEBUG_LOG(3, "Connect to the server");
	if (connect(hSocket, (LPSOCKADDR)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			closesocket(hSocket);
			throw Exception::CORE::wsa_connect("connecting on sockets");;
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
			throw Exception::CORE::wsa_select("selecting sockets");;
		}

		if (!res)
		{
			closesocket(hSocket);
			throw Exception::CORE::select_timeout("connecting on sockets");;
		}
		if (res && FD_ISSET(hSocket, &fdwrite))
			break;
		if (res && FD_ISSET(hSocket, &fdexcept))
		{
			closesocket(hSocket);
			throw Exception::CORE::wsa_select("connecting on sockets");;
		}
	} // while

	FD_CLR(hSocket, &fdwrite);
	FD_CLR(hSocket, &fdexcept);

	isConnected = true;
	DEBUG_LOG(3, "Connection with server successfully established");
}

void Sockets::Disconnect()
{
	DEBUG_LOG(3, "Sockets disconnected");
	if (hSocket)
	{
		closesocket(hSocket);
	}
	isConnected = false;
	hSocket = INVALID_SOCKET;
}

void Sockets::Send(const string& SendBuf)
{
	DEBUG_LOG(3, "Sending data using sockets");
	int res;
	fd_set fdwrite;
	timeval time;

	time.tv_sec = TIMEOUT;
	time.tv_usec = 0;

	if (SendBuf.size())
		throw Exception::CORE::sendbuf_is_empty("send by sockets");

	FD_ZERO(&fdwrite);

	FD_SET(hSocket, &fdwrite);

	if ((res = select(static_cast<int>(hSocket) + 1, NULL, &fdwrite, NULL, &time)) == SOCKET_ERROR)
	{
		FD_CLR(hSocket, &fdwrite);
		throw Exception::CORE::wsa_select("send by sockets");
	}

	if (!res)
	{
		//timeout
		FD_CLR(hSocket, &fdwrite);
		throw Exception::CORE::server_not_responding("send by sockets");
	}

	if (res && FD_ISSET(hSocket, &fdwrite))
	{
		res = send(hSocket, SendBuf.c_str(), static_cast<int>(SendBuf.size()), 0);
		if (res == SOCKET_ERROR || res == 0)
		{
			FD_CLR(hSocket, &fdwrite);
			throw Exception::CORE::wsa_send("send by sockets");
		}
	}

	FD_CLR(hSocket, &fdwrite);
}

string Sockets::Receive()
{
	DEBUG_LOG(3, "Receiving data using sockets");
	char buffer[BUFFER_SIZE];
	string RecvBuf;
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
		throw Exception::CORE::wsa_select("sockets select");
	}

	if (!res)
	{
		//timeout
		FD_CLR(hSocket, &fdread);
		throw Exception::CORE::server_not_responding("sockets select");
	}

	if (FD_ISSET(hSocket, &fdread))
	{
		res = recv(hSocket, buffer, BUFFER_SIZE, 0);
		const auto old_size = RecvBuf.size();
		RecvBuf += buffer;
		//RecvBuf[old_size + res] = '\0';
		if (res == SOCKET_ERROR)
		{
			FD_CLR(hSocket, &fdread);
			throw Exception::CORE::wsa_recv("receiving data over sockets failed");
		}
	}

	FD_CLR(hSocket, &fdread);
	if (res == 0)
	{
		isConnected = false;
		throw Exception::CORE::connection_closed("receiving data over sockets");
	}
	return RecvBuf;
}
