#include "smtp.h"

RETCODE SMTP::Init()
{
	DEBUG_LOG("Инициализация протокола smtp");
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(220))
		return FAIL(SERVER_NOT_RESPONDING);

	return SUCCESS;
}

RETCODE SMTP::Ehlo() 
{
	DEBUG_LOG("Отправка EHLO комманды");
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

RETCODE SMTP::AuthPlain()
{
	DEBUG_LOG("Аунтификация AUTH PLAIN");
	string s = server.auth.login + "^" + server.auth.login + "^" + server.auth.password;
	unsigned int length = s.size();
	unsigned char *ustrLogin = UTILS::StringToUnsignedChar(s);
	for (unsigned int i = 0; i < length; i++)
	{
		if (ustrLogin[i] == 94) ustrLogin[i] = 0;
	}
	std::string encoded_login = base64_encode(ustrLogin, length);
	delete[] ustrLogin;
	SendBuf =  "AUTH PLAIN " + encoded_login + "\r\n";

	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(235))
		return FAIL(AUTH_PLAIN_FAILED);

	return SUCCESS;
}

RETCODE SMTP::AuthLogin()
{
	DEBUG_LOG("Аунтификация AUTH LOGIN");
	SendBuf =  "AUTH LOGIN\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(334))
		return FAIL(AUTH_LOGIN_FAILED);

	DEBUG_LOG("Отправка логина");
	string encoded_login = base64_encode(reinterpret_cast<const unsigned char*>(server.auth.login.c_str()), server.auth.login.size());
	SendBuf = encoded_login + "\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(334))
		return FAIL(UNDEF_XYZ_RESPONSE);

	DEBUG_LOG("Отправка пароля");
	string encoded_password = base64_encode(reinterpret_cast<const unsigned char*>(server.auth.password.c_str()), server.auth.password.size());
	SendBuf = encoded_password + "\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(235))
	{
		DEBUG_LOG("Неверный пароль/логин или не запрещён доступ из небезопасных приложений");
		return FAIL(BAD_LOGIN_PASS);
	}

	return SUCCESS;
}

RETCODE SMTP::CramMD5()
{
	DEBUG_LOG("Аунтификация AUTH CRAM-MD5");
	SendBuf = "AUTH CRAM-MD5\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(334))
		return FAIL(AUTH_CRAMMD5_FAILED);

	DEBUG_LOG("Генерация токена");

	std::string encoded_challenge = RecvBuf;
	encoded_challenge = encoded_challenge.substr(4);
	std::string decoded_challenge = base64_decode(encoded_challenge);

	/////////////////////////////////////////////////////////////////////
	//test data from RFC 2195
	//decoded_challenge = "<1896.697170952@postoffice.reston.mci.net>";
	//m_sLogin = "tim";
	//m_sPassword = "tanstaaftanstaaf";
	//MD5 should produce b913a602c7eda7a495b4e6e7334d3890
	//should encode as dGltIGI5MTNhNjAyYzdlZGE3YTQ5NWI0ZTZlNzMzNGQzODkw
	/////////////////////////////////////////////////////////////////////

	unsigned char *ustrChallenge = UTILS::StringToUnsignedChar(decoded_challenge);
	unsigned char *ustrPassword = UTILS::StringToUnsignedChar(server.auth.password);

	// if ustrPassword is longer than 64 bytes reset it to ustrPassword=MD5(ustrPassword)
	int passwordLength = server.auth.password.size();
	if (passwordLength > 64) {
		MD5 md5password;
		md5password.update(ustrPassword, passwordLength);
		md5password.finalize();
		ustrPassword = md5password.raw_digest();
		passwordLength = 16;
	}

	//Storing ustrPassword in pads
	unsigned char ipad[65], opad[65];
	memset(ipad, 0, 64);
	memset(opad, 0, 64);
	memcpy(ipad, ustrPassword, passwordLength);
	memcpy(opad, ustrPassword, passwordLength);

	// XOR ustrPassword with ipad and opad values
	for (int i = 0; i < 64; i++) {
		ipad[i] ^= 0x36;
		opad[i] ^= 0x5c;
	}

	//perform inner MD5
	MD5 md5pass1;
	md5pass1.update(ipad, 64);
	md5pass1.update(ustrChallenge, decoded_challenge.size());
	md5pass1.finalize();
	unsigned char *ustrResult = md5pass1.raw_digest();

	//perform outer MD5
	MD5 md5pass2;
	md5pass2.update(opad, 64);
	md5pass2.update(ustrResult, 16);
	md5pass2.finalize();
	decoded_challenge = md5pass2.hex_digest();

	delete[] ustrChallenge;
	delete[] ustrPassword;
	delete[] ustrResult;

	decoded_challenge = server.auth.login + " " + decoded_challenge;
	encoded_challenge = base64_encode(reinterpret_cast<const unsigned char*>(decoded_challenge.c_str()), decoded_challenge.size());

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG("Оправка токена " + encoded_challenge);

	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(334))
		return FAIL(AUTH_CRAMMD5_FAILED);

	return SUCCESS;
}

