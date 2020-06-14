#pragma once
#ifndef _SMTP_H_
#define _SMTP_H_
#include "core.h"
#include "socket.h"
#include "mail.h"
#include <vector>
#include <string>
namespace EMAIL
{
#define MSG_SIZE_IN_MB	25		// the maximum size of the message with all attachments
#define COUNTER_VALUE	100		// how many times program will try to receive data

	class SMTP : public Socket
	{

	public:
		SMTP();
		~SMTP();

		void Connect(const std::string& host, unsigned short port) override;
		void Disconnect() override;
				
		void SendMail(const MAIL& m);
	protected:

		const std::string m_sLocalHostName;

		void Handshake();

		bool isRetCodeValid(int validCode) const;
		bool IsCommandSupported(const std::string& response, const std::string& command) const;
		int SmtpXYZdigits() const;

		using COMMAND = const unsigned short int;
		void Command(COMMAND command);
		static const COMMAND INIT = 1;
	private:
		MAIL mail;
		static const COMMAND HELO = 2;
		static const COMMAND MAILFROM = 3;
		static const COMMAND RCPTTO = 4;
		static const COMMAND DATA = 5;
		static const COMMAND DATABLOCK = 6;
		static const COMMAND DATAEND = 7;
		static const COMMAND QUIT = 8;
		void Init();
		void Helo();
		void MailFrom();
		void RCPTto();
		void Data();
		void Datablock();
		void DataEnd();
		void Quit();
	};
}
#endif
