#include "esmtpsa.h"
#include "../../../core/exception.h"
#include "../../../core/filesystem/explorer.h"
#include "../../../encryption/algorithm/base64.h"
#include "../../../core/utils.h"
#include "../../../core/logging/debug_logger.h"
#include "../authentication/method.h"
#include "mail/mail.h"
#include "exception.h"
#include "../exception.h"

Cout::Network::Protocol::SMTP::ESMTPSA::ESMTPSA() : pendingTransaction(false), Secured(), m_sLocalHostName(GetLocalName())
{
	DEBUG_LOG(3, "Initializing ESMTPSA protocol");
}

Cout::Network::Protocol::SMTP::ESMTPSA::~ESMTPSA()
{
	if (isConnected) 
		Disconnect();
}

void Cout::Network::Protocol::SMTP::ESMTPSA::Send()
{
	Secured::Send();
}

void Cout::Network::Protocol::SMTP::ESMTPSA::Receive()
{
	Secured::Receive();
}

void Cout::Network::Protocol::SMTP::ESMTPSA::Init()
{
	DEBUG_LOG(2, "Initializing SMTP protocol");
	Receive();

	if (isRetCodeValid(500))
		throw Cout::Network::Protocol::Exceptions::smtp::command_not_recognized(WHERE, "The server uses an outdated specification and does not support extensions");

	if (!isRetCodeValid(220))
		throw Cout::Network::Protocol::Exceptions::wsa::server_not_responding(WHERE, "SMTP init");
}

void Cout::Network::Protocol::SMTP::ESMTPSA::Disconnect()
{
	DEBUG_LOG(2, "SMTP Disconnecting");
	if (isConnected)
	{
		Command(QUIT);
	}
	Secured::Disconnect();
}

void Cout::Network::Protocol::SMTP::ESMTPSA::Quit()
{
	DEBUG_LOG(3, "Sending QUIT command");
	if (pendingTransaction)
	{
		// close pending transaction first
		SendBuf = "\r\n.\r\n";
		Send();
		Receive();
	}
	SendBuf = "QUIT\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(221))
		throw Cout::Network::Protocol::Exceptions::smtp::command_failed(WHERE, "sending QUIT command");
}

void Cout::Network::Protocol::SMTP::ESMTPSA::MailFrom()
{
	DEBUG_LOG(3, "Sending MAIL FROM command");
	if (!mail->GetMailFrom().size())
		throw Cout::Network::Protocol::Exceptions::smtp::undef_mail_from(WHERE, "sending MAIL FROM command");

	SendBuf = "MAIL FROM:<" + mail->GetMailFrom() + ">\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(250))
		throw Cout::Network::Protocol::Exceptions::smtp::command_failed(WHERE, "sending MAIL FROM command");
}

void Cout::Network::Protocol::SMTP::ESMTPSA::RCPTto()
{
	DEBUG_LOG(3, "Sending RCPT TO command");
	if (!mail->GetRecipientCount())
		throw Cout::Network::Protocol::Exceptions::smtp::undef_recipients(WHERE, "sending RCPT TO command");

	const auto& recipients = mail->GetRecipient();
	for (const auto& [mail, name] : recipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail + ">\r\n";

		Send();
		Receive();

		if (!isRetCodeValid(250))
			throw Cout::Network::Protocol::Exceptions::smtp::command_failed(WHERE, "sending recipients by RCPT TO command");
	}

	const auto& ccrecipients = mail->GetCCRecipient();
	for (const auto& [mail, name] : ccrecipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail + ">\r\n";

		Send();
		Receive();

		if (!isRetCodeValid(250))
			throw Cout::Network::Protocol::Exceptions::smtp::command_failed(WHERE, "sending ccrecipients by RCPT TO command");
	}

	const auto& bccrecipients = mail->GetBCCRecipient();
	for (const auto& [mail, name] : bccrecipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail + ">\r\n";

		Send();
		Receive();

		if (!isRetCodeValid(250))
			throw Cout::Network::Protocol::Exceptions::smtp::command_failed(WHERE, "sending bccrecipients by RCPT TO command");
	}
}

void Cout::Network::Protocol::SMTP::ESMTPSA::Data()
{
	DEBUG_LOG(3, "Sending DATA command");
	SendBuf = "DATA\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(354))
		throw Cout::Network::Protocol::Exceptions::smtp::command_failed(WHERE, "sending DATA command");
}