RETCODE SMTP::DigestMD5()
{
	DEBUG_LOG("Аунтификация AUTH DIGEST-MD5");
	SendBuf = "AUTH DIGEST-MD5\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(335))
		return FAIL(DIGESTMD5_FAILED);

	DEBUG_LOG("Генерация токена");

	string encoded_challenge = RecvBuf;
	encoded_challenge = encoded_challenge.substr(4);
	string decoded_challenge = base64_decode(encoded_challenge);

	/////////////////////////////////////////////////////////////////////
	//Test data from RFC 2831
	//To test jump into authenticate and read this line and the ones down to next test data section
	//decoded_challenge = "realm=\"elwood.innosoft.com\",nonce=\"OA6MG9tEQGm2hh\",qop=\"auth\",algorithm=md5-sess,charset=utf-8";
	/////////////////////////////////////////////////////////////////////

	//Get the nonce (manditory)
	int find = decoded_challenge.find("nonce");
	//if (find < 0)
	//	return FAIL(BAD_DIGEST_RESPONSE);
	std::string nonce = decoded_challenge.substr(find + 7);
	find = nonce.find("\"");
	//if (find < 0)
	//	return FAIL(BAD_DIGEST_RESPONSE);
	nonce = nonce.substr(0, find);

	//Get the realm (optional)
	std::string realm;
	find = decoded_challenge.find("realm");
	if (find >= 0) {
		realm = decoded_challenge.substr(find + 7);
		find = realm.find("\"");
	//	if (find < 0)
	//		return FAIL(BAD_DIGEST_RESPONSE);
		realm = realm.substr(0, find);
	}

	//Create a cnonce
	stringstream tempn;
	tempn << std::hex << (unsigned int)time(NULL);
	string cnonce = tempn.str();

	//Set nonce count
	string nc = "00000001";

	//Set QOP
	std::string qop = "auth";

	//Get server address and set uri
	//Skip this step during test
	int len;
	struct sockaddr_storage addr;
	len = sizeof addr;
	int err = getpeername(hSocket, (struct sockaddr*)&addr, &len);
	// if(!err)
	//	 return FAIL(BAD_SERVER_NAME);

	struct sockaddr_in *s = (struct sockaddr_in *)&addr;
	std::string uri = inet_ntoa(s->sin_addr);
	uri = "smtp/" + uri;

	/////////////////////////////////////////////////////////////////////
	//test data from RFC 2831
	//m_sLogin = "chris";
	//m_sPassword = "secret";
	//snprintf(cnonce, 17, "OA6MHXh6VqTrRk");
	//uri = "imap/elwood.innosoft.com";
	//Should form the response:
	//    charset=utf-8,username="chris",
	//    realm="elwood.innosoft.com",nonce="OA6MG9tEQGm2hh",nc=00000001,
	//    cnonce="OA6MHXh6VqTrRk",digest-uri="imap/elwood.innosoft.com",
	//    response=d388dad90d4bbd760a152321f2143af7,qop=auth
	//This encodes to:
	//    Y2hhcnNldD11dGYtOCx1c2VybmFtZT0iY2hyaXMiLHJlYWxtPSJlbHdvb2
	//    QuaW5ub3NvZnQuY29tIixub25jZT0iT0E2TUc5dEVRR20yaGgiLG5jPTAw
	//    MDAwMDAxLGNub25jZT0iT0E2TUhYaDZWcVRyUmsiLGRpZ2VzdC11cmk9Im
	//    ltYXAvZWx3b29kLmlubm9zb2Z0LmNvbSIscmVzcG9uc2U9ZDM4OGRhZDkw
	//    ZDRiYmQ3NjBhMTUyMzIxZjIxNDNhZjcscW9wPWF1dGg=
	/////////////////////////////////////////////////////////////////////

	//Calculate digest response
	unsigned char *ustrRealm = UTILS::StringToUnsignedChar(realm);
	unsigned char *ustrUsername = UTILS::StringToUnsignedChar(server.auth.login);
	unsigned char *ustrPassword = UTILS::StringToUnsignedChar(server.auth.password);
	unsigned char *ustrNonce = UTILS::StringToUnsignedChar(nonce);
	unsigned char *ustrCNonce = UTILS::StringToUnsignedChar(cnonce);
	unsigned char *ustrUri = UTILS::StringToUnsignedChar(uri);
	unsigned char *ustrNc = UTILS::StringToUnsignedChar(nc);
	unsigned char *ustrQop = UTILS::StringToUnsignedChar(qop);
	//if (!ustrRealm || !ustrUsername || !ustrPassword || !ustrNonce || !ustrCNonce || !ustrUri || !ustrNc || !ustrQop)
	//	return FAIL(BAD_LOGIN_PASSWORD);

	MD5 md5a1a;
	md5a1a.update(ustrUsername, server.auth.login.size());
	md5a1a.update((unsigned char*)":", 1);
	md5a1a.update(ustrRealm, realm.size());
	md5a1a.update((unsigned char*)":", 1);
	md5a1a.update(ustrPassword, server.auth.password.size());
	md5a1a.finalize();
	unsigned char *ua1 = md5a1a.raw_digest();

	MD5 md5a1b;
	md5a1b.update(ua1, 16);
	md5a1b.update((unsigned char*)":", 1);
	md5a1b.update(ustrNonce, nonce.size());
	md5a1b.update((unsigned char*)":", 1);
	md5a1b.update(ustrCNonce, strlen(cnonce.c_str()));
	//authzid could be added here
	md5a1b.finalize();
	char *a1 = md5a1b.hex_digest();

	MD5 md5a2;
	md5a2.update((unsigned char*) "AUTHENTICATE:", 13);
	md5a2.update(ustrUri, uri.size());
	//authint and authconf add an additional line here	
	md5a2.finalize();
	char *a2 = md5a2.hex_digest();

	delete[] ua1;
	ua1 = UTILS::StringToUnsignedChar(a1);
	unsigned char *ua2 = UTILS::StringToUnsignedChar(a2);

	//compute KD
	MD5 md5;
	md5.update(ua1, 32);
	md5.update((unsigned char*)":", 1);
	md5.update(ustrNonce, nonce.size());
	md5.update((unsigned char*)":", 1);
	md5.update(ustrNc, strlen(nc.c_str()));
	md5.update((unsigned char*)":", 1);
	md5.update(ustrCNonce, strlen(cnonce.c_str()));
	md5.update((unsigned char*)":", 1);
	md5.update(ustrQop, qop.size());
	md5.update((unsigned char*)":", 1);
	md5.update(ua2, 32);
	md5.finalize();
	decoded_challenge = md5.hex_digest();

	delete[] ustrRealm;
	delete[] ustrUsername;
	delete[] ustrPassword;
	delete[] ustrNonce;
	delete[] ustrCNonce;
	delete[] ustrUri;
	delete[] ustrNc;
	delete[] ustrQop;
	delete[] ua1;
	delete[] ua2;
	delete[] a1;
	delete[] a2;

	string resstr;
	//send the response
	if (RecvBuf.find("charset") != std::string::npos)
		resstr = "charset=utf-8,";

	resstr += "username=\"" + server.auth.login + "\"";
	if (!realm.empty()) {
		resstr += ",realm=\"" + realm + "\"";
	}
	resstr += ",nonce=\"" + nonce + "\"";
	resstr += ",nc=\"" + nc + "\"";
	resstr += ",cnonce=\"" + cnonce + "\"";
	resstr += ",digest-uri=\"" + uri + "\"";
	resstr += ",response=\"" + decoded_challenge + "\"";
	resstr += ",qop=\"" + qop + "\"";
	unsigned char *ustrDigest = UTILS::StringToUnsignedChar(resstr);
	encoded_challenge = base64_encode(ustrDigest, resstr.size());
	delete[] ustrDigest;
	
	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG("Оправка токена " + encoded_challenge);

	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(335))
		return FAIL(DIGESTMD5_FAILED);

	// only completion carraige needed for end digest md5 auth
	SendBuf = "\r\n";

	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(335))
		return FAIL(DIGESTMD5_FAILED);

	return SUCCESS;
}

