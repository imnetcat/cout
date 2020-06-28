#include "esmtpsa.h"
#include "../../core/exception.h"
#include "../../core/filesystem/explorer.h"
#include "../../algorithm/base64.h"
#include "../../core/utils.h"
#include "../../core/config.h"
#include "../authentication/method.h"
#include "mail/mail.h"
#include "exceptions.h"
using namespace std;
using namespace Protocol::SMTP;

ESMTPSA::ESMTPSA() : pendingTransaction(false), Secured(), m_sLocalHostName(GetLocalName())
{
	DEBUG_LOG(3, "Initializing ESMTPSA protocol");
}

ESMTPSA::~ESMTPSA()
{
	if (isConnected) 
		this->Disconnect();
}

void ESMTPSA::Send()
{
	Secured::Send();
}

void ESMTPSA::Receive()
{
	Secured::Receive();
}

void ESMTPSA::Init()
{
	DEBUG_LOG(2, "Initializing SMTP protocol");
	this->Receive();

	if (isRetCodeValid(500))
		throw Exceptions::SMTP::command_not_recognized("The server uses an outdated specification and does not support extensions");

	if (!isRetCodeValid(220))
		throw Exceptions::Core::server_not_responding("SMTP init");
}

void ESMTPSA::Disconnect()
{
	DEBUG_LOG(2, "SMTP Disconnecting");
	if (isConnected)
	{
		this->Command(QUIT);
	}
	Secured::Disconnect();
}

void ESMTPSA::Quit()
{
	DEBUG_LOG(3, "Sending QUIT command");
	if (pendingTransaction)
	{
		// close pending transaction first
		SendBuf = "\r\n.\r\n";
		this->Send();
		this->Receive();
	}
	SendBuf = "QUIT\r\n";
	this->Send();
	this->Receive();

	if (!isRetCodeValid(221))
		throw Exceptions::SMTP::QUIT_FAILED("sending QUIT command");
}

void ESMTPSA::MailFrom()
{
	DEBUG_LOG(3, "Sending MAIL FROM command");
	if (!mail->GetMailFrom().size())
		throw Exceptions::SMTP::UNDEF_MAIL_FROM("sending MAIL FROM command");

	SendBuf = "MAIL FROM:<" + mail->GetMailFrom() + ">\r\n";

	this->Send();
	this->Receive();

	if (!isRetCodeValid(250))
		throw Exceptions::SMTP::MAIL_FROM_FAILED("sending MAIL FROM command");
}

void ESMTPSA::RCPTto()
{
	DEBUG_LOG(3, "Sending RCPT TO command");
	if (!mail->GetRecipientCount())
		throw Exceptions::SMTP::UNDEF_RECIPIENTS("sending RCPT TO command");

	const auto& recipients = mail->GetRecipient();
	for (const auto& [mail, name] : recipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail + ">\r\n";

		this->Send();
		this->Receive();

		if (!isRetCodeValid(250))
			throw Exceptions::SMTP::RCPT_TO_FAILED("sending recipients by RCPT TO command");
	}

	const auto& ccrecipients = mail->GetCCRecipient();
	for (const auto& [mail, name] : ccrecipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail + ">\r\n";

		this->Send();
		this->Receive();

		if (!isRetCodeValid(250))
			throw Exceptions::SMTP::RCPT_TO_FAILED("sending ccrecipients by RCPT TO command");
	}

	const auto& bccrecipients = mail->GetBCCRecipient();
	for (const auto& [mail, name] : bccrecipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail + ">\r\n";

		this->Send();
		this->Receive();

		if (!isRetCodeValid(250))
			throw Exceptions::SMTP::RCPT_TO_FAILED("sending bccrecipients by RCPT TO command");
	}
}

void ESMTPSA::Data()
{
	DEBUG_LOG(3, "Sending DATA command");
	SendBuf = "DATA\r\n";
	this->Send();
	this->Receive();

	if (!isRetCodeValid(354))
		throw Exceptions::SMTP::DATA_FAILED("sending DATA command");
}

