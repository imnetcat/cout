#pragma once
#ifndef _SSL__H
#define _SSL__H
#include "openssl.h"
#include "raw.h"
class SecureSocks : public Raw, private OpenSSL
{
public:
	virtual ~SecureSocks() {};

	void Connect(const std::string& host, unsigned short port) override;
	void Send() override;
	void Receive() override;
};
#endif