RETCODE SMTP::Quit()
{
	DEBUG_LOG("Завершение соеденения по протоколу smtp");
	SendBuf = "QUIT\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(221))
		return FAIL(QUIT_FAILED);

	return SUCCESS;
}
RETCODE SMTP::MailFrom()
{
	DEBUG_LOG("Устанавливаем отправителя");
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
RETCODE SMTP::RCPTto()
{
	DEBUG_LOG("Устанавливаем получателей");
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
RETCODE SMTP::Data()
{
	DEBUG_LOG("Отправка заголовков письма");
	SendBuf = "DATA\r\n"; 
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(2 * 60))
		return FAIL(SMTP_RECV_DATA);
	if (!isRetCodeValid(354))
		return FAIL(DATA_FAILED);

	SendBuf = mail.header;
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(2 * 60))
		return FAIL(SMTP_RECV_DATA);
	if (!isRetCodeValid(354))
		return FAIL(DATA_FAILED);

	DEBUG_LOG("Отправка тела письма");

	while (mail.body.size())
	{
		SendBuf = mail.body[0] + "\r\n";
		mail.body.erase(mail.body.begin());

		if (SendData(5 * 60))
			return FAIL(SMTP_SEND_DATA);
		if (ReceiveData(2 * 60))
			return FAIL(SMTP_RECV_DATA);
		if (!isRetCodeValid(354))
			return FAIL(DATA_FAILED);

	}

	SendBuf = " \r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(2 * 60))
		return FAIL(SMTP_RECV_DATA);
	if (!isRetCodeValid(354))
		return FAIL(DATA_FAILED);

	return SUCCESS;
}
RETCODE SMTP::Datablock()
{
	DEBUG_LOG("Отправка прикриплённых файлов, если есть");

	// next goes attachments (if they are)
	while (mail.attachments.size())
	{
		DEBUG_LOG("Отправка прикриплённого файла");
		unsigned int i, rcpt_count, res;
		char *FileBuf = NULL;
		FILE* hFile = NULL;
		unsigned long int FileSize, TotalSize, MsgPart;
		string FileName, EncodedFileName;
		string::size_type pos;

		//Allocate memory
		if ((FileBuf = new char[55]) == NULL)
			return FAIL(LACK_OF_MEMORY);

		//Check that any attachments specified can be opened
		TotalSize = 0;
		DEBUG_LOG("Проверяем существует ли файл");

		// opening the file:
		hFile = fopen(mail.attachments[0].c_str(), "rb");
		if (hFile == NULL)
			return FAIL(FILE_NOT_EXIST);

		DEBUG_LOG("Проверяем размер файла");

		// checking file size:
		fseek(hFile, 0, SEEK_END);
		FileSize = ftell(hFile);
		TotalSize += FileSize;

		// sending the file:
		if (TotalSize / 1024 > MSG_SIZE_IN_MB * 1024)
			return FAIL(MSG_TOO_BIG);

		DEBUG_LOG("Проверяем размер файла");

		fclose(hFile);
		hFile = NULL;
		delete[] FileBuf;
		FileBuf = NULL;

		pos = mail.attachments[0].find_last_of("\\");
		if (pos == string::npos) FileName = mail.attachments[0];
		else FileName = mail.attachments[0].substr(pos + 1);

		//RFC 2047 - Use UTF-8 charset,base64 encode.
		EncodedFileName = "=?UTF-8?B?";
		EncodedFileName += base64_encode((unsigned char *)FileName.c_str(), FileName.size());
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
		if (ReceiveData(0))
			return FAIL(SMTP_RECV_DATA);
		if (!isRetCodeValid(0))
			return FAIL(DATABLOCK_FAILED);

		DEBUG_LOG("Отправляем тело файла");

		// opening the file:
		hFile = fopen(mail.attachments[0].c_str(), "rb");

		// get file size:
		fseek(hFile, 0, SEEK_END);
		FileSize = ftell(hFile);
		fseek(hFile, 0, SEEK_SET);

		MsgPart = 0;
		for (i = 0; i < FileSize / 54 + 1; i++)
		{
			res = fread(FileBuf, sizeof(char), 54, hFile);
			MsgPart ? SendBuf += base64_encode(reinterpret_cast<const unsigned char*>(FileBuf), res)
				: SendBuf = base64_encode(reinterpret_cast<const unsigned char*>(FileBuf), res);
			SendBuf += "\r\n";
			MsgPart += res + 2;
			if (MsgPart >= BUFFER_SIZE / 2)
			{ 
				// sending part of the message
				MsgPart = 0;
				if (SendData(3 * 60))
					return FAIL(SMTP_SEND_DATA);
				if (ReceiveData(0))
					return FAIL(SMTP_RECV_DATA);
				if (!isRetCodeValid(0))
					return FAIL(DATABLOCK_FAILED);
			}
		}
		if (MsgPart)
		{
			if (SendData(3 * 60))
				return FAIL(SMTP_SEND_DATA);
			if (ReceiveData(0))
				return FAIL(SMTP_RECV_DATA);
			if (!isRetCodeValid(0))
				return FAIL(DATABLOCK_FAILED);
		}
		fclose(hFile);
		hFile = NULL;

		mail.attachments.erase(mail.attachments.begin());
	}

	DEBUG_LOG("Закрываем письмо");

	SendBuf = "\r\n--" + BOUNDARY_TEXT + "--\r\n";

	if (SendData(3 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(0))
		return FAIL(SMTP_RECV_DATA);
	if (!isRetCodeValid(0))
		return FAIL(DATABLOCK_FAILED);

	SendBuf = "\r\n.\r\n";
	if (SendData(3 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(0))
		return FAIL(SMTP_RECV_DATA);
	if (!isRetCodeValid(0))
		return FAIL(DATABLOCK_FAILED);

	return SUCCESS;
}
RETCODE SMTP::Starttls()
{
	DEBUG_LOG("Обьявляем о начале соеденения с использованием tls");
	SendBuf = "STARTTLS\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);
	if (!isRetCodeValid(220))
		return FAIL(STARTTLS_FAILED);

	return SUCCESS;
}

bool SMTP::isRetCodeValid(int validCode)
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

RETCODE SMTP::Command(COMMANDS command)
{
	ERR	error;

	switch (command)
	{
	case SMTP::INIT:
		if (Init())
			return FAIL(INIT_FAILED);
		break;
	case SMTP::EHLO:
		if (Ehlo())
			return FAIL(EHLO_FAILED);
		break;
	case SMTP::AUTHPLAIN:
		if (AuthPlain())
			return FAIL(AUTH_PLAIN_FAILED);
		break;
	case SMTP::AUTHLOGIN:
		if (AuthLogin())
			return FAIL(AUTH_LOGIN_FAILED);
		break;
	case SMTP::AUTHCRAMMD5:
		if (CramMD5())
			return FAIL(AUTH_CRAMMD5_FAILED);
		break;
	case SMTP::AUTHDIGESTMD5:
		if (DigestMD5())
			return FAIL(AUTH_DIGESTMD5_FAILED);
		break;
	case SMTP::MAILFROM:
		if (MailFrom())
			return FAIL(MAIL_FROM_FAILED);
		break;
	case SMTP::RCPTTO:
		if (RCPTto())
			return FAIL(RCPT_TO_FAILED);
		break;
	case SMTP::DATA:
		if (Data())
			return FAIL(DATA_FAILED);
		break;
	case SMTP::DATABLOCK:
		if (Datablock())
			return FAIL(DATABLOCK_FAILED);
		break;
	case SMTP::QUIT:
		if (Quit())
			return FAIL(QUIT_FAILED);
		break;
	case SMTP::STARTTLS:
		if (Starttls())
			return FAIL(STARTTLS_FAILED);
		break;
	default:
		DEBUG_LOG("Неизвестная комманда");
		return FAIL(SMTP_UNDEF_COMM);
		break;
	}

	return SUCCESS;
}

SMTP::SMTP()
{
	ctx = NULL;
	ssl = NULL;

	WSA_Init();
}

SMTP::~SMTP()
{
	if (server.isConnected) DisconnectRemoteServer();
	
	CleanupOpenSSL();

	WSACleanup();
}


// A simple string match
bool SMTP::IsCommandSupported(string response, string command)
{
	if (response.find(command) == string::npos)
		return false;
	else
		return true;
}

bool SMTP::isAuthRequire()
{
	return server.isAuth;
}

void SMTP::SetServerAuth(string login, string pass)
{
	server.auth.login = login;
	server.auth.password = pass;

}

RETCODE SMTP::SetSMTPServer(SUPPORTED_SMTP_SERVERS serv_id, SMTP_SECURITY_TYPE sec_type)
{
	for (auto supp_server : supported_servers)
	{
		if (supp_server.id == serv_id && supp_server.required_security == sec_type)
		{
			server.port = supp_server.port;
			server.name = supp_server.name;
			server.isAuth = supp_server.isAuth;
			return SUCCESS;
		}
	}
	return 1;//FAIL(UNDEF_ERROR); // TODO: такой сервер не поддерживается
}


SMTP_SECURITY_TYPE SMTP::GetSecurityType() const
{
	return server.security;
}

void SMTP::SetSecurityType(SMTP_SECURITY_TYPE type)
{
	server.security = type;
}

RETCODE SMTP::WSA_Init() {
	DEBUG_LOG("Инициализация WinSocks");
	// Initialize WinSock
	hSocket = INVALID_SOCKET;
	WSADATA wsaData;
	WORD wVer = MAKEWORD(2, 2);
	if (WSAStartup(wVer, &wsaData) != NO_ERROR)
		return FAIL(WSA_STARTUP);

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return FAIL(WSA_VER);
	}

	char hostname[255];
	if (gethostname((char *)&hostname, 255) == SOCKET_ERROR)
		return FAIL(WSA_HOSTNAME);

	m_sLocalHostName = hostname;

	return SUCCESS;
}

RETCODE SMTP::SocksConnect()
{
	DEBUG_LOG("Установка соеденения с сервором");
	string szServer = server.name;
	const unsigned short nPort_ = server.port;

	unsigned short nPort = 0;
	LPSERVENT lpServEnt;
	SOCKADDR_IN sockAddr;
	unsigned long ul = 1;
	fd_set fdwrite, fdexcept;
	timeval timeout;
	int res = 0;

	timeout.tv_sec = TIME_IN_SEC;
	timeout.tv_usec = 0;

	hSocket = INVALID_SOCKET;

	DEBUG_LOG("Создаём новый сокет");
	if ((hSocket = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return FAIL(WSA_INVALID_SOCKET);

	DEBUG_LOG("Конвертируем байтовое представление порта в сетевой порядок байтов");
	if (nPort_ != 0)
		nPort = htons(nPort_);
	else
	{
		lpServEnt = getservbyname("mail", 0);
		if (lpServEnt == NULL)
			nPort = htons(25);
		else
			nPort = lpServEnt->s_port;
	}

	DEBUG_LOG("Заполняем структуру сервера");
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = nPort;
	if ((sockAddr.sin_addr.s_addr = inet_addr(szServer.c_str())) == INADDR_NONE)
	{
		LPHOSTENT host;

		host = gethostbyname(szServer.c_str());
		if (host)
			memcpy(&sockAddr.sin_addr, host->h_addr_list[0], host->h_length);
		else
		{
			closesocket(hSocket);
			return FAIL(WSA_GETHOSTBY_NAME_ADDR);
		}
	}

	DEBUG_LOG("Устанавлмваем сокет в неблокирующий режим");
	if (ioctlsocket(hSocket, FIONBIO, (unsigned long*)&ul) == SOCKET_ERROR)
	{
		closesocket(hSocket);
		return FAIL(WSA_IOCTLSOCKET);
	}

	DEBUG_LOG("Подключаемся к серверу");
	if (connect(hSocket, (LPSOCKADDR)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			closesocket(hSocket);
			return FAIL(WSA_CONNECT);
		}
	}

	DEBUG_LOG("Проверяем подключение");
	while (true)
	{
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdexcept);

		FD_SET(hSocket, &fdwrite);
		FD_SET(hSocket, &fdexcept);

		if ((res = select(hSocket + 1, NULL, &fdwrite, &fdexcept, &timeout)) == SOCKET_ERROR)
		{
			closesocket(hSocket);
			return FAIL(WSA_SELECT);
		}

		if (!res)
		{
			closesocket(hSocket);
			return FAIL(SELECT_TIMEOUT);
		}
		if (res && FD_ISSET(hSocket, &fdwrite))
			break;
		if (res && FD_ISSET(hSocket, &fdexcept))
		{
			closesocket(hSocket);
			return FAIL(WSA_SELECT);
		}
	} // while

	FD_CLR(hSocket, &fdwrite);
	FD_CLR(hSocket, &fdexcept);

	DEBUG_LOG("Подключение с сервером успешно установлено");
	return SUCCESS;
}

RETCODE SMTP::Auth()
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
			DEBUG_LOG("Не один из известных протоколов аутификации не поддерживается сервером");
			return FAIL(AUTH_NOT_SUPPORTED);
		}
	}
	else
	{
		DEBUG_LOG("Aутификаця не поддерживается сервером");
		return FAIL(AUTH_NOT_SUPPORTED);
	}

	return SUCCESS;
}

