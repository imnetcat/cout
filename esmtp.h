#pragma once
#ifndef _ESMTP_H_
#define _ESMTP_H_
#include "smtp.h"
#include "core.h"
namespace EMAIL
{
	class ESMTP : public SMTP
	{
	public:
		ESMTP();
		~ESMTP();
		void Connect(const std::string& host, unsigned short port) override;
	protected:
		void Command(COMMAND command);
		void Ehlo();
		void Handshake();
		static const COMMAND EHLO = 9;
	};
}
#endif // _ESMTP_H_
