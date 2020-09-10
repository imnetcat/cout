#pragma once
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_
#include "../../core/types/binary.h"
namespace Protocol
{
	class Interface
	{
	public:
		virtual void Connect(const std::string& host, unsigned short port) = 0;
		virtual void Disconnect() = 0;
		virtual void Send() = 0;
		virtual void Receive() = 0;
	protected:
		Binary SendBuf;
		Binary RecvBuf;
	};
}
#endif