void SMTP::DisconnectRemoteServer()
{
	if (server.isConnected) Command(QUIT);
	if (hSocket)
	{
		closesocket(hSocket);
	}
	hSocket = INVALID_SOCKET;
}

int SMTP::SmtpXYZdigits()
{
	if (RecvBuf.empty())
		return 0;
	return (RecvBuf[0] - '0') * 100 + (RecvBuf[1] - '0') * 10 + RecvBuf[2] - '0';
}

RETCODE SMTP::Connect() {
	if (hSocket == INVALID_SOCKET)
	{
		if (SocksConnect())
		{
			DEBUG_LOG("Ошибка при соеденении");
			if (RecvBuf[0] == '5' && RecvBuf[1] == '3' && RecvBuf[2] == '0')
				server.isConnected = false;
			DisconnectRemoteServer();
			return FAIL(WSA_INVALID_SOCKET);
		}
	}
	return SUCCESS;
}

RETCODE SMTP::Send(MAIL m)
{
	DEBUG_LOG("Отправка емейла");
	mail = m;
	if (Connect())
		return FAIL(STMP_CONNECT);

	if (server.security != NO_SECURITY)
	{
		DEBUG_LOG("Инициализация openssl");
		InitOpenSSL(); 
		if (server.security == USE_SSL)
		{
			DEBUG_LOG("Установка ssl поверх smpt");
			OpenSSLConnect();
			useSecurity = true;
			DEBUG_LOG("Успешно установлено соеденение по протоколу smtps с использованием ssl");
			DEBUG_LOG("Далее передача данных по протоколу smtps");
		}
	}

	DEBUG_LOG("Рукопожатие с сервером по протоколу smtp");
	if (Command(INIT))
		return FAIL(SMTP_COMM);
	if (Command(EHLO))
		return FAIL(SMTP_COMM);
	
	if (server.security == USE_TLS)
	{
		DEBUG_LOG("Устанавливаем tsl поверх smpt");
		if (IsCommandSupported(RecvBuf, "STARTTLS") == false)
		{
			DEBUG_LOG("tsl протокол не поддерживается сервером");
			return FAIL(STARTTLS_NOT_SUPPORTED);
		}

		if (Command(STARTTLS))
			return FAIL(SMTP_COMM);

		OpenSSLConnect();

		useSecurity = true;

		DEBUG_LOG("Успешно установлено соеденение по протоколу smtps с использованием tsl");
		DEBUG_LOG("Далее передача данных по протоколу smtps");

		if (Command(EHLO))
			return FAIL(SMTP_COMM);
	}

	if (server.isAuth)
	{
		DEBUG_LOG("Аутификация");
		if (Auth())
			return FAIL(SMTP_AUTH);
	}

	DEBUG_LOG("Отправка письма");

	if (SendMail())
		return FAIL(SMTP_SEND_MAIL);

	return SUCCESS;
}

