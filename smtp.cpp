#include "smtp.h"
using namespace std;
using namespace EMAIL;

SMTP::SMTP() : m_sLocalHostName(GetLocalName()) { }

SMTP::~SMTP()
{
	if (isConnected) SMTP::Disconnect();
}

void SMTP::Init()
{
	DEBUG_LOG(2, "Initializing SMTP protocol");
	SMTP::Receive();

	if (!isRetCodeValid(220))
		throw CORE::Exception::server_not_responding("SMTP init");
}

void SMTP::Disconnect()
{
	DEBUG_LOG(2, "SMTP Disconnecting");
	if (isConnected)
	{
		SMTP::Command(QUIT);
	}
	Socket::Disconnect();
}

void SMTP::Helo()
{
	DEBUG_LOG(3, "Sending HELO command");
	SendBuf = "HELO ";
	SendBuf += m_sLocalHostName.empty() ? "localhost" : m_sLocalHostName;
	SendBuf += "\r\n";

	SMTP::Send();
	SMTP::Receive();

	if (!isRetCodeValid(250))
		throw Exception::HELO_FAILED("sending HELO command");
}

void SMTP::Quit()
{
	DEBUG_LOG(3, "Sending QUIT command");
	SendBuf = "QUIT\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(221))
		throw Exception::QUIT_FAILED("sending QUIT command");
}

void SMTP::MailFrom()
{
	DEBUG_LOG(3, "Sending MAIL FROM command");
	if (!mail.GetMailFrom().size())
		throw Exception::UNDEF_MAIL_FROM("sending MAIL FROM command");

	SendBuf = "MAIL FROM:<" + mail.GetMailFrom() + ">\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(250))
		throw Exception::MAIL_FROM_FAILED("sending MAIL FROM command");
}

void SMTP::RCPTto()
{
	DEBUG_LOG(3, "Sending RCPT TO command");
	if (!mail.GetRecipientCount())
		throw Exception::UNDEF_RECIPIENTS("sending RCPT TO command");

	const auto& recipients = mail.GetRecipient();
	for (const auto& [mail, name] : recipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail + ">\r\n";

		Send();
		Receive();

		if (!isRetCodeValid(250))
			throw Exception::RCPT_TO_FAILED("sending recipients by RCPT TO command");
	}

	const auto& ccrecipients = mail.GetCCRecipient();
	for (const auto& [mail, name] : ccrecipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail + ">\r\n";

		Send();
		Receive();

		if (!isRetCodeValid(250))
			throw Exception::RCPT_TO_FAILED("sending ccrecipients by RCPT TO command");
	}

	const auto& bccrecipients = mail.GetBCCRecipient();
	for (const auto& [mail, name] : bccrecipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail + ">\r\n";

		Send();
		Receive();

		if (!isRetCodeValid(250))
			throw Exception::RCPT_TO_FAILED("sending bccrecipients by RCPT TO command");
	}
}

void SMTP::Data()
{
	DEBUG_LOG(3, "Sending DATA command");
	SendBuf = "DATA\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(354))
		throw Exception::DATA_FAILED("sending DATA command");
}

void SMTP::Datablock()
{
	DEBUG_LOG(2, "Sending mail header");
	SendBuf = mail.createHeader();
	Send();

	DEBUG_LOG(2, "Sending mail body");

	if (!mail.GetBodySize())
	{
		SendBuf = " \r\n";
		Send();
	}

	const auto& body = mail.GetBody();
	for (const auto& line : body)
	{
		SendBuf = line + "\r\n";
		Send();
	}

	const auto& attachments = mail.GetAttachments();
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

		Send();

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
				Send();
			}
		}
		if (MsgPart)
		{
			Send();
		}
		file.close();
	}

	if (mail.GetAttachmentsSize())
	{
		SendBuf = "\r\n--" + MAIL::BOUNDARY_TEXT + "--\r\n";
		Send();
	}
}

void SMTP::DataEnd()
{
	DEBUG_LOG(3, "Sending the CRLF");
	// <CRLF> . <CRLF>
	SendBuf = "\r\n.\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(250))
		throw Exception::MSG_BODY_ERROR("wrong letter format");
}

bool SMTP::isRetCodeValid(int validCode) const
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

void SMTP::Command(COMMAND command)
{
	switch (command)
	{
	case INIT:
		Init();
		break;
	case HELO:
		Helo();
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
	case QUIT:
		Quit();
		break;
	default:
		throw Exception::SMTP_UNDEF_COMM("specifying a command");
		break;
	}
}

// A simple string match
bool SMTP::IsCommandSupported(const string& response, const string& command) const
{
	if (response.find(command) == string::npos)
		return false;
	else
		return true;
}

int SMTP::SmtpXYZdigits() const
{
	if (RecvBuf.empty())
		return 0;
	return (RecvBuf[0] - '0') * 100 + (RecvBuf[1] - '0') * 10 + RecvBuf[2] - '0';
}

void SMTP::Handshake()
{
	DEBUG_LOG(1, "SMTP Handshake");
	SMTP::Command(INIT);
	SMTP::Command(HELO);
}

void SMTP::Connect(const string& name, unsigned short port)
{
	DEBUG_LOG(1, "SMTP Connecting");
	Socket::Connect(name, port);
	SMTP::Handshake();
}

void SMTP::SendMail(const MAIL& m)
{
	mail = m;
	SMTP::Command(MAILFROM);
	SMTP::Command(RCPTTO);
	DEBUG_LOG(1, "Start SMTP transaction");
	SMTP::Command(DATA);
	SMTP::Command(DATABLOCK);
	SMTP::Command(DATAEND);
	DEBUG_LOG(1, "Success SMTP transaction");
}

