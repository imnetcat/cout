#pragma once
#ifndef _ESMTPS_H_
#define _ESMTPS_H_
#include "ssl.h"
#include "esmtp.h"
#include "core.h"
namespace EMAIL
{
	class Extensions : public Security::SSL
	{
	public:
		Extensions();

		void Connect(const std::string& host, unsigned short port) override;

		enum SMTP_SECURITY_TYPE
		{
			NO_SECURITY,
			USE_TLS,
			USE_SSL
		};

		void SetSecuriry(SMTP_SECURITY_TYPE type);

		void SetUpSSL();
		void SetUpTLS();
	protected:
		void Command(COMMAND command);
	private:
		static const COMMAND STARTTLS = 10;
		void Starttls();
		SMTP_SECURITY_TYPE sec;
	};
}
#endif