RETCODE SMTP::SendMail()
{
	if(Command(MAILFROM))
		return FAIL(SMTP_COMM);
	
	if (Command(RCPTTO))
		return FAIL(SMTP_COMM);

	if (Command(DATA))
		return FAIL(SMTP_COMM);

	if (Command(DATABLOCK))
		return FAIL(SMTP_COMM);

	return SUCCESS;
}

RETCODE SMTP::ReceiveData(int timeout)
{
	if (useSecurity)
	{
		DEBUG_LOG("Принимаем ответ с использованием шифрования");
		if (ReceiveData_SSL(timeout))
			return FAIL(SMTP_RECV_DATA_SEC);
	}
	else
	{
		DEBUG_LOG("Принимаем ответ без шифрования");
		if (ReceiveData_NoSec(timeout))
			return FAIL(SMTP_RECV_DATA_NOSEC);
	}

	DEBUG_LOG("Ответ сервера принят");
	return SUCCESS;
}
RETCODE SMTP::SendData(int timeout)
{
	if (useSecurity)
	{
		DEBUG_LOG("Отправляем запрос с использованием шифрования");
		if (SendData_SSL(timeout))
			return FAIL(SMTP_SEND_DATA_SEC);
	}
	else
	{
		DEBUG_LOG("Отправляем запрос без шифрования");
		if (SendData_NoSec(timeout))
			return FAIL(SMTP_SEND_DATA_NOSEC);
	}

	DEBUG_LOG("Запрос на сервер отправлен");
	return SUCCESS;
}

