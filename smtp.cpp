#include "smtp.h"
using namespace std;

SMTP::SMTP() { }

SMTP::~SMTP()
{
	if (server.isConnected) Disconnect();
}

const std::string SMTP::BOUNDARY_TEXT = "__MESSAGE__ID__54yg6f6h6y456345";

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
	if (!mail.senderMail.size())
		throw CORE::UNDEF_MAIL_FROM;

	SendBuf = "MAIL FROM:<" + mail.senderMail + ">\r\n";

	Send();
	Receive();

	if (!isRetCodeValid(250))
		throw CORE::MAIL_FROM_FAILED;
}

void SMTP::RCPTto()
{
	DEBUG_LOG(1, "Устанавливаем получателей");
	if (!mail.recipients.size())
		throw CORE::UNDEF_RECIPIENTS;

	while (mail.recipients.size())
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail.recipients.at(0).Mail + ">\r\n";

		Send();
		Receive();

		if (!isRetCodeValid(250))
			throw CORE::RCPT_TO_FAILED;

		mail.recipients.erase(mail.recipients.begin());
	}

	while (mail.ccrecipients.size())
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail.ccrecipients.at(0).Mail + ">\r\n";

		Send();
		Receive();

		if (!isRetCodeValid(250))
			throw CORE::RCPT_TO_FAILED;
		mail.ccrecipients.erase(mail.ccrecipients.begin());
	}

	while (mail.bccrecipients.size())
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail.bccrecipients.at(0).Mail + ">\r\n";

		Send();
		Receive();

		if (!isRetCodeValid(250))
			throw CORE::RCPT_TO_FAILED;
		mail.bccrecipients.erase(mail.bccrecipients.begin());
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
	SendBuf = mail.header;
	Send();

	DEBUG_LOG(1, "Отправка тела письма");

	if (!mail.body.size())
	{
		SendBuf = " \r\n";
		Send();
	}

	while (mail.body.size())
	{
		SendBuf = mail.body[0] + "\r\n";
		mail.body.erase(mail.body.begin());

		Send();
	}

	DEBUG_LOG(1, "Отправка прикриплённых файлов, если есть");
	bool isAttachmentsExist = mail.attachments.size();
	while (mail.attachments.size())
	{
		DEBUG_LOG(1, "Отправка прикриплённого файла");
		unsigned long long FileSize, TotalSize;
		unsigned long long MsgPart;
		string FileName, EncodedFileName;
		string::size_type pos;
				
		TotalSize = 0;
		DEBUG_LOG(1, "Проверяем существует ли файл");

		if(!CORE::Filesystem::file::exist(mail.attachments[0]))
			throw CORE::FILE_NOT_EXIST;

		DEBUG_LOG(1, "Проверяем размер файла");

		FileSize = CORE::Filesystem::file::size(mail.attachments[0]);
		TotalSize += FileSize;

		if (TotalSize / 1024 > MSG_SIZE_IN_MB * 1024)
			throw CORE::MSG_TOO_BIG;

		DEBUG_LOG(1, "Отправляем заголовок файла");
	
		pos = mail.attachments[0].find_last_of("\\");
		if (pos == string::npos) FileName = mail.attachments[0];
		else FileName = mail.attachments[0].substr(pos + 1);

		//RFC 2047 - Use UTF-8 charset,base64 encode.
		EncodedFileName = "=?UTF-8?B?";
		EncodedFileName += CORE::BASE64::base64_encode((unsigned char *)FileName.c_str(), FileName.size());
		EncodedFileName += "?=";

		SendBuf = "--" + BOUNDARY_TEXT + "\r\n";
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
		
		CORE::File file(mail.attachments[0]);

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
		
		mail.attachments.erase(mail.attachments.begin());
	}

	if (isAttachmentsExist)
	{
		SendBuf = "\r\n--" + BOUNDARY_TEXT + "--\r\n";
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

void SMTP::createHeader()
{
	char month[][4] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
	size_t i;
	stringstream to;
	stringstream cc;
	stringstream bcc;
	stringstream sheader;
	time_t rawtime;
	struct tm* timeinfo = nullptr;

	// date/time check
	if (time(&rawtime) > 0)
		localtime_s(timeinfo, &rawtime);
	else
		throw CORE::TIME_ERROR;

	// check for at least one recipient
	if (mail.recipients.size())
	{
		for (i = 0; i < mail.recipients.size(); i++)
		{
			if (i > 0)
				to << ',';
			to << mail.recipients[i].Name;
			to << '<';
			to << mail.recipients[i].Mail;
			to << '>';
		}
	}
	else
		throw CORE::UNDEF_RECIPIENTS;

	if (mail.ccrecipients.size())
	{
		for (i = 0; i < mail.ccrecipients.size(); i++)
		{
			if (i > 0)
				cc << ',';
			cc << mail.ccrecipients[i].Name;
			cc << '<';
			cc << mail.ccrecipients[i].Mail;
			cc << '>';
		}
	}

	if (mail.bccrecipients.size())
	{
		for (i = 0; i < mail.bccrecipients.size(); i++)
		{
			if (i > 0)
				bcc << ',';
			bcc << mail.bccrecipients[i].Name;
			bcc << '<';
			bcc << mail.bccrecipients[i].Mail;
			bcc << '>';
		}
	}

	// Date: <SP> <dd> <SP> <mon> <SP> <yy> <SP> <hh> ":" <mm> ":" <ss> <SP> <zone> <CRLF>
	sheader << "Date: " <<
		timeinfo->tm_mday << " " <<
		month[timeinfo->tm_mon] << " " <<
		timeinfo->tm_year + 1900 << " " <<
		timeinfo->tm_hour << ":" <<
		timeinfo->tm_min << ":" <<
		timeinfo->tm_sec << "\r\n";
	// From: <SP> <sender>  <SP> "<" <sender-email> ">" <CRLF>
	if (!mail.senderMail.size())
		throw CORE::UNDEF_MAIL_FROM;

	sheader << "From: ";
	if (mail.senderName.size()) sheader << mail.senderName;

	sheader << " <";
	sheader << mail.senderMail;
	sheader << ">\r\n";

	// X-Mailer: <SP> <xmailer-app> <CRLF>
	if (mail.mailer.size())
	{
		sheader << "X-Mailer: ";
		sheader << mail.mailer;
		sheader << "\r\n";
	}

	// Reply-To: <SP> <reverse-path> <CRLF>
	if (mail.replyTo.size())
	{
		sheader << "Reply-To: ";
		sheader << mail.replyTo;
		sheader << "\r\n";
	}

	// Disposition-Notification-To: <SP> <reverse-path or sender-email> <CRLF>
	if (mail.readReceipt)
	{
		sheader << "Disposition-Notification-To: ";
		if (mail.replyTo.size()) sheader << mail.replyTo;
		else sheader << mail.senderName;
		sheader << "\r\n";
	}

	// X-Priority: <SP> <number> <CRLF>
	switch (mail.priority)
	{
	case SMTP::MAIL::PRIORITY::HIGH:
		sheader << "X-Priority: 2 (High)\r\n";
		break;
	case SMTP::MAIL::PRIORITY::NORMAL:
		sheader << "X-Priority: 3 (Normal)\r\n";
		break;
	case SMTP::MAIL::PRIORITY::LOW:
		sheader << "X-Priority: 4 (Low)\r\n";
		break;
	default:
		sheader << "X-Priority: 3 (Normal)\r\n";
	}

	// To: <SP> <remote-user-mail> <CRLF>
	sheader << "To: ";
	sheader << to.str();
	sheader << "\r\n";

	// Cc: <SP> <remote-user-mail> <CRLF>
	if (mail.ccrecipients.size())
	{
		sheader << "Cc: ";
		sheader << cc.str();
		sheader << "\r\n";
	}

	if (mail.bccrecipients.size())
	{
		sheader << "Bcc: ";
		sheader << bcc.str();
		sheader << "\r\n";
	}

	// Subject: <SP> <subject-text> <CRLF>
	if (!mail.subject.size())
		sheader << "Subject:  ";
	else
	{
		sheader << "Subject: ";
		sheader << mail.subject;
	}
	sheader << "\r\n";

	// MIME-Version: <SP> 1.0 <CRLF>
	sheader << "MIME-Version: 1.0\r\n";
	if (!mail.attachments.size())
	{ // no attachments
		if (mail.html) sheader << "Content-Type: text/html; charset=\"";
		else sheader << "Content-type: text/plain; charset=\"";
		sheader << mail.charSet;
		sheader << "\"\r\n";
		sheader << "Content-Transfer-Encoding: 7bit\r\n";
		sheader << "\r\n";
	}
	else
	{ // there is one or more attachments
		sheader << "Content-Type: multipart/mixed; boundary=\"";
		sheader << SMTP::BOUNDARY_TEXT;
		sheader << "\"\r\n";
		sheader << "\r\n";
		// first goes text message
		sheader << "--";
		sheader << SMTP::BOUNDARY_TEXT;
		sheader << "\r\n";
		if (mail.html) sheader << "Content-type: text/html; charset=";
		else sheader << "Content-type: text/plain; charset=";
		sheader << mail.charSet;
		sheader << "\r\n";
		sheader << "Content-Transfer-Encoding: 7bit\r\n";
		sheader << "\r\n";
	}

	sheader << '\0';

	mail.header = sheader.str();
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
	createHeader();
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
