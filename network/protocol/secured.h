#pragma once
#ifndef _SSL__H
#define _SSL__H
#include "../../encryption/openssl.h"
#include "raw.h"
#include <utility>
namespace Protocol
{
	class Secured : public Raw, private Encryption::OpenSSL
	{
	public:
		enum Type
		{
			TLS,
			SSL
		};
		Secured();
		virtual ~Secured() {};

		void Connect(const std::string& host, unsigned short port) override;
		void Disconnect() override;
		void Send() override;
		void Receive() override;
		void SetUpSSL();
	protected:
		bool isSecured;
	};
}
#endif