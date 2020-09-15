#pragma once
#include "../raw.h"
#include "codes.h"
#include <map>
#include <sstream>
namespace Cout
{
	namespace Network
	{
		namespace Protocol
		{
			namespace HTTP
			{
				class HTTP : public Raw
				{
				private:
					int _socket;
					std::string _host;
				public:
					void Connect(const std::string& host, unsigned short port);

					bool ResponseCode(Code code);

					std::string ResponseData();

					bool PutRequest(const std::string& path, size_t size);

					void Send(const Binary& data);

					bool PostRequest(const std::string& path);
				};
			}
		}
	}
}