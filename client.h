#pragma once
#ifndef _CLIENT_H_
#define _CLIENT_H_
#include "ssl.h"
#include "mail.h"
#include <vector>
#include <string>
namespace SMTP
{
#define MSG_SIZE_IN_MB	25		// the maximum size of the message with all attachments
#define COUNTER_VALUE	100		// how many times program will try to receive data

	class Client : public SecureSocks
	{

	public:
		Client();
		~Client();

		void Connect(const std::string& host, unsigned short port) override;
		void Disconnect() override;
		void Send() override;
		void Receive() override;

		void SetAuth(const std::string& login, const std::string& pass);
		void Send(MAIL* mail);
	protected:

		const std::string m_sLocalHostName;

		void Handshake();

		bool isRetCodeValid(int validCode) const;
		bool IsCommandSupported(const std::string& response, const std::string& command) const;
		int SmtpXYZdigits() const;

		void SetUpSSL();
		void SetUpTLS();

		using COMMAND = const unsigned short int;
		void Command(COMMAND command);
		static const COMMAND INIT = 1;
	private:
		bool pendingTransaction;
		bool isSecured;
		MAIL* mail;
		const unsigned short BUFFER_SIZE = 10240;
		void Auth();

		struct Creds
		{
			std::string login;
			std::string password;
		};
		bool isAuthRequired = true;
		Creds credentials;

		static const COMMAND AUTHPLAIN = 11;
		static const COMMAND AUTHLOGIN = 12;
		static const COMMAND AUTHCRAMMD5 = 13;
		static const COMMAND AUTHDIGESTMD5 = 14;
		void AuthLogin();
		void AuthPlain();
		void CramMD5();
		void DigestMD5();
		static const COMMAND EHLO = 2;
		static const COMMAND MAILFROM = 3;
		static const COMMAND RCPTTO = 4;
		static const COMMAND DATA = 5;
		static const COMMAND DATABLOCK = 6;
		static const COMMAND DATAEND = 7;
		static const COMMAND QUIT = 8;
		static const COMMAND STARTTLS = 10;
		void Init();
		void Ehlo();
		void Starttls();
		void MailFrom();
		void RCPTto();
		void Data();
		void Datablock();
		void DataEnd();
		void Quit();
	};
}
#endif
