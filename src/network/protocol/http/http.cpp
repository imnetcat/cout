#include "http.h"
void Cout::Network::Protocol::HTTP::HTTP::Connect(const std::string& host, unsigned short port)
{
	_host = host;
	Raw::Connect(host, port);
}

bool Cout::Network::Protocol::HTTP::HTTP::ResponseCode(Code code)
{
	switch (code)
	{
	case OK:
		return std::string(RecvBuf.data()).find("200 OK") != std::string::npos;
	}
}

std::string Cout::Network::Protocol::HTTP::HTTP::ResponseData()
{
	std::string recvdata = std::string(RecvBuf.data());
	auto pos = recvdata.find("\r\n\r\n");
	if (pos == std::string::npos)
		return "";

	return recvdata.substr(pos + 2, RecvBuf.size() - pos - 2);
}

bool Cout::Network::Protocol::HTTP::HTTP::PutRequest(const std::string& path, size_t size)
{
	std::stringstream ss;
	ss << "PUT " << path << " HTTP/1.1\n";
	ss << "Host: " << _host << "\n";
	ss << "Content-Length: " << size << "\n";
	ss << "Content-Type: application/zip\n\n";

	std::string tmp = ss.str();
	SendBuf = ss.str();
	Raw::Send();
	return true;
}

void Cout::Network::Protocol::HTTP::HTTP::Send(const Binary& data)
{
	SendBuf = data;
	Raw::Send();
}

bool Cout::Network::Protocol::HTTP::HTTP::PostRequest(const std::string& path)
{
	std::stringstream ss;
	ss << "POST " << path << " HTTP/1.1\n";
	ss << "Host: " << _host << "\n\n\n";

	SendBuf = ss.str();
	Raw::Send();
	return true;
}