#include "client.h"
#include "core.h"
#include "auth.h"
#include "mail.h"
#include "exceptions.h"
using namespace std;
using namespace SMTP;

Client::Client() : SecureSocks(), m_sLocalHostName(GetLocalName()) { }

Client::~Client()
{
	if (isConnected) Client::Disconnect();
}

void Client::Init()
{
	DEBUG_LOG(2, "Initializing SMTP protocol");
	Client::SecureSocks::Receive();

	if (!isRetCodeValid(220))
		throw CORE::Exception::server_not_responding("SMTP init");
}

void Client::Disconnect()
{
	DEBUG_LOG(2, "SMTP Disconnecting");
	if (isConnected)
	{
		Client::Command(QUIT);
	}
	SecureSocks::Disconnect();
}

void Client::Quit()
{
	DEBUG_LOG(3, "Sending QUIT command");
	SendBuf = "QUIT\r\n";
	SecureSocks::Send();
	SecureSocks::Receive();

	if (!isRetCodeValid(221))
		throw Exception::QUIT_FAILED("sending QUIT command");
}

void Client::MailFrom()
{
	DEBUG_LOG(3, "Sending MAIL FROM command");
	if (!mail->GetMailFrom().size())
		throw Exception::UNDEF_MAIL_FROM("sending MAIL FROM command");

	SendBuf = "MAIL FROM:<" + mail->GetMailFrom() + ">\r\n";

	SecureSocks::Send();
	SecureSocks::Receive();

	if (!isRetCodeValid(250))
		throw Exception::MAIL_FROM_FAILED("sending MAIL FROM command");
}

void Client::RCPTto()
{
	DEBUG_LOG(3, "Sending RCPT TO command");
	if (!mail->GetRecipientCount())
		throw Exception::UNDEF_RECIPIENTS("sending RCPT TO command");

	const auto& recipients = mail->GetRecipient();
	for (const auto& [mail, name] : recipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail + ">\r\n";

		SecureSocks::Send();
		SecureSocks::Receive();

		if (!isRetCodeValid(250))
			throw Exception::RCPT_TO_FAILED("sending recipients by RCPT TO command");
	}

	const auto& ccrecipients = mail->GetCCRecipient();
	for (const auto& [mail, name] : ccrecipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail + ">\r\n";

		SecureSocks::Send();
		SecureSocks::Receive();

		if (!isRetCodeValid(250))
			throw Exception::RCPT_TO_FAILED("sending ccrecipients by RCPT TO command");
	}

	const auto& bccrecipients = mail->GetBCCRecipient();
	for (const auto& [mail, name] : bccrecipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail + ">\r\n";

		SecureSocks::Send();
		SecureSocks::Receive();

		if (!isRetCodeValid(250))
			throw Exception::RCPT_TO_FAILED("sending bccrecipients by RCPT TO command");
	}
}

void Client::Data()
{
	DEBUG_LOG(3, "Sending DATA command");
	SendBuf = "DATA\r\n";
	SecureSocks::Send();
	SecureSocks::Receive();

	if (!isRetCodeValid(354))
		throw Exception::DATA_FAILED("sending DATA command");
}

void Client::Datablock()
{
	DEBUG_LOG(2, "Sending mail header");
	SendBuf = mail->createHeader();
	SecureSocks::Send();

	DEBUG_LOG(2, "Sending mail body");

	if (!mail->GetBodySize())
	{
		SendBuf = " \r\n";
		SecureSocks::Send();
	}

	const auto& body = mail->GetBody();
	for (const auto& line : body)
	{
		SendBuf = line + "\r\n";
		SecureSocks::Send();
	}

	const auto& attachments = mail->GetAttachments();
	for (const auto& path : attachments)
	{
		DEBUG_LOG(2, "Sending the attachment file");
		unsigned long long FileSize, TotalSize;
		unsigned long long MsgPart;
		string FileName, EncodedFileName;
		string::size_type pos;
				
		TotalSize = 0;
		DEBUG_LOG(3, "Checking file for existing");

		if(!CORE::Filesystem::file::exist(path))
			throw CORE::Exception::file_not_exist("SMTP attachment file not found");

		DEBUG_LOG(3, "Checking file size");

		FileSize = CORE::Filesystem::file::size(path);
		TotalSize += FileSize;

		if (TotalSize / 1024 > MSG_SIZE_IN_MB * 1024)
			throw Exception::MSG_TOO_BIG("SMTP attachment files are too large");

		DEBUG_LOG(3, "Sending file header");
	
		pos = path.find_last_of("\\");
		if (pos == string::npos) FileName = path;
		else FileName = path.substr(pos + 1);

		//RFC 2047 - Use UTF-8 charset,base64 encode.
		EncodedFileName = "=?UTF-8?B?";
		EncodedFileName += CORE::BASE64::base64_encode((unsigned char *)FileName.c_str(), FileName.size());
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

		SecureSocks::Send();

		DEBUG_LOG(3, "Sending file body");
		
		CORE::File file(path);

		MsgPart = 0;
		vector<CORE::Byte> FileBuf;
		const size_t s = file.Size();
		for (size_t i = 0; i < s; i += 54)
		{
			FileBuf = file.Read(i, 54);
			MsgPart ? SendBuf += CORE::BASE64::base64_encode(reinterpret_cast<const unsigned char*>(FileBuf.data()), FileBuf.size())
				: SendBuf = CORE::BASE64::base64_encode(reinterpret_cast<const unsigned char*>(FileBuf.data()), FileBuf.size());
			SendBuf += "\r\n";
			MsgPart += FileBuf.size() + 2ull;
			if (MsgPart >= BUFFER_SIZE / 2)
			{
				// sending part of the message
				MsgPart = 0;
				SecureSocks::Send();
			}
		}
		if (MsgPart)
		{
			SecureSocks::Send();
		}
		file.close();
	}

	if (mail->GetAttachmentsSize())
	{
		SendBuf = "\r\n--" + MAIL::BOUNDARY_TEXT + "--\r\n";
		SecureSocks::Send();
	}
}