void ESMTPSA::Datablock()
{
	DEBUG_LOG(2, "Sending mail header");
	SendBuf = mail->createHeader();
	this->Send();

	DEBUG_LOG(2, "Sending mail body");

	if (!mail->GetBodySize())
	{
		SendBuf = " \r\n";
		this->Send();
	}

	const auto& body = mail->GetBody();
	for (const auto& line : body)
	{
		SendBuf = line + "\r\n";
		this->Send();
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

		Core::Filesystem::Explorer explorer;

		if (!explorer.exist(path))
			throw Exceptions::Core::file_not_exist("SMTP attachment file not found");

		DEBUG_LOG(3, "Checking file size");

		FileSize = explorer.size(path);
		TotalSize += FileSize;

		if (TotalSize / 1024 > MSG_SIZE_IN_MB * 1024)
			throw Exceptions::SMTP::MSG_TOO_BIG("SMTP attachment files are too large");

		DEBUG_LOG(3, "Sending file header");

		pos = path.find_last_of("\\");
		if (pos == string::npos) FileName = path;
		else FileName = path.substr(pos + 1);

		//RFC 2047 - Use UTF-8 charset,base64 encode.
		EncodedFileName = "=?UTF-8?B?";
		EncodedFileName += Core::Base64::Encode((unsigned char *)FileName.c_str(), FileName.size());
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

		this->Send();

		DEBUG_LOG(3, "Sending file body");

		MsgPart = 0;
		explorer.read(path, 54, [&MsgPart, this] (vector<Core::Filesystem::Byte> block) mutable {
			MsgPart ? SendBuf += Core::Base64::Encode(reinterpret_cast<const unsigned char*>(block.data()), block.size())
				: SendBuf = Core::Base64::Encode(reinterpret_cast<const unsigned char*>(block.data()), block.size());
			SendBuf += "\r\n";
			MsgPart += block.size() + 2ull;
			if (MsgPart >= BUFFER_SIZE / 2)
			{
				// sending part of the message
				MsgPart = 0;
				this->Send();
			}
		});
		if (MsgPart)
		{
			this->Send();
		}
	}

	if (mail->GetAttachmentsSize())
	{
		SendBuf = "\r\n--" + MAIL::BOUNDARY_TEXT + "--\r\n";
		this->Send();
	}
}

void ESMTPSA::DataEnd()
{
	DEBUG_LOG(3, "Sending the CRLF");
	// <CRLF> . <CRLF>
	SendBuf = "\r\n.\r\n";
	this->Send();
	this->Receive();

	if (!isRetCodeValid(250))
		throw Exceptions::SMTP::MSG_BODY_ERROR("wrong letter format");
}

const string& ESMTPSA::GetLogin() const noexcept
{
	return credentials.login;
}
const string& ESMTPSA::GetPassword() const noexcept
{
	return credentials.password;
}

void ESMTPSA::SetLogin(const string& login)
{
	credentials.login = login;
}

void ESMTPSA::SetPassword(const string& pass)
{
	credentials.password = pass;
}

bool ESMTPSA::isRetCodeValid(int validCode) const
{
	if (!RecvBuf.size())
		return false;

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

void ESMTPSA::Command(COMMAND command)
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
		throw Exceptions::SMTP::SMTP_UNDEF_COMM("specifying a command");
		break;
	}
}

// A simple string match
bool ESMTPSA::IsCommandSupported(const string& response, const string& command) const
{
	if (response.find(command) == string::npos)
		return false;
	else
		return true;
}

int ESMTPSA::SmtpXYZdigits() const
{
	if (RecvBuf.empty())
		return 0;
	return (RecvBuf[0] - '0') * 100 + (RecvBuf[1] - '0') * 10 + RecvBuf[2] - '0';
}

void ESMTPSA::Handshake()
{
	DEBUG_LOG(1, "SMTP Handshake");
	this->Command(INIT);
	this->Command(EHLO);
}

void ESMTPSA::Starttls()
{
	DEBUG_LOG(3, "Sending STARTTLS command");
	SendBuf = "STARTTLS\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(220))
		throw Exceptions::SMTP::STARTTLS_FAILED("attempt to set up tls over SMTP");
}
void ESMTPSA::Ehlo()
{
	DEBUG_LOG(3, "Sending EHLO command");
	SendBuf = "EHLO ";
	SendBuf += m_sLocalHostName.empty() ? "localhost" : m_sLocalHostName;
	SendBuf += "\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(250))
		throw Exceptions::SMTP::EHLO_FAILED("server return error after EHLO command");
}

void ESMTPSA::SetUpSSL()
{
	DEBUG_LOG(2, "Setting up SSL over ESMTP");
	Secured::SetUp();
	DEBUG_LOG(2, "Successfuly set up SSL over ESMTP connection");
}

void ESMTPSA::SetUpTLS()
{
	DEBUG_LOG(2, "Setting up TLS over ESMTP");
	if (IsCommandSupported(RecvBuf, "STARTTLS") == false)
	{
		throw Exceptions::SMTP::STARTTLS_NOT_SUPPORTED("attempt to set up TLS over ESMTP");
	}

	Command(STARTTLS);
	Secured::SetUp();

	Command(EHLO);

	DEBUG_LOG(2, "Successfuly set up TLS over ESMTP connection");
}

void ESMTPSA::Connect(const string& host, unsigned short port)
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


void ESMTPSA::Send(MAIL* m)
{
	mail = m;
	this->Command(MAILFROM);
	this->Command(RCPTTO);
	this->Command(DATA);
	DEBUG_LOG(1, "Start SMTP transaction");
	pendingTransaction = true;
	this->Command(DATABLOCK);
	this->Command(DATAEND);
	pendingTransaction = false;
	DEBUG_LOG(1, "Success SMTP transaction");
	mail = nullptr;
}

