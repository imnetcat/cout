#include "esmtp.h"

using namespace std;

RETCODE ESMTP::Init()
{
	DEBUG_LOG(1 , "Инициализация протокола smtp");
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(220))
		return FAIL(SERVER_NOT_RESPONDING);

	return SUCCESS;
}

void ESMTP::DisconnectRemoteServer()
{
	if (server.isConnected) Command(QUIT);
	Disconnect();
}

RETCODE ESMTP::Ehlo() 
{
	DEBUG_LOG(1 , "Отправка EHLO комманды");
	SendBuf = "EHLO ";
	SendBuf += GetLocalHostName().empty() ? "localhost" : m_sLocalHostName;
	SendBuf += "\r\n";

	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(250))
		return FAIL(EHLO_FAILED);

	return SUCCESS;
}


RETCODE ESMTP::Quit()
{
	DEBUG_LOG(1 , "Завершение соеденения по протоколу smtp");
	SendBuf = "QUIT\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(221))
		return FAIL(QUIT_FAILED);

	return SUCCESS;
}
RETCODE ESMTP::MailFrom()
{
	DEBUG_LOG(1 , "Устанавливаем отправителя");
	if (!mail.senderMail.size())
		return FAIL(UNDEF_MAIL_FROM);

	SendBuf = "MAIL FROM:<" + mail.senderMail + ">\r\n";

	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(250))
		return FAIL(MAIL_FROM_FAILED);

	return SUCCESS;
}
RETCODE ESMTP::RCPTto()
{
	DEBUG_LOG(1 , "Устанавливаем получателей");
	if (!mail.recipients.size())
		return FAIL(UNDEF_RECIPIENTS);

	while (mail.recipients.size())
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail.recipients.at(0).Mail + ">\r\n";

		if (SendData(5 * 60))
			return FAIL(SMTP_SEND_DATA);
		if (ReceiveData(5 * 60))
			return FAIL(SMTP_RECV_DATA);
		if (!isRetCodeValid(250))
			return FAIL(RCPT_TO_FAILED);
		mail.recipients.erase(mail.recipients.begin());
	}

	while (mail.ccrecipients.size())
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail.ccrecipients.at(0).Mail + ">\r\n";

		if (SendData(5 * 60))
			return FAIL(SMTP_SEND_DATA);
		if (ReceiveData(5 * 60))
			return FAIL(SMTP_RECV_DATA);
		if (!isRetCodeValid(250))
			return FAIL(RCPT_TO_FAILED);
		mail.ccrecipients.erase(mail.ccrecipients.begin());
	}

	while (mail.bccrecipients.size())
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		SendBuf = "RCPT TO:<" + mail.bccrecipients.at(0).Mail + ">\r\n";

		if (SendData(5 * 60))
			return FAIL(SMTP_SEND_DATA);
		if (ReceiveData(5 * 60))
			return FAIL(SMTP_RECV_DATA);
		if (!isRetCodeValid(250))
			return FAIL(RCPT_TO_FAILED);
		mail.bccrecipients.erase(mail.bccrecipients.begin());
	}

	return SUCCESS;
}
RETCODE ESMTP::Data()
{
	DEBUG_LOG(1 , "Начало smtp транзакции");
	SendBuf = "DATA\r\n"; 
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(2 * 60))
		return FAIL(SMTP_RECV_DATA);
	if (!isRetCodeValid(354))
		return FAIL(DATA_FAILED);

	return SUCCESS;
}
RETCODE ESMTP::Datablock()
{
	DEBUG_LOG(1 , "Отправка заголовков письма");
	SendBuf = mail.header;
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);

	DEBUG_LOG(1 , "Отправка тела письма");

	if (!mail.body.size())
	{
		SendBuf = " \r\n";
		if (SendData(5 * 60))
			return FAIL(SMTP_SEND_DATA);
	}

	while (mail.body.size())
	{
		SendBuf = mail.body[0] + "\r\n";
		mail.body.erase(mail.body.begin());

		if (SendData(5 * 60))
			return FAIL(SMTP_SEND_DATA);
	}

	DEBUG_LOG(1 , "Отправка прикриплённых файлов, если есть");
	bool isAttachmentsExist = false;
	while (mail.attachments.size())
	{
		isAttachmentsExist = true;
		DEBUG_LOG(1 , "Отправка прикриплённого файла");
		unsigned int i, rcpt_count, res;
		char *FileBuf = NULL;
		FILE* hFile = NULL;
		unsigned long int FileSize, TotalSize, MsgPart;
		string FileName, EncodedFileName;
		string::size_type pos;

		//Allocate memory
		if ((FileBuf = new char[55]) == NULL)
			return FAIL(LACK_OF_MEMORY);

		TotalSize = 0;
		DEBUG_LOG(1 , "Проверяем существует ли файл");

		fopen_s(&hFile, mail.attachments[0].c_str(), "rb");
		if (hFile == NULL)
			return FAIL(FILE_NOT_EXIST);

		DEBUG_LOG(1 , "Проверяем размер файла");

		fseek(hFile, 0, SEEK_END);
		FileSize = ftell(hFile);
		TotalSize += FileSize;

		if (TotalSize / 1024 > MSG_SIZE_IN_MB * 1024)
			return FAIL(MSG_TOO_BIG);

		DEBUG_LOG(1 , "Отправляем заголовок файла");

		fclose(hFile);
		hFile = NULL;
		delete[] FileBuf;
		FileBuf = NULL;

		if ((FileBuf = new char[55]) == NULL)
			return FAIL(LACK_OF_MEMORY);

		pos = mail.attachments[0].find_last_of("\\");
		if (pos == string::npos) FileName = mail.attachments[0];
		else FileName = mail.attachments[0].substr(pos + 1);

		//RFC 2047 - Use UTF-8 charset,base64 encode.
		EncodedFileName = "=?UTF-8?B?";
		EncodedFileName += BASE64::base64_encode((unsigned char *)FileName.c_str(), FileName.size());
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

		if (SendData(3 * 60))
			return FAIL(SMTP_SEND_DATA);

		DEBUG_LOG(1 , "Отправляем тело файла");

		// opening the file:
		fopen_s(&hFile, mail.attachments[0].c_str(), "rb");

		// get file size:
		fseek(hFile, 0, SEEK_END);
		FileSize = ftell(hFile);
		fseek(hFile, 0, SEEK_SET);

		MsgPart = 0;
		for (i = 0; i < FileSize / 54 + 1; i++)
		{
			res = fread(FileBuf, sizeof(char), 54, hFile);
			MsgPart ? SendBuf += BASE64::base64_encode(reinterpret_cast<const unsigned char*>(FileBuf), res)
				: SendBuf = BASE64::base64_encode(reinterpret_cast<const unsigned char*>(FileBuf), res);
			SendBuf += "\r\n";
			MsgPart += res + 2;
			if (MsgPart >= BUFFER_SIZE / 2)
			{
				// sending part of the message
				MsgPart = 0;
				if (SendData(3 * 60))
					return FAIL(SMTP_SEND_DATA);
			}
		}
		if (MsgPart)
		{
			if (SendData(3 * 60))
				return FAIL(SMTP_SEND_DATA);
		}
		fclose(hFile);
		hFile = NULL;

		mail.attachments.erase(mail.attachments.begin());
	}

	if (isAttachmentsExist) 
	{
		SendBuf = "\r\n--" + BOUNDARY_TEXT + "--\r\n";
		if (SendData(3 * 60))
			return FAIL(SMTP_SEND_DATA);
	}
}
RETCODE ESMTP::DataEnd()
{
	DEBUG_LOG(1 , "Закрываем письмо");
	// <CRLF> . <CRLF>
	SendBuf = "\r\n.\r\n";
	if (SendData(3 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(10 * 60))
		return FAIL(SMTP_RECV_DATA);
	if (!isRetCodeValid(250))
		return FAIL(MSG_BODY_ERROR);

	return SUCCESS;
}

bool ESMTP::isRetCodeValid(int validCode)
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

RETCODE ESMTP::Command(COMMANDS command)
{
	ERR	error;

	switch (command)
	{
	case ESMTP::INIT:
		if (Init())
			return FAIL(INIT_FAILED);
		break;
	case ESMTP::EHLO:
		if (Ehlo())
			return FAIL(EHLO_FAILED);
		break;
	case ESMTP::MAILFROM:
		if (MailFrom())
			return FAIL(MAIL_FROM_FAILED);
		break;
	case ESMTP::RCPTTO:
		if (RCPTto())
			return FAIL(RCPT_TO_FAILED);
		break;
	case ESMTP::DATA:
		if (Data())
			return FAIL(DATA_FAILED);
		break;
	case ESMTP::DATABLOCK:
		if (Datablock())
			return FAIL(DATABLOCK_FAILED);
		break;
	case ESMTP::DATAEND:
		if (DataEnd())
			return FAIL(MSG_BODY_ERROR);
		break;
	case ESMTP::QUIT:
		if (Quit())
			return FAIL(QUIT_FAILED);
		break;
	default:
		DEBUG_LOG(1 , "Неизвестная комманда");
		return FAIL(SMTP_UNDEF_COMM);
		break;
	}

	return SUCCESS;
}

ESMTP::ESMTP()
{

}

ESMTP::~ESMTP()
{
	if (server.isConnected) DisconnectRemoteServer();
}

// A simple string match
bool ESMTP::IsCommandSupported(string response, string command)
{
	if (response.find(command) == string::npos)
		return false;
	else
		return true;
}

bool ESMTP::isAuthRequire()
{
	return server.isAuth;
}

void ESMTP::SetServerAuth(string login, string pass)
{
	server.auth.login = login;
	server.auth.password = pass;

}

RETCODE ESMTP::SetSMTPServer(unsigned short int port, const string & name, bool isAuth)
{
	server.port = port;
	server.name = name;
	server.isAuth = isAuth;
	return SUCCESS;
}

RETCODE ESMTP::Auth()
{
	if (IsCommandSupported(RecvBuf, "AUTH"))
	{
		if (!server.auth.login.size())
			return FAIL(UNDEF_LOGIN);

		if (!server.auth.password.size())
			return FAIL(UNDEF_PASSWORD);

		if (IsCommandSupported(RecvBuf, "LOGIN") == true)
		{
			if(Command(AUTHLOGIN))
				return FAIL(SMTP_COMM);
		}
		else if (IsCommandSupported(RecvBuf, "PLAIN") == true)
		{
			if (Command(AUTHPLAIN))
				return FAIL(SMTP_COMM);
		}
		else if (IsCommandSupported(RecvBuf, "CRAM-MD5") == true)
		{
			if (Command(AUTHCRAMMD5))
				return FAIL(SMTP_COMM);
		}
		else if (IsCommandSupported(RecvBuf, "DIGEST-MD5") == true)
		{
			if (Command(AUTHDIGESTMD5))
				return FAIL(SMTP_COMM);
		}
		else
		{
			DEBUG_LOG(1 , "Не один из известных протоколов аутификации не поддерживается сервером");
			return FAIL(AUTH_NOT_SUPPORTED);
		}
	}
	else
	{
		DEBUG_LOG(1 , "Aутификаця не поддерживается сервером");
		return FAIL(AUTH_NOT_SUPPORTED);
	}

	return SUCCESS;
}

int ESMTP::SmtpXYZdigits()
{
	if (RecvBuf.empty())
		return 0;
	return (RecvBuf[0] - '0') * 100 + (RecvBuf[1] - '0') * 10 + RecvBuf[2] - '0';
}

RETCODE ESMTP::Send(MAIL m)
{
	mail = m;
	if (Connect())
		return FAIL(STMP_CONNECT);


	DEBUG_LOG(1 , "Рукопожатие с сервером по протоколу smtp");
	if (Command(INIT))
		return FAIL(SMTP_COMM);
	if (Command(EHLO))
		return FAIL(SMTP_COMM);
	
	if (server.isAuth)
	{
		DEBUG_LOG(1 , "Аутификация");
		if (Auth())
			return FAIL(SMTP_AUTH);
	}

	DEBUG_LOG(1 , "Отправка письма");

	if (SendMail())
		return FAIL(SMTP_SEND_MAIL);

	return SUCCESS;
}

RETCODE ESMTP::SendMail()
{
	DEBUG_LOG(1, "Отправка емейла");

	if(Command(MAILFROM))
		return FAIL(SMTP_COMM);
	
	if (Command(RCPTTO))
		return FAIL(SMTP_COMM);

	if (Command(DATA))
		return FAIL(SMTP_COMM);

	if (Command(DATABLOCK))
		return FAIL(SMTP_COMM);

	if (Command(DATAEND))
		return FAIL(SMTP_COMM);

	return SUCCESS;
}

RETCODE ESMTP::ReceiveData(int timeout)
{
	DEBUG_LOG(2, "Принимаем ответ без шифрования");
	if (ReceiveData_NoSec(timeout))
		return FAIL(SMTP_RECV_DATA_NOSEC);

	DEBUG_LOG(2, "Ответ сервера принят");
	return SUCCESS;
}
RETCODE ESMTP::SendData(int timeout)
{
	DEBUG_LOG(2, "Отправляем запрос без шифрования");
	if (SendData_NoSec(timeout))
		return FAIL(SMTP_SEND_DATA_NOSEC);

	DEBUG_LOG(2, "Запрос на сервер отправлен");
	return SUCCESS;
}

string ESMTP::GetLocalHostName()
{
	return m_sLocalHostName;
}


void ESMTP::SetLocalHostName(const char *sLocalHostName)
{
	m_sLocalHostName = sLocalHostName;
}