RETCODE SMTP::SendData_NoSec(int send_timeout)
{
	int res;
	fd_set fdwrite;
	timeval time;

	time.tv_sec = send_timeout;
	time.tv_usec = 0;

	if (SendBuf.empty())
		return FAIL(SENDBUF_IS_EMPTY);

	FD_ZERO(&fdwrite);

	FD_SET(hSocket, &fdwrite);

	if ((res = select(hSocket + 1, NULL, &fdwrite, NULL, &time)) == SOCKET_ERROR)
	{
		FD_CLR(hSocket, &fdwrite);
		return FAIL(WSA_SELECT);
	}

	if (!res)
	{
		//timeout
		FD_CLR(hSocket, &fdwrite);
		return FAIL(SERVER_NOT_RESPONDING);
	}

	if (res && FD_ISSET(hSocket, &fdwrite))
	{
		res = send(hSocket, SendBuf.c_str(), SendBuf.size(), 0);
		if (res == SOCKET_ERROR || res == 0)
		{
			FD_CLR(hSocket, &fdwrite);
			return FAIL(WSA_SEND);
		}
	}

	FD_CLR(hSocket, &fdwrite);

	return SUCCESS;
}

string SMTP::GetLocalHostName()
{
	return m_sLocalHostName;
}


void SMTP::SetLocalHostName(const char *sLocalHostName)
{
	m_sLocalHostName = sLocalHostName;
}