void Cout::Network::Protocol::SMTP::ESMTPSA::Datablock()
{
	DEBUG_LOG(2, "Sending mail header");
	SendBuf = mail->createHeader();
	Send();

	DEBUG_LOG(2, "Sending mail body");

	if (!mail->GetBodySize())
	{
		SendBuf = " \r\n";
		Send();
	}

	const auto& body = mail->GetBody();
	for (const auto& line : body)
	{
		SendBuf = line + "\r\n";
		Send();
	}

	const auto& attachments = mail->GetAttachments();
	for (const auto& path : attachments)
	{
		DEBUG_LOG(2, "Sending the attachment file");
		unsigned long long FileSize, TotalSize;
		unsigned long long MsgPart;
		std::string FileName, EncodedFileName;
		std::string::size_type pos;

		TotalSize = 0;
		DEBUG_LOG(3, "Checking file for existing");

		Core::Filesystem::Explorer explorer;

		if (!explorer.exist(path))
			throw Cout::Exceptions::Core::file_not_exist(WHERE, "SMTP attachment file not found");

		DEBUG_LOG(3, "Checking file size");

		FileSize = explorer.size(path);
		TotalSize += FileSize;

		if (TotalSize / 1024 > MSG_SIZE_IN_MB * 1024)
			throw Cout::Network::Protocol::Exceptions::smtp::msg_too_big(WHERE, "SMTP attachment files are too large");

		DEBUG_LOG(3, "Sending file header");

		pos = path.find_last_of("\\");
		if (pos == std::string::npos) FileName = path;
		else FileName = path.substr(pos + 1);

		Encryption::Algorithm::Base64 base64;

		UnsignedBinary fnamebin;
		fnamebin.Assign((UnsignedByte*)FileName.c_str(), FileName.size());

		//RFC 2047 - Use UTF-8 charset,base64 encode.
		EncodedFileName = "=?UTF-8?B?";
		EncodedFileName += Core::Utils::to_string(base64.Encode(fnamebin).data());
		EncodedFileName += "?=";

		SendBuf = "--" + MAIL::BOUNDARY_TEXT + "\r\n";
		SendBuf += "Content-Type: application/x-msdownload; name=\"";
		SendBuf += EncodedFileName;
		SendBuf += "\"\r\n";
		SendBuf += "Content-Transfer-Encoding: base64\r\n";
		SendBuf += "Content-Disposition: attachment; filename=\"";
		SendBuf += EncodedFileName;
		SendBuf += "\"\r\n";
		SendBuf += "\r\n";

		Send();

		DEBUG_LOG(3, "Sending file body");

		MsgPart = 0;
		explorer.read(path, 54, [&base64, &MsgPart, this] (const Binary& block) mutable {
			UnsignedBinary bin_block;
			bin_block.Assign((UnsignedByte*)block.data(), block.size());
			MsgPart ? SendBuf += Core::Utils::to_string(base64.Encode(bin_block).data())
				: SendBuf = Core::Utils::to_string(base64.Encode(bin_block).data());
			SendBuf += "\r\n";
			MsgPart += block.size() + 2ull;
			if (MsgPart >= BUFFER_SIZE / 2)
			{
				// sending part of the message
				MsgPart = 0;
				Send();
			}
		});
		if (MsgPart)
		{
			Send();
		}
	}

	if (mail->GetAttachmentsSize())
	{
		SendBuf = "\r\n--" + MAIL::BOUNDARY_TEXT + "--\r\n";
		Send();
	}
}

void Cout::Network::Protocol::SMTP::ESMTPSA::DataEnd()
{
	DEBUG_LOG(3, "Sending the CRLF");
	// <CRLF> . <CRLF>
	SendBuf = "\r\n.\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(250))
		throw Cout::Network::Protocol::Exceptions::smtp::msg_body_error(WHERE, "wrong letter format");
}

const std::string& Cout::Network::Protocol::SMTP::ESMTPSA::GetLogin() const noexcept
{
	return credentials.login;
}
const std::string& Cout::Network::Protocol::SMTP::ESMTPSA::GetPassword() const noexcept
{
	return credentials.password;
}

void Cout::Network::Protocol::SMTP::ESMTPSA::SetLogin(const std::string& login)
{
	credentials.login = login;
}

void Cout::Network::Protocol::SMTP::ESMTPSA::SetPassword(const std::string& pass)
{
	credentials.password = pass;
}

bool Cout::Network::Protocol::SMTP::ESMTPSA::isRetCodeValid(int validCode) const
{
	if (!RecvBuf.size())
		return false;

	int receiveCode;
	std::stringstream iss;
	iss << RecvBuf[0] << RecvBuf[1] << RecvBuf[2];
	iss >> receiveCode;

	bool retCodeValid = (validCode == receiveCode);
	return retCodeValid;
}

