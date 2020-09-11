#pragma once
#include "iprotocol.h"
#include "../sockets.h"
namespace Cout
{
	namespace Network
	{
		namespace Protocol
		{
			class Raw : public Sockets, public IProtocol
			{
			public:
				Raw();
				virtual ~Raw()
				{
					if (isConnected)
						Disconnect();
				}
				void Connect(const std::string& host, unsigned short port) override;
				void Disconnect() override;
				void Send() override;
				void Receive() override;
			protected:
				Binary SendBuf;
				Binary RecvBuf;
			};
		}
	}
}