void ESMTPSA::Auth()
{
	DEBUG_LOG(3, "Choosing authentication");
	if (IsCommandSupported(RecvBuf, "AUTH"))
	{
		if (!credentials.login.size())
			throw Exceptions::SMTP::UNDEF_LOGIN("SMTP authentication selection");

		if (!credentials.password.size())
			throw Exceptions::SMTP::UNDEF_PASSWORD("SMTP authentication selection");

		if (IsCommandSupported(RecvBuf, "LOGIN") == true)
		{
			this->Command(AUTHLOGIN);
		}
		else if (IsCommandSupported(RecvBuf, "PLAIN") == true)
		{
			this->Command(AUTHPLAIN);
		}
		else if (IsCommandSupported(RecvBuf, "CRAM-MD5") == true)
		{
			this->Command(AUTHCRAMMD5);
		}
		else if (IsCommandSupported(RecvBuf, "DIGEST-MD5") == true)
		{
			this->Command(AUTHDIGESTMD5);
		}
		else
		{
			throw Exceptions::SMTP::AUTH_NOT_SUPPORTED("SMTP authentication selection");
		}
	}
	else
	{
		throw Exceptions::SMTP::AUTH_NOT_SUPPORTED("SMTP authentication selection");
	}
}

void ESMTPSA::AuthPlain()
{
	DEBUG_LOG(2, "Authentication AUTH PLAIN");

	SendBuf = "AUTH PLAIN " + Authentication::Method::Plain(credentials.login, credentials.password) + "\r\n";

	this->Send();
	this->Receive();

	if (!isRetCodeValid(235))
		throw Exceptions::SMTP::AUTH_PLAIN_FAILED("SMTP Plain authentication");
}

void ESMTPSA::AuthLogin()
{
	DEBUG_LOG(2, "Authentication AUTH LOGIN");
	SendBuf = "AUTH LOGIN\r\n";
	this->Send();
	this->Receive();

	if (!isRetCodeValid(334))
		throw Exceptions::SMTP::AUTH_LOGIN_FAILED("SMTP LOGIN authentication");

	DEBUG_LOG(3, "Sending login");
	string encoded_login = Authentication::Method::Login(credentials.login);
	SendBuf = encoded_login + "\r\n";
	this->Send();
	this->Receive();

	if (!isRetCodeValid(334))
		throw Exceptions::SMTP::UNDEF_XYZ_RESPONSE("SMTP LOGIN authentication");

	DEBUG_LOG(3, "Sending password");
	string encoded_password = Authentication::Method::Login(credentials.password);
	SendBuf = encoded_password + "\r\n";
	this->Send();
	this->Receive();

	if (!isRetCodeValid(235))
	{
		throw Exceptions::SMTP::BAD_LOGIN_PASS("SMTP LOGIN authentication");
	}
}

void ESMTPSA::CramMD5()
{
	DEBUG_LOG(2, "Authentication AUTH CRAM-MD5");
	SendBuf = "AUTH CRAM-MD5\r\n";
	this->Send();
	this->Receive();

	if (!isRetCodeValid(334))
		throw Exceptions::SMTP::AUTH_CRAMMD5_FAILED("SMTP CRAM-MD5 authentication");

	DEBUG_LOG(3, "Token generation");

	string encoded_challenge = Authentication::Method::CramMD5(RecvBuf.substr(4), credentials.login, credentials.password);

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(1, "Token sending " + encoded_challenge);

	this->Send();
	this->Receive();

	if (!isRetCodeValid(334))
		throw Exceptions::SMTP::AUTH_CRAMMD5_FAILED("SMTP CRAM-MD5 authentication");
}

void ESMTPSA::DigestMD5()
{
	DEBUG_LOG(2, "Authentication AUTH DIGEST-MD5");
	SendBuf = "AUTH DIGEST-MD5\r\n";
	this->Send();
	this->Receive();

	if (!isRetCodeValid(335))
		throw Exceptions::SMTP::DIGESTMD5_FAILED("SMTP DIGEST-MD5 authentication");

	DEBUG_LOG(3, "Token generation");

	const string charset = RecvBuf.find("charset") != std::string::npos ?
		"charset=utf-8," : "";
	const string addr = Core::Utils::to_string(host) + ":" + Core::Utils::to_string(port);

	string encoded_challenge = Authentication::Method::DigestMD5(RecvBuf.substr(4), charset, addr, credentials.login, credentials.password);

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(3, "Token sending " + encoded_challenge);

	this->Send();
	this->Receive();

	if (!isRetCodeValid(335))
		throw Exceptions::SMTP::DIGESTMD5_FAILED("SMTP DIGEST-MD5 authentication");

	// only completion carraige needed for end digest md5 auth
	SendBuf = "\r\n";

	this->Send();
	this->Receive();

	if (!isRetCodeValid(335))
		throw Exceptions::SMTP::DIGESTMD5_FAILED("SMTP DIGEST-MD5 authentication");
}