void Cout::Network::Protocol::SMTP::ESMTPSA::Command(COMMAND command)
{
	switch (command)
	{
	case INIT:
		Init();
		break;
	case EHLO:
		Ehlo();
		break;
	case STARTTLS:
		Starttls();
		break;
	case MAILFROM:
		MailFrom();
		break;
	case RCPTTO:
		RCPTto();
		break;
	case DATA:
		Data();
		break;
	case DATABLOCK:
		Datablock();
		break;
	case DATAEND:
		DataEnd();
		break;
	case AUTHPLAIN:
		AuthPlain();
		break;
	case AUTHLOGIN:
		AuthLogin();
		break;
	case AUTHCRAMMD5:
		CramMD5();
		break;
	case AUTHDIGESTMD5:
		DigestMD5();
		break;
	case QUIT:
		Quit();
		break;
	default:
		throw Cout::Network::Protocol::Exceptions::smtp::undef_command(WHERE, "specifying a command");
		break;
	}
}

// A simple string match
bool Cout::Network::Protocol::SMTP::ESMTPSA::IsCommandSupported(const std::string& response, const std::string& command) const
{
	return response.find(command) != std::string::npos;
}

int Cout::Network::Protocol::SMTP::ESMTPSA::SmtpXYZdigits() const
{
	if (RecvBuf.empty())
		return 0;
	return (RecvBuf[0] - '0') * 100 + (RecvBuf[1] - '0') * 10 + RecvBuf[2] - '0';
}

void Cout::Network::Protocol::SMTP::ESMTPSA::Handshake()
{
	DEBUG_LOG(1, "SMTP Handshake");
	Command(INIT);
	Command(EHLO);
}

void Cout::Network::Protocol::SMTP::ESMTPSA::Starttls()
{
	DEBUG_LOG(3, "Sending STARTTLS command");
	SendBuf = "STARTTLS\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(220))
		throw Cout::Network::Protocol::Exceptions::smtp::command_failed(WHERE, "attempt to set up tls over SMTP");
}
void Cout::Network::Protocol::SMTP::ESMTPSA::Ehlo()
{
	DEBUG_LOG(3, "Sending EHLO command");
	SendBuf = "EHLO ";
	SendBuf += m_sLocalHostName.empty() ? "localhost" : m_sLocalHostName;
	SendBuf += "\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(250))
		throw Cout::Network::Protocol::Exceptions::smtp::command_failed(WHERE, "server return error after EHLO command");
}

void Cout::Network::Protocol::SMTP::ESMTPSA::SetUpSSL()
{
	DEBUG_LOG(2, "Setting up SSL over ESMTP");
	Secured::SetUpSSL();
	DEBUG_LOG(2, "Successfuly set up SSL over ESMTP connection");
}

void Cout::Network::Protocol::SMTP::ESMTPSA::SetUpTLS()
{
	DEBUG_LOG(2, "Setting up TLS over ESMTP");
	if (IsCommandSupported(RecvBuf.data(), "STARTTLS") == false)
	{
		throw Cout::Network::Protocol::Exceptions::smtp::tls_not_supported(WHERE, "attempt to set up TLS over ESMTP");
	}

	Command(STARTTLS);
	Secured::SetUpSSL();
	Command(EHLO);

	DEBUG_LOG(2, "Successfuly set up TLS over ESMTP connection");
}

void Cout::Network::Protocol::SMTP::ESMTPSA::Connect(const std::string& host, unsigned short port)
{
	DEBUG_LOG(1, "ESMTPSA Connecting");
	Secured::Connect(host, port);

	if (sec == Protocol::Secured::Type::SSL)
	{
		SetUpSSL();
	}

	Handshake();

	if (sec == Protocol::Secured::Type::TLS)
	{
		SetUpTLS();
	}

	Auth();
}


void Cout::Network::Protocol::SMTP::ESMTPSA::Send(MAIL* m)
{
	mail = m;
	Command(MAILFROM);
	Command(RCPTTO);
	Command(DATA);
	DEBUG_LOG(1, "Start SMTP transaction");
	pendingTransaction = true;
	Command(DATABLOCK);
	Command(DATAEND);
	pendingTransaction = false;
	DEBUG_LOG(1, "Success SMTP transaction");
	mail = nullptr;
}