void Client::DataEnd()
{
	DEBUG_LOG(3, "Sending the CRLF");
	// <CRLF> . <CRLF>
	SendBuf = "\r\n.\r\n";
	SecureSocks::Send();
	SecureSocks::Receive();

	if (!isRetCodeValid(250))
		throw Exception::MSG_BODY_ERROR("wrong letter format");
}

bool Client::isRetCodeValid(int validCode) const
{
	stringstream istr(RecvBuf);
	vector <string> ostr;
	string to;
	while (getline(istr, to, '\n')) {
		ostr.push_back(to);
	}
	ostr.pop_back();
	string lastLine = ostr.back();

	int receiveCode;
	std::istringstream(lastLine.substr(0, 3)) >> receiveCode;

	bool retCodeValid = (validCode == receiveCode);
	return retCodeValid;
}

void Client::Command(COMMAND command)
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
		throw Exception::SMTP_UNDEF_COMM("specifying a command");
		break;
	}
}

// A simple string match
bool Client::IsCommandSupported(const string& response, const string& command) const
{
	if (response.find(command) == string::npos)
		return false;
	else
		return true;
}

int Client::SmtpXYZdigits() const
{
	if (RecvBuf.empty())
		return 0;
	return (RecvBuf[0] - '0') * 100 + (RecvBuf[1] - '0') * 10 + RecvBuf[2] - '0';
}

void Client::Handshake()
{
	DEBUG_LOG(1, "SMTP Handshake");
	Client::Command(INIT);
	Client::Command(EHLO);
}

void Client::Starttls()
{
	DEBUG_LOG(3, "Sending STARTTLS command");
	SendBuf = "STARTTLS\r\n";
	SecureSocks::Send();
	SecureSocks::Receive();

	if (!isRetCodeValid(220))
		throw Exception::STARTTLS_FAILED("attempt to set up tls over SMTP");
}
void Client::Ehlo()
{
	DEBUG_LOG(3, "Sending EHLO command");
	SendBuf = "EHLO ";
	SendBuf += m_sLocalHostName.empty() ? "localhost" : m_sLocalHostName;
	SendBuf += "\r\n";

	SecureSocks::Send();
	SecureSocks::Receive();

	if (!isRetCodeValid(250))
		throw Exception::EHLO_FAILED("server return error after EHLO command");
}

void Client::SetUpSSL()
{
	DEBUG_LOG(2, "Setting up SSL over ESMTP");
	SecureSocks::Connect(host, port);
	DEBUG_LOG(2, "Successfuly set up SSL over ESMTP connection");
}

void Client::SetUpTLS()
{
	DEBUG_LOG(2, "Setting up TLS over ESMTP");
	if (IsCommandSupported(RecvBuf, "STARTTLS") == false)
	{
		throw Exception::STARTTLS_NOT_SUPPORTED("attempt to set up TLS over ESMTP");
	}

	Command(STARTTLS);
	SecureSocks::Connect(host, port);

	Command(EHLO);

	DEBUG_LOG(2, "Successfuly set up TLS over ESMTP connection");
}

void Client::Connect(const string& host, unsigned short port)
{
	DEBUG_LOG(1, "ESMTPS Connecting");
	Raw::Connect(host, port);

	if (sec == Security::Encryption::Type::SSL)
	{
		SetUpSSL();
	}

	Handshake();

	if (sec == Security::Encryption::Type::TLS)
	{
		SetUpTLS();
	}

	Auth();
}

void Client::Send(MAIL* m)
{
	mail = m;
	Client::Command(MAILFROM);
	Client::Command(RCPTTO);
	DEBUG_LOG(1, "Start SMTP transaction");
	Client::Command(DATA);
	Client::Command(DATABLOCK);
	Client::Command(DATAEND);
	DEBUG_LOG(1, "Success SMTP transaction");
	mail = nullptr;
}