RETCODE SMTP::ReceiveData_NoSec(int recv_timeout)
{
	int res = 0;
	fd_set fdread;
	timeval time;

	time.tv_sec = recv_timeout;
	time.tv_usec = 0;

	FD_ZERO(&fdread);

	FD_SET(hSocket, &fdread);

	if ((res = select(hSocket + 1, &fdread, NULL, NULL, &time)) == SOCKET_ERROR)
	{
		FD_CLR(hSocket, &fdread);
		return FAIL(WSA_SELECT);
	}

	if (!res)
	{
		//timeout
		FD_CLR(hSocket, &fdread);
		return FAIL(SERVER_NOT_RESPONDING);
	}

	if (FD_ISSET(hSocket, &fdread))
	{
		char buffer[BUFFER_SIZE];
		res = recv(hSocket, buffer, BUFFER_SIZE, 0);
		RecvBuf = buffer;
		RecvBuf[res] = '\0';
		if (res == SOCKET_ERROR)
		{
			FD_CLR(hSocket, &fdread);
			return FAIL(WSA_RECV);
		}
	}

	FD_CLR(hSocket, &fdread);
	if (res == 0)
	{
		return FAIL(CONNECTION_CLOSED);
	}

	return SUCCESS;
}


RETCODE SMTP::ReceiveData_SSL(int recv_timeout)
{
	int res = 0;
	int offset = 0;
	fd_set fdread;
	fd_set fdwrite;
	timeval time;

	int read_blocked_on_write = 0;

	time.tv_sec = recv_timeout;
	time.tv_usec = 0;

	bool bFinish = false;

	while (!bFinish)
	{
		FD_ZERO(&fdread);
		FD_ZERO(&fdwrite);

		FD_SET(hSocket, &fdread);

		if (read_blocked_on_write)
		{
			FD_SET(hSocket, &fdwrite);
		}

		if ((res = select(hSocket + 1, &fdread, &fdwrite, NULL, &time)) == SOCKET_ERROR)
		{
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			return FAIL(WSA_SELECT);
		}

		if (!res)
		{
			//timeout
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			return FAIL(SERVER_NOT_RESPONDING);
		}

		if (FD_ISSET(hSocket, &fdread) || (read_blocked_on_write && FD_ISSET(hSocket, &fdwrite)))
		{
			RecvBuf = "";
			while (1)
			{
				read_blocked_on_write = 0;

				const int buff_len = 1024;
				char buff[buff_len];

				res = SSL_read(ssl, buff, buff_len);

				int ssl_err = SSL_get_error(ssl, res);
				if (ssl_err == SSL_ERROR_NONE)
				{
					if (offset + res > BUFFER_SIZE - 1)
					{
						FD_ZERO(&fdread);
						FD_ZERO(&fdwrite);
						return FAIL(LACK_OF_MEMORY);
					}
					RecvBuf += buff;
					offset += res;
					RecvBuf[offset] = '\0';
					if (SSL_pending(ssl))
					{
						continue;
					}
					else
					{
						bFinish = true;
						break;
					}
				}
				else if (ssl_err == SSL_ERROR_ZERO_RETURN)
				{
					bFinish = true;
					break;
				}
				else if (ssl_err == SSL_ERROR_WANT_READ)
				{
					break;
				}
				else if (ssl_err == SSL_ERROR_WANT_WRITE)
				{
					/* We get a WANT_WRITE if we're
					trying to rehandshake and we block on
					a write during that rehandshake.

					We need to wait on the socket to be
					writeable but reinitiate the read
					when it is */
					read_blocked_on_write = 1;
					break;
				}
				else
				{
					FD_ZERO(&fdread);
					FD_ZERO(&fdwrite);
					return FAIL(SSL_PROBLEM);
				}
			}
		}
	}

	FD_ZERO(&fdread);
	FD_ZERO(&fdwrite);
	if (offset == 0)
	{
		return FAIL(CONNECTION_CLOSED);
	}

	return SUCCESS;
}

