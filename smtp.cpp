#include "smtp.h"
using namespace std;
using namespace EMAIL;

SMTP::SMTP() { }

SMTP::~SMTP()
{
	if (server.isConnected) Disconnect();
}

void SMTP::Init()
{
	DEBUG_LOG(1, "Инициализация протокола smtp");
	Receive();

	if (!isRetCodeValid(220))
		throw CORE::SERVER_NOT_RESPONDING;
}

void SMTP::Disconnect()
{
	if (server.isConnected) Command(QUIT);
	Raw::Disconnect();
}

void SMTP::Helo()
{
	DEBUG_LOG(1, "Отправка EHLO комманды");
	SendBuf = "HELO ";
	SendBuf += m_sLocalHostName.empty() ? "localhost" : m_sLocalHostName;
	SendBuf += "\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(250))
		throw CORE::HELO_FAILED;
}

void SMTP::Quit()
{
	DEBUG_LOG(1, "Завершение соеденения по протоколу smtp");
	SendBuf = "QUIT\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(221))
		throw CORE::QUIT_FAILED;
}

void SMTP::MailFrom()
{
	DEBUG_LOG(1, "Устанавливаем отправителя");
	if (!mail.GetMailFrom().size())
		throw CORE::UNDEF_MAIL_FROM;

	SendBuf = "MAIL FROM:<" + mail.GetMailFrom() + ">\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(250))
		throw CORE::MAIL_FROM_FAILED;
}

void SMTP::RCPTto()
{
	DEBUG_LOG(1, "Устанавливаем получателей");
	if (!mail.GetRecipientCount())
		throw CORE::UNDEF_RECIPIENTS;

	const auto& recipients = mail.GetRecipient();
	for (const auto& r : recipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + r.Mail + ">\r\n";

		Send();
		Receive();

		if (!isRetCodeValid(250))
			throw CORE::RCPT_TO_FAILED;
	}

	const auto& ccrecipients = mail.GetCCRecipient();
	for (const auto& r : ccrecipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + r.Mail + ">\r\n";

		Send();
		Receive();

		if (!isRetCodeValid(250))
			throw CORE::RCPT_TO_FAILED;
	}

	const auto& bccrecipients = mail.GetBCCRecipient();
	for (const auto& r : bccrecipients)
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + r.Mail + ">\r\n";

		Send();
		Receive();

		if (!isRetCodeValid(250))
			throw CORE::RCPT_TO_FAILED;
	}
}

void SMTP::Data()
{
	DEBUG_LOG(1, "Начало smtp транзакции");
	SendBuf = "DATA\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(354))
		throw CORE::DATA_FAILED;
}

void SMTP::Datablock()
{
	DEBUG_LOG(1, "Отправка заголовков письма");
	SendBuf = mail.createHeader();
	Send();

	DEBUG_LOG(1, "Отправка тела письма");

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
		DEBUG_LOG(1, "Отправка прикриплённого файла");
		unsigned long long FileSize, TotalSize;
		unsigned long long MsgPart;
		string FileName, EncodedFileName;
		string::size_type pos;
				
		TotalSize = 0;
		DEBUG_LOG(1, "Проверяем существует ли файл");

		if(!CORE::Filesystem::file::exist(path))
			throw CORE::FILE_NOT_EXIST;

		DEBUG_LOG(1, "Проверяем размер файла");

		FileSize = CORE::Filesystem::file::size(path);
		TotalSize += FileSize;

		if (TotalSize / 1024 > MSG_SIZE_IN_MB * 1024)
			throw CORE::MSG_TOO_BIG;

		DEBUG_LOG(1, "Отправляем заголовок файла");
	
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

		DEBUG_LOG(1, "Отправляем тело файла");
		
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
	DEBUG_LOG(1, "Закрываем письмо");
	// <CRLF> . <CRLF>
	SendBuf = "\r\n.\r\n";
	Send();
	Receive();

	if (!isRetCodeValid(250))
		throw CORE::MSG_BODY_ERROR;
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
		DEBUG_LOG(1, "Неизвестная комманда");
		throw CORE::SMTP_UNDEF_COMM;
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

void SMTP::SetSMTPServer(unsigned short int port, const string& name)
{
	server.port = port;
	server.name = name;
}

int SMTP::SmtpXYZdigits() const
{
	if (RecvBuf.empty())
		return 0;
	return (RecvBuf[0] - '0') * 100 + (RecvBuf[1] - '0') * 10 + RecvBuf[2] - '0';
}

void SMTP::Handshake()
{
	DEBUG_LOG(1, "Рукопожатие с сервером по протоколу SMTP");
	Command(INIT);
	Command(HELO);
}

void SMTP::Connect()
{
	Raw::Connect();
	Handshake();
}

void SMTP::SendMail(MAIL m)
{
	mail = m;
	DEBUG_LOG(1, "Отправка емейла");
	Command(MAILFROM);
	Command(RCPTTO);
	Command(DATA);
	Command(DATABLOCK);
	Command(DATAEND);
}

void SMTP::Receive()
{
	DEBUG_LOG(2, "Принимаем ответ без шифрования");
	Raw::Receive();
	DEBUG_LOG(2, "Ответ сервера принят");
}

void SMTP::Send()
{
	DEBUG_LOG(2, "Отправляем запрос без шифрования");
	Raw::Send();
	DEBUG_LOG(2, "Запрос на сервер отправлен");
}
