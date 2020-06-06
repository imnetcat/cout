#pragma once
#ifndef _SSL__H
#define _SSL__H
#include "openssl.h"
namespace Security
{
	template<class Proto>
	class SSL : public Proto, private OpenSSL
	{
	public:
		SSL();

		void Connect() override;
		void Disconnect() override;
		void Send() override;
		void Receive() override;
	};
}
#endif