RETCODE SMTP::SendData_SSL(int send_timeout)
{
	int res;
	fd_set fdwrite;
	fd_set fdread;
	timeval time;

	int write_blocked_on_read = 0;

	time.tv_sec = send_timeout;
	time.tv_usec = 0;

	if (SendBuf.empty())
		return FAIL(SENDBUF_IS_EMPTY);

	FD_ZERO(&fdwrite);
	FD_ZERO(&fdread);

	FD_SET(hSocket, &fdwrite);

	if (write_blocked_on_read)
	{
		FD_SET(hSocket, &fdread);
	}

	if ((res = select(hSocket + 1, &fdread, &fdwrite, NULL, &time)) == SOCKET_ERROR)
	{
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdread);
		return FAIL(WSA_SELECT);
	}

	if (!res)
	{
		//timeout
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdread);
		return FAIL(SERVER_NOT_RESPONDING);
	}

	if (FD_ISSET(hSocket, &fdwrite) || (write_blocked_on_read && FD_ISSET(hSocket, &fdread)))
	{
		write_blocked_on_read = 0;

		/* Try to write */
		res = SSL_write(ssl, SendBuf.c_str(), SendBuf.size());

		switch (SSL_get_error(ssl, res))
		{
			/* We wrote something*/
		case SSL_ERROR_NONE:
			break;

			/* We would have blocked */
		case SSL_ERROR_WANT_WRITE:
			break;

			/* We get a WANT_READ if we're
			   trying to rehandshake and we block on
			   write during the current connection.

			   We need to wait on the socket to be readable
			   but reinitiate our write when it is */
		case SSL_ERROR_WANT_READ:
			write_blocked_on_read = 1;
			break;

			/* Some other error */
		default:
			FD_ZERO(&fdread);
			FD_ZERO(&fdwrite);
			return FAIL(SSL_PROBLEM);
		}

	}

	FD_ZERO(&fdwrite);
	FD_ZERO(&fdread);

	return SUCCESS;
}

RETCODE SMTP::InitOpenSSL()
{
	SSL_library_init();
	SSL_load_error_strings();
	ctx = SSL_CTX_new(SSLv23_client_method());
	if (ctx == NULL)
		return FAIL(SSL_PROBLEM);

	return SUCCESS;
}

RETCODE SMTP::OpenSSLConnect()
{
	if (ctx == NULL)
		return FAIL(SSL_PROBLEM);
	ssl = SSL_new(ctx);
	if (ssl == NULL)
		return FAIL(SSL_PROBLEM);
	SSL_set_fd(ssl, (int)hSocket);
	SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

	int res = 0;
	fd_set fdwrite;
	fd_set fdread;
	int write_blocked = 0;
	int read_blocked = 0;

	timeval time;
	time.tv_sec = TIME_IN_SEC;
	time.tv_usec = 0;

	while (1)
	{
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdread);

		if (write_blocked)
			FD_SET(hSocket, &fdwrite);
		if (read_blocked)
			FD_SET(hSocket, &fdread);

		if (write_blocked || read_blocked)
		{
			write_blocked = 0;
			read_blocked = 0;
			if ((res = select(hSocket + 1, &fdread, &fdwrite, NULL, &time)) == SOCKET_ERROR)
			{
				FD_ZERO(&fdwrite);
				FD_ZERO(&fdread);
				return FAIL(WSA_SELECT);
			}
			if (!res)
			{
				//timeout
				FD_ZERO(&fdwrite);
				FD_ZERO(&fdread);
				return FAIL(SERVER_NOT_RESPONDING);
			}
		}
		res = SSL_connect(ssl);
		switch (SSL_get_error(ssl, res))
		{
		case SSL_ERROR_NONE:
			FD_ZERO(&fdwrite);
			FD_ZERO(&fdread);
			return SUCCESS;
			break;

		case SSL_ERROR_WANT_WRITE:
			write_blocked = 1;
			break;

		case SSL_ERROR_WANT_READ:
			read_blocked = 1;
			break;

		default:
			FD_ZERO(&fdwrite);
			FD_ZERO(&fdread);
			return FAIL(SSL_PROBLEM);
		}
	}
	return SUCCESS;
}

void SMTP::CleanupOpenSSL()
{
	if (ssl != NULL)
	{
		SSL_shutdown(ssl);  /* send SSL/TLS close_notify */
		SSL_free(ssl);
		ssl = NULL;
	}
	if (ctx != NULL)
	{
		SSL_CTX_free(ctx);
		ctx = NULL;
		ERR_remove_state(0);
		ERR_free_strings();
		EVP_cleanup();
		CRYPTO_cleanup_all_ex_data();
	}
}