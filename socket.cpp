#include "socket.h"
using namespace std;

Socket::Socket() : hSocket(INVALID_SOCKET) 
{
	DEBUG_LOG(1, "Инициализация WinSocks");
	WSADATA wsaData;
	WORD wVer = MAKEWORD(2, 2);
	if (WSAStartup(wVer, &wsaData) != NO_ERROR)
		throw CORE::Exception::wsa_startup("WSA initializating");

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		throw CORE::Exception::wsa_version("WSA initializating");;
	}
}

Socket::~Socket()
{
	WSACleanup();
}

string Socket::GetLocalName() const
{
	char hostname[255];
	if (gethostname((char *)&hostname, 255) == SOCKET_ERROR)
		throw CORE::Exception::wsa_hostname("get local hostname");;
	return hostname;
}

void Socket::SocksConnect(const string& szServer, const unsigned short nPort_)
{
	DEBUG_LOG(1, "Установка соеденения с сервором");

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

	DEBUG_LOG(1, "Создаём новый сокет");
	if ((hSocket = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		throw CORE::Exception::wsa_invalid_socket("connecting on sockets");

	DEBUG_LOG(1, "Конвертируем байтовое представление порта в сетевой порядок байтов");
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

	DEBUG_LOG(1, "Заполняем структуру сервера");
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
			throw CORE::Exception::wsa_gethostby_name_addr("connecting on sockets");
		}
	}

	DEBUG_LOG(1, "Устанавлмваем сокет в неблокирующий режим");
	if (ioctlsocket(hSocket, FIONBIO, (unsigned long*)&ul) == SOCKET_ERROR)
	{
		closesocket(hSocket);
		throw CORE::Exception::wsa_ioctlsocket("connecting on sockets");;
	}

	DEBUG_LOG(1, "Подключаемся к серверу");
	if (connect(hSocket, (LPSOCKADDR)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			closesocket(hSocket);
			throw CORE::Exception::wsa_connect("connecting on sockets");;
		}
	}

	DEBUG_LOG(1, "Проверяем подключение");
	while (true)
	{
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdexcept);

		FD_SET(hSocket, &fdwrite);
		FD_SET(hSocket, &fdexcept);

		if ((res = select(static_cast<int>(hSocket) + 1, NULL, &fdwrite, &fdexcept, &timeout)) == SOCKET_ERROR)
		{
			closesocket(hSocket);
			throw CORE::Exception::wsa_select("selecting sockets");;
		}

		if (!res)
		{
			closesocket(hSocket);
			throw CORE::Exception::select_timeout("connecting on sockets");;
		}
		if (res && FD_ISSET(hSocket, &fdwrite))
			break;
		if (res && FD_ISSET(hSocket, &fdexcept))
		{
			closesocket(hSocket);
			throw CORE::Exception::wsa_select("connecting on sockets");;
		}
	} // while

	FD_CLR(hSocket, &fdwrite);
	FD_CLR(hSocket, &fdexcept);

	DEBUG_LOG(1, "Подключение с сервером успешно установлено");
}

void Socket::Disconnect()
{
	if (hSocket)
	{
		closesocket(hSocket);
	}
	hSocket = INVALID_SOCKET;
}

void Socket::Input(const char* data, size_t size)
{
	int res;
	fd_set fdwrite;
	timeval time;

	time.tv_sec = TIMEOUT;
	time.tv_usec = 0;

	if (size)
		throw CORE::Exception::sendbuf_is_empty("send by sockets");

	FD_ZERO(&fdwrite);

	FD_SET(hSocket, &fdwrite);

	if ((res = select(static_cast<int>(hSocket) + 1, NULL, &fdwrite, NULL, &time)) == SOCKET_ERROR)
	{
		FD_CLR(hSocket, &fdwrite);
		throw CORE::Exception::wsa_select("send by sockets");
	}

	if (!res)
	{
		//timeout
		FD_CLR(hSocket, &fdwrite);
		throw CORE::Exception::server_not_responding("send by sockets");
	}

	if (res && FD_ISSET(hSocket, &fdwrite))
	{
		res = send(hSocket, data, static_cast<int>(size), 0);
		if (res == SOCKET_ERROR || res == 0)
		{
			FD_CLR(hSocket, &fdwrite);
			throw CORE::Exception::wsa_send("send by sockets");
		}
	}

	FD_CLR(hSocket, &fdwrite);
}

const char* Socket::Output()
{
	ZeroMemory(&OutputBuf, BUFFER_SIZE);
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
		throw CORE::Exception::wsa_select("sockets select");
	}

	if (!res)
	{
		//timeout
		FD_CLR(hSocket, &fdread);
		throw CORE::Exception::server_not_responding("sockets select");
	}

	if (FD_ISSET(hSocket, &fdread))
	{
		res = recv(hSocket, OutputBuf, BUFFER_SIZE, 0);
		OutputBuf[res] = '\0';
		if (res == SOCKET_ERROR)
		{
			FD_CLR(hSocket, &fdread);
			throw CORE::Exception::wsa_recv("sockets receiving");
		}
	}

	FD_CLR(hSocket, &fdread);
	if (res == 0)
	{
		throw CORE::Exception::connection_closed("sockets receiving");
	}

	return OutputBuf;
}
