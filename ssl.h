#pragma once
#ifndef _SSL__H
#define _SSL__H
#include "socket.h"
#include "openssl.h"
namespace Security
{
	class SSL : public Socket, private OpenSSL
	{
	public:
		SSL();

		void Connect(const std::string& host, unsigned short port) override;
		void Send() override;
		void Receive() override;
	};
}
#endif