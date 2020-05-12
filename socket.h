#pragma once
#ifndef _SOCKET_H_
#define _SOCKET_H_

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define TIME_IN_SEC		3*60	// how long client will wait for server response in non-blocking mode
#define BUFFER_SIZE		10240	// SendData and RecvData buffers sizes

class Socket
{
public:

	Socket() {
		DEBUG_LOG(1, "������������� WinSocks");
		// Initialize WinSock
		hSocket = INVALID_SOCKET;
		WSADATA wsaData;
		WORD wVer = MAKEWORD(2, 2);
		if (WSAStartup(wVer, &wsaData) != NO_ERROR)
			throw FAIL(WSA_STARTUP);

		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
		{
			WSACleanup();
			throw FAIL(WSA_VER);
		}

		char hostname[255];
		if (gethostname((char *)&hostname, 255) == SOCKET_ERROR)
			throw FAIL(WSA_HOSTNAME);

		m_sLocalHostName = hostname;
	}

	~Socket();

	RETCODE SocksConnect()
	{
		DEBUG_LOG(1, "��������� ���������� � ��������");
		string szServer = server.name;
		const unsigned short nPort_ = server.port;

		unsigned short nPort = 0;
		LPSERVENT lpServEnt;
		SOCKADDR_IN sockAddr;
		unsigned long ul = 1;
		fd_set fdwrite, fdexcept;
		timeval timeout;
		int res = 0;

		timeout.tv_sec = TIME_IN_SEC;
		timeout.tv_usec = 0;

		hSocket = INVALID_SOCKET;

		DEBUG_LOG(1, "������ ����� �����");
		if ((hSocket = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
			throw FAIL(WSA_INVALID_SOCKET);

		DEBUG_LOG(1, "������������ �������� ������������� ����� � ������� ������� ������");
		if (nPort_ != 0)
			nPort = htons(nPort_);
		else
		{
			lpServEnt = getservbyname("mail", 0);
			if (lpServEnt == NULL)
				nPort = htons(25);
			else
				nPort = lpServEnt->s_port;
		}

		DEBUG_LOG(1, "��������� ��������� �������");
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = nPort;
		if ((sockAddr.sin_addr.s_addr = inet_addr(szServer.c_str())) == INADDR_NONE)
		{
			LPHOSTENT host;

			host = gethostbyname(szServer.c_str());
			if (host)
				memcpy(&sockAddr.sin_addr, host->h_addr_list[0], host->h_length);
			else
			{
				closesocket(hSocket);
				throw FAIL(WSA_GETHOSTBY_NAME_ADDR);
			}
		}

		DEBUG_LOG(1, "������������� ����� � ������������� �����");
		if (ioctlsocket(hSocket, FIONBIO, (unsigned long*)&ul) == SOCKET_ERROR)
		{
			closesocket(hSocket);
			throw FAIL(WSA_IOCTLSOCKET);
		}

		DEBUG_LOG(1, "������������ � �������");
		if (connect(hSocket, (LPSOCKADDR)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				closesocket(hSocket);
				throw FAIL(WSA_CONNECT);
			}
		}

		DEBUG_LOG(1, "��������� �����������");
		while (true)
		{
			FD_ZERO(&fdwrite);
			FD_ZERO(&fdexcept);

			FD_SET(hSocket, &fdwrite);
			FD_SET(hSocket, &fdexcept);

			if ((res = select(hSocket + 1, NULL, &fdwrite, &fdexcept, &timeout)) == SOCKET_ERROR)
			{
				closesocket(hSocket);
				throw FAIL(WSA_SELECT);
			}

			if (!res)
			{
				closesocket(hSocket);
				throw FAIL(SELECT_TIMEOUT);
			}
			if (res && FD_ISSET(hSocket, &fdwrite))
				break;
			if (res && FD_ISSET(hSocket, &fdexcept))
			{
				closesocket(hSocket);
				throw FAIL(WSA_SELECT);
			}
		} // while

		FD_CLR(hSocket, &fdwrite);
		FD_CLR(hSocket, &fdexcept);

		DEBUG_LOG(1, "����������� � �������� ������� �����������");
		return SUCCESS;
	}


	void Disconnect()
	{
		if (hSocket)
		{
			closesocket(hSocket);
		}
		hSocket = INVALID_SOCKET;
	}

	RETCODE Connect() {
		if (hSocket == INVALID_SOCKET)
		{
			if (SocksConnect())
			{
				DEBUG_LOG(1, "������ ��� ����������");
				if (RecvBuf[0] == '5' && RecvBuf[1] == '3' && RecvBuf[2] == '0')
					server.isConnected = false;
				Disconnect();
				throw FAIL(WSA_INVALID_SOCKET);
			}
		}
		return SUCCESS;
	}


	RETCODE SendData_NoSec(int send_timeout)
	{
		int res;
		fd_set fdwrite;
		timeval time;

		time.tv_sec = send_timeout;
		time.tv_usec = 0;

		if (SendBuf.empty())
			throw FAIL(SENDBUF_IS_EMPTY);

		FD_ZERO(&fdwrite);

		FD_SET(hSocket, &fdwrite);

		if ((res = select(hSocket + 1, NULL, &fdwrite, NULL, &time)) == SOCKET_ERROR)
		{
			FD_CLR(hSocket, &fdwrite);
			throw FAIL(WSA_SELECT);
		}

		if (!res)
		{
			//timeout
			FD_CLR(hSocket, &fdwrite);
			throw FAIL(SERVER_NOT_RESPONDING);
		}

		if (res && FD_ISSET(hSocket, &fdwrite))
		{
			res = send(hSocket, SendBuf.c_str(), SendBuf.size(), 0);
			if (res == SOCKET_ERROR || res == 0)
			{
				FD_CLR(hSocket, &fdwrite);
				throw FAIL(WSA_SEND);
			}
		}

		FD_CLR(hSocket, &fdwrite);

		return SUCCESS;
	}

	RETCODE ReceiveData_NoSec(int recv_timeout)
	{
		int res = 0;
		fd_set fdread;
		timeval time;

		time.tv_sec = recv_timeout;
		time.tv_usec = 0;

		FD_ZERO(&fdread);

		FD_SET(hSocket, &fdread);

		if ((res = select(hSocket + 1, &fdread, NULL, NULL, &time)) == SOCKET_ERROR)
		{
			FD_CLR(hSocket, &fdread);
			throw FAIL(WSA_SELECT);
		}

		if (!res)
		{
			//timeout
			FD_CLR(hSocket, &fdread);
			throw FAIL(SERVER_NOT_RESPONDING);
		}

		if (FD_ISSET(hSocket, &fdread))
		{
			char buffer[BUFFER_SIZE];
			res = recv(hSocket, buffer, BUFFER_SIZE, 0);
			RecvBuf = buffer;
			RecvBuf[res] = '\0';
			if (res == SOCKET_ERROR)
			{
				FD_CLR(hSocket, &fdread);
				throw FAIL(WSA_RECV);
			}
		}

		FD_CLR(hSocket, &fdread);
		if (res == 0)
		{
			throw FAIL(CONNECTION_CLOSED);
		}

		return SUCCESS;
	}

protected:
	struct Auth
	{
		std::string login;
		std::string password;
	};

	struct SERVER
	{
		SMTP_SECURITY_TYPE security = NO_SECURITY;
		bool isConnected = false;
		unsigned short port = 0;
		std::string name;
		bool isAuth = true;
		Auth auth;
	};
	SERVER server;
	std::string SendBuf;
	std::string RecvBuf;
	SOCKET hSocket;
	std::string m_sLocalHostName;
};

Socket::~Socket()
{
	WSACleanup();
}

#endif