void Cout::Network::Protocol::SMTP::ESMTPSA::Auth()
{
	DEBUG_LOG(3, "Choosing authentication");
	if (IsCommandSupported(RecvBuf.data(), "AUTH"))
	{
		if (!credentials.login.size())
			throw Cout::Network::Protocol::Exceptions::smtp::undef_login(WHERE, "SMTP authentication selection");

		if (!credentials.password.size())
			throw Cout::Network::Protocol::Exceptions::smtp::undef_password(WHERE, "SMTP authentication selection");

		if (IsCommandSupported(RecvBuf.data(), "LOGIN") == true)
		{
			Command(AUTHLOGIN);
		}
		else if (IsCommandSupported(RecvBuf.data(), "PLAIN") == true)
		{
			Command(AUTHPLAIN);
		}
		else if (IsCommandSupported(RecvBuf.data(), "CRAM-MD5") == true)
		{
			Command(AUTHCRAMMD5);
		}
		else if (IsCommandSupported(RecvBuf.data(), "DIGEST-MD5") == true)
		{
			Command(AUTHDIGESTMD5);
		}
		else
		{
			throw Cout::Network::Protocol::Exceptions::smtp::auth_not_supported(WHERE, "SMTP authentication selection");
		}
	}
	else
	{
		throw Cout::Network::Protocol::Exceptions::smtp::auth_not_supported(WHERE, "SMTP authentication selection");
	}
}

void Cout::Network::Protocol::SMTP::ESMTPSA::AuthPlain()
{
	DEBUG_LOG(2, "Authentication AUTH PLAIN");

	SendBuf = "AUTH PLAIN " + Authentication::Method::Plain(credentials.login, credentials.password) + "\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(235))
		throw Cout::Network::Protocol::Exceptions::smtp::auth_failed(WHERE, "SMTP Plain authentication");
}

void Cout::Network::Protocol::SMTP::ESMTPSA::AuthLogin()
{
	DEBUG_LOG(2, "Authentication AUTH LOGIN");
	SendBuf = "AUTH LOGIN\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(334))
		throw Cout::Network::Protocol::Exceptions::smtp::auth_failed(WHERE, "SMTP LOGIN authentication");

	DEBUG_LOG(3, "Sending login");
	std::string encoded_login = Authentication::Method::Login(credentials.login);
	SendBuf = encoded_login + "\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(334))
		throw Cout::Network::Protocol::Exceptions::smtp::undef_response(WHERE, "SMTP LOGIN authentication");

	DEBUG_LOG(3, "Sending password");
	std::string encoded_password = Authentication::Method::Login(credentials.password);
	SendBuf = encoded_password + "\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(235))
	{
		throw Cout::Network::Protocol::Exceptions::smtp::bad_credentials(WHERE, "SMTP LOGIN authentication");
	}
}

void Cout::Network::Protocol::SMTP::ESMTPSA::CramMD5()
{
	DEBUG_LOG(2, "Authentication AUTH CRAM-MD5");
	SendBuf = "AUTH CRAM-MD5\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(334))
		throw Cout::Network::Protocol::Exceptions::smtp::auth_failed(WHERE, "SMTP CRAM-MD5 authentication");

	DEBUG_LOG(3, "Token generation");

	std::string encoded_challenge = Authentication::Method::CramMD5(std::string(RecvBuf.data()).substr(4), credentials.login, credentials.password);

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(1, "Token sending " + encoded_challenge);

	Send();
	Receive();

	if (!isRetCodeValid(334))
		throw Cout::Network::Protocol::Exceptions::smtp::auth_failed(WHERE, "SMTP CRAM-MD5 authentication");
}

void Cout::Network::Protocol::SMTP::ESMTPSA::DigestMD5()
{
	DEBUG_LOG(2, "Authentication AUTH DIGEST-MD5");
	SendBuf = "AUTH DIGEST-MD5\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(335))
		throw Cout::Network::Protocol::Exceptions::smtp::auth_failed(WHERE, "SMTP DIGEST-MD5 authentication");

	DEBUG_LOG(3, "Token generation");

	const std::string charset = std::string(RecvBuf.data()).find("charset") != std::string::npos ?
		"charset=utf-8," : "";
	const std::string addr = Core::Utils::to_string(host) + ":" + Core::Utils::to_string(port);

	std::string encoded_challenge = Authentication::Method::DigestMD5(std::string(RecvBuf.data()).substr(4), charset, addr, credentials.login, credentials.password);

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(3, "Token sending " + encoded_challenge);

	Send();
	Receive();

	if (!isRetCodeValid(335))
		throw Cout::Network::Protocol::Exceptions::smtp::auth_failed(WHERE, "SMTP DIGEST-MD5 authentication");

	// only completion carraige needed for end digest md5 auth
	SendBuf = "\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(335))
		throw Cout::Network::Protocol::Exceptions::smtp::auth_failed(WHERE, "SMTP DIGEST-MD5 authentication");
}