void Client::SetAuth(const string& login, const string& pass)
{
	credentials.login = login;
	credentials.password = pass;
}

void Client::Auth()
{
	DEBUG_LOG(3, "Choosing authentication");
	if (IsCommandSupported(RecvBuf, "AUTH"))
	{
		if (!credentials.login.size())
			throw Exception::UNDEF_LOGIN("SMTP authentication selection");

		if (!credentials.password.size())
			throw Exception::UNDEF_PASSWORD("SMTP authentication selection");

		if (IsCommandSupported(RecvBuf, "LOGIN") == true)
		{
			Command(AUTHLOGIN);
		}
		else if (IsCommandSupported(RecvBuf, "PLAIN") == true)
		{
			Command(AUTHPLAIN);
		}
		else if (IsCommandSupported(RecvBuf, "CRAM-MD5") == true)
		{
			Command(AUTHCRAMMD5);
		}
		else if (IsCommandSupported(RecvBuf, "DIGEST-MD5") == true)
		{
			Command(AUTHDIGESTMD5);
		}
		else
		{
			throw Exception::AUTH_NOT_SUPPORTED("SMTP authentication selection");
		}
	}
	else
	{
		throw Exception::AUTH_NOT_SUPPORTED("SMTP authentication selection");
	}
}

void Client::AuthPlain()
{
	DEBUG_LOG(2, "Authentication AUTH PLAIN");

	SendBuf = "AUTH PLAIN " + Auth::Plain(credentials.login, credentials.password) + "\r\n";

	Client::SecureSocks::Send();
	Client::SecureSocks::Receive();

	if (!isRetCodeValid(235))
		throw Exception::AUTH_PLAIN_FAILED("SMTP Plain authentication");
}

void Client::AuthLogin()
{
	DEBUG_LOG(2, "Authentication AUTH LOGIN");
	SendBuf = "AUTH LOGIN\r\n";
	Client::SecureSocks::Send();
	Client::SecureSocks::Receive();

	if (!isRetCodeValid(334))
		throw Exception::AUTH_LOGIN_FAILED("SMTP LOGIN authentication");

	DEBUG_LOG(3, "Sending login");
	string encoded_login = Auth::Login(credentials.login);
	SendBuf = encoded_login + "\r\n";
	Client::SecureSocks::Send();
	Client::SecureSocks::Receive();

	if (!isRetCodeValid(334))
		throw Exception::UNDEF_XYZ_RESPONSE("SMTP LOGIN authentication");

	DEBUG_LOG(3, "Sending password");
	string encoded_password = Auth::Login(credentials.password);
	SendBuf = encoded_password + "\r\n";
	Client::SecureSocks::Send();
	Client::SecureSocks::Receive();

	if (!isRetCodeValid(235))
	{
		throw Exception::BAD_LOGIN_PASS("SMTP LOGIN authentication");
	}
}

void Client::CramMD5()
{
	DEBUG_LOG(2, "Authentication AUTH CRAM-MD5");
	SendBuf = "AUTH CRAM-MD5\r\n";
	Client::SecureSocks::Send();
	Client::SecureSocks::Receive();

	if (!isRetCodeValid(334))
		throw Exception::AUTH_CRAMMD5_FAILED("SMTP CRAM-MD5 authentication");

	DEBUG_LOG(3, "Token generation");

	string encoded_challenge = Auth::CramMD5(RecvBuf.substr(4), credentials.login, credentials.password);

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(1, "Token sending " + encoded_challenge);

	Client::SecureSocks::Send();
	Client::SecureSocks::Receive();

	if (!isRetCodeValid(334))
		throw Exception::AUTH_CRAMMD5_FAILED("SMTP CRAM-MD5 authentication");
}

void Client::DigestMD5()
{
	DEBUG_LOG(2, "Authentication AUTH DIGEST-MD5");
	SendBuf = "AUTH DIGEST-MD5\r\n";
	Client::SecureSocks::Send();
	Client::SecureSocks::Receive();

	if (!isRetCodeValid(335))
		throw Exception::DIGESTMD5_FAILED("SMTP DIGEST-MD5 authentication");

	DEBUG_LOG(3, "Token generation");

	const string charset = RecvBuf.find("charset") != std::string::npos ?
		"charset=utf-8," : "";
	const string addr = host + ":" + CORE::UTILS::to_string(port);

	string encoded_challenge = Auth::DigestMD5(RecvBuf.substr(4), charset, addr, credentials.login, credentials.password);

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(3, "Token sending " + encoded_challenge);

	Client::SecureSocks::Send();
	Client::SecureSocks::Receive();

	if (!isRetCodeValid(335))
		throw Exception::DIGESTMD5_FAILED("SMTP DIGEST-MD5 authentication");

	// only completion carraige needed for end digest md5 auth
	SendBuf = "\r\n";

	Client::SecureSocks::Send();
	Client::SecureSocks::Receive();

	if (!isRetCodeValid(335))
		throw Exception::DIGESTMD5_FAILED("SMTP DIGEST-MD5 authentication");
}
