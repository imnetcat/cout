#include "smtp.h"

string SMTP::command_Ehlo(
) {
	string s = "EHLO ";
	s += GetLocalHostName().empty() ? "localhost" : m_sLocalHostName;
	s += "\r\n";
	return s;
}

string SMTP::command_AuthPlain()
{
	string s = server.auth.login + "^" + server.auth.login + "^" + server.auth.password;
	unsigned int length = s.size();
	unsigned char *ustrLogin = CharToUnsignedChar(s.c_str());
	for (unsigned int i = 0; i < length; i++)
	{
		if (ustrLogin[i] == 94) ustrLogin[i] = 0;
	}
	std::string encoded_login = base64_encode(ustrLogin, length);
	delete[] ustrLogin;
	return "AUTH PLAIN " + encoded_login + "\r\n";
}

string SMTP::command_AuthPlain()
{
	return "AUTH LOGIN\r\n";
}

string SMTP::command_User()
{

	string encoded_login = base64_encode(reinterpret_cast<const unsigned char*>(server.auth.login.c_str()), server.auth.login.size());
	return encoded_login + "\r\n";

}

string SMTP::command_Password()
{
	string encoded_password = base64_encode(reinterpret_cast<const unsigned char*>(server.auth.password.c_str()), server.auth.password.size());
	return encoded_password + "\r\n";
}

string SMTP::command_crammd5()
{
	return "AUTH CRAM-MD5\r\n";
}

string SMTP::command_crammd5_password()
{
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

	unsigned char *ustrChallenge = CharToUnsignedChar(decoded_challenge.c_str());
	unsigned char *ustrPassword = CharToUnsignedChar(server.auth.password.c_str());

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

	return encoded_challenge + "\r\n";
}

string SMTP::command_dgmd5()
{
	return "AUTH DIGEST-MD5\r\n";
}

string SMTP::command_dgmd5_tocken()
{
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
	unsigned char *ustrRealm = CharToUnsignedChar(realm.c_str());
	unsigned char *ustrUsername = CharToUnsignedChar(server.auth.login.c_str());
	unsigned char *ustrPassword = CharToUnsignedChar(server.auth.password.c_str());
	unsigned char *ustrNonce = CharToUnsignedChar(nonce.c_str());
	unsigned char *ustrCNonce = CharToUnsignedChar(cnonce.c_str());
	unsigned char *ustrUri = CharToUnsignedChar(uri.c_str());
	unsigned char *ustrNc = CharToUnsignedChar(nc.c_str());
	unsigned char *ustrQop = CharToUnsignedChar(qop.c_str());
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
	ua1 = CharToUnsignedChar(a1);
	unsigned char *ua2 = CharToUnsignedChar(a2);

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
	unsigned char *ustrDigest = CharToUnsignedChar(resstr.c_str());
	encoded_challenge = base64_encode(ustrDigest, resstr.size());
	delete[] ustrDigest;
	return encoded_challenge + "\r\n";
}

string SMTP::command_dgmd5_pass()
{
	// only completion carraige needed
	return "\r\n";
}

string SMTP::command_quit()
{
	return "QUIT\r\n";
}
string SMTP::command_mailfrom()
{
	return "MAIL FROM:<" + mail.senderMail + ">\r\n";
}
string SMTP::command_rcptto()
{
	return "RCPT TO:<" + mail.recipients.at(0).Mail + ">\r\n";
}
string SMTP::command_ccrcptto()
{
	return "RCPT TO:<" + mail.ccrecipients.at(0).Mail + ">\r\n";
}
string SMTP::command_bccrcptto()
{
	return "RCPT TO:<" + mail.bccrecipients.at(0).Mail + ">\r\n";
}
string SMTP::command_data()
{
	return "DATA\r\n";
}
string SMTP::command_datablock()
{
	return mail.header;
}

const Command_Entry* SMTP::FindCommandEntry(SMTP_COMMAND command)
{
	const Command_Entry* pEntry = nullptr;
	for (size_t i = 0; i < command_list.size(); ++i)
	{
		if (command_list[i].command == command)
		{
			pEntry = &command_list[i];
			break;
		}
	}
	return pEntry;
}
unsigned char* CharToUnsignedChar(const char *strIn)
{
	unsigned char *strOut;

	unsigned long length,
		i;


	length = strlen(strIn);

	strOut = new unsigned char[length + 1];
	if (!strOut) return NULL;

	for (i = 0; i < length; i++) strOut[i] = (unsigned char)strIn[i];
	strOut[length] = '\0';

	return strOut;
}

SMTP::SMTP()
{

	WSA_Init();

}

SMTP::~SMTP()
{
	if (server.isConnected) DisconnectRemoteServer();
	
	WSACleanup();
}


// A simple string match
bool SMTP::IsCommandSupported(string response, string command)
{
	int res_len = response.size();
	int key_len = command.size();
	if (res_len < key_len)
		return false;
	int pos = 0;
	for (; pos < res_len - key_len + 1; ++pos)
	{
		int pos = 0;
		if (pos = command.find(response) != string::npos)
		{
			if (pos > 0 &&
				(response[pos - 1] == '-' ||
					response[pos - 1] == ' ' ||
					response[pos - 1] == '='))
			{
				if (pos + key_len < res_len)
				{
					if (response[pos + key_len] == ' ' ||
						response[pos + key_len] == '=')
					{
						return true;
					}
					else if (pos + key_len + 1 < res_len)
					{
						if (response[pos + key_len] == '\r' &&
							response[pos + key_len + 1] == '\n')
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
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

	if ((hSocket = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return FAIL(WSA_INVALID_SOCKET);

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

	// start non-blocking mode for socket:
	if (ioctlsocket(hSocket, FIONBIO, (unsigned long*)&ul) == SOCKET_ERROR)
	{
		closesocket(hSocket);
		return FAIL(WSA_IOCTLSOCKET);
	}

	if (connect(hSocket, (LPSOCKADDR)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			closesocket(hSocket);
			return FAIL(WSA_CONNECT);
		}
	}
	else
		return true;

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
	return SUCCESS;
}

RETCODE SMTP::Command(SMTP_COMMAND command)
{
	const Command_Entry* pEntry = FindCommandEntry(command);
	SendBuf = pEntry->getCommandText();
	SendData(pEntry->send_timeout);
	ReceiveData(pEntry);

	return SUCCESS;
}

RETCODE SMTP::InitHandshake()
{
	if (Command(command_INIT))
		return FAIL(SMTP_COMM);

	return SUCCESS;
}

RETCODE SMTP::Handshake()
{
	Command_Entry* pEntry = nullptr;
	bool authenticate = server.isAuth;
	if (authenticate && IsCommandSupported(RecvBuf.c_str(), "AUTH") == true)
	{
		if (!server.auth.login.size())
			return FAIL(UNDEF_LOGIN);

		if (!server.auth.password.size())
			return FAIL(UNDEF_PASSWORD);

		if (IsCommandSupported(RecvBuf.c_str(), "LOGIN") == true)
		{
			if(Command(command_AUTHLOGIN))
				return FAIL(SMTP_COMM);

			// send login:
			if (Command(command_USER))
				return FAIL(SMTP_COMM);

			// send password:
			if (Command(command_PASSWORD))
				return FAIL(SMTP_COMM);
		}
		else if (IsCommandSupported(RecvBuf.c_str(), "PLAIN") == true)
		{
			if (Command(command_AUTHPLAIN))
				return FAIL(SMTP_COMM);
		}
		else if (IsCommandSupported(RecvBuf.c_str(), "CRAM-MD5") == true)
		{
			if (Command(command_AUTHCRAMMD5))
				return FAIL(SMTP_COMM);

			if (Command(command_CRAMMD5_PASSWORD))
				return FAIL(SMTP_COMM);
		}
		else if (IsCommandSupported(RecvBuf.c_str(), "DIGEST-MD5") == true)
		{
			if (Command(command_AUTHDIGESTMD5))
				return FAIL(SMTP_COMM);

			if(Command(command_DIGESTMD5_TOCKEN))
				return FAIL(SMTP_COMM);

			if (Command(command_DIGESTMD5_PASS))
				return FAIL(SMTP_COMM);
		}
		else return FAIL(LOGIN_NOT_SUPPORTED);
	}

	return SUCCESS;
}

void SMTP::DisconnectRemoteServer()
{
	if (server.isConnected) Command(command_QUIT);
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
	mail = m;
	if (Connect())
		return FAIL(STMP_CONNECT);
	if (InitHandshake())
		return FAIL(SMTP_INIT_HANDSHAKE);
	if (Handshake())
		return FAIL(SMTP_HANDSHAKE);
	if (WrappedSend())
		return FAIL(SMTP_WRAPPED_SEND);
	return SUCCESS;
}

RETCODE SMTP::WrappedSend()
{
	unsigned int i, rcpt_count, res, FileId;
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
	for (FileId = 0; FileId < mail.attachments.size(); FileId++)
	{
		// opening the file:
		hFile = fopen(mail.attachments[FileId].c_str(), "rb");
		if (hFile == NULL)
			return FAIL(FILE_NOT_EXIST);

		// checking file size:
		fseek(hFile, 0, SEEK_END);
		FileSize = ftell(hFile);
		TotalSize += FileSize;

		// sending the file:
		if (TotalSize / 1024 > MSG_SIZE_IN_MB * 1024)
			return FAIL(MSG_TOO_BIG);

		fclose(hFile);
		hFile = NULL;
	}

	// ***** SENDING E-MAIL *****

	if (!mail.senderMail.size())
		return FAIL(UNDEF_MAIL_FROM);

	// MAIL <SP> FROM:<reverse-path> <CRLF>
	if(Command(command_MAILFROM))
		return FAIL(SMTP_COMM);

	if (!(rcpt_count = mail.recipients.size()))
		return FAIL(UNDEF_RECIPIENTS);

	while (!mail.recipients.size())
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		if (Command(command_RCPTTO))
			return FAIL(SMTP_COMM);
		mail.recipients.erase(mail.recipients.begin());
	}

	while (!mail.ccrecipients.size())
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		if (Command(command_CCRCPTTO))
			return FAIL(SMTP_COMM);
		mail.ccrecipients.erase(mail.ccrecipients.begin());
	}

	while (!mail.bccrecipients.size())
	{
		// RCPT <SP> TO:<forward-path> <CRLF>
		if (Command(command_BCCRCPTTO))
			return FAIL(SMTP_COMM);
		mail.bccrecipients.erase(mail.bccrecipients.begin());
	}

	// DATA <CRLF>
	if (Command(command_DATA))
		return FAIL(SMTP_COMM);

	// send header
	if (Command(command_DATABLOCK))
		return FAIL(SMTP_COMM);

	// send text message
	if (mail.body.size())
	{
		for (i = 0; i < mail.body.size(); i++)
		{
			SendBuf = mail.body[i] + "\r\n";
			SendData(pEntry->send_timeout);
		}
	}
	else
	{
		SendBuf = " \r\n";
		SendData(pEntry->send_timeout);
	}

	// next goes attachments (if they are)
	for (FileId = 0; FileId < mail.attachments.size(); FileId++)
	{
		pos = mail.attachments[FileId].find_last_of("\\");
		if (pos == string::npos) FileName = mail.attachments[FileId];
		else FileName = mail.attachments[FileId].substr(pos + 1);

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

		SendData(pEntry->send_timeout);

		// opening the file:
		hFile = fopen(mail.attachments[FileId].c_str(), "rb");
		if (hFile == NULL)
			return FAIL(FILE_NOT_EXIST);

		// get file size:
		fseek(hFile, 0, SEEK_END);
		FileSize = ftell(hFile);
		fseek(hFile, 0, SEEK_SET);

		MsgPart = 0;
		for (i = 0; i < FileSize / 54 + 1; i++)
		{
			res = fread(FileBuf, sizeof(char), 54, hFile);
			MsgPart ? SendBuf += base64_encode(reinterpret_cast<const unsigned char*>(FileBuf), res)
				: SendBuf += base64_encode(reinterpret_cast<const unsigned char*>(FileBuf), res);
			SendBuf += "\r\n";
			MsgPart += res + 2;
			if (MsgPart >= BUFFER_SIZE / 2)
			{ // sending part of the message
				MsgPart = 0;
				SendData(pEntry->send_timeout); // FileBuf, FileName, fclose(hFile);
			}
		}
		if (MsgPart)
		{
			SendData(pEntry->send_timeout); // FileBuf, FileName, fclose(hFile);
		}
		fclose(hFile);
		hFile = NULL;
	}
	delete[] FileBuf;
	FileBuf = NULL;

	// sending last message block (if there is one or more attachments)
	if (mail.attachments.size())
	{
		SendBuf = "\r\n--" + BOUNDARY_TEXT + "--\r\n";
		SendData(pEntry->send_timeout);
	}

	pEntry = FindCommandEntry(command_DATAEND);
	// <CRLF> . <CRLF>
	SendBuf = "\r\n.\r\n";
	SendData(pEntry->send_timeout);
	ReceiveData(pEntry);

	return SUCCESS;
}

RETCODE SMTP::SendData(int send_timeout)
{
	int idx = 0, res, nLeft = SendBuf.size();
	fd_set fdwrite;
	timeval time;

	time.tv_sec = send_timeout;
	time.tv_usec = 0;

	if (SendBuf.empty())
		return FAIL(SENDBUF_IS_EMPTY);

	while (nLeft > 0)
	{
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
			res = send(hSocket, &SendBuf[idx], nLeft, 0);
			if (res == SOCKET_ERROR || res == 0)
			{
				FD_CLR(hSocket, &fdwrite);
				return FAIL(WSA_SEND);
			}
			nLeft -= res;
			idx += res;
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

void SMTP::SayHello()
{
	Command_Entry* pEntry = FindCommandEntry(command_EHLO);
	SendBuf = "EHLO ";
	SendBuf += GetLocalHostName().empty() ? "localhost" : m_sLocalHostName;
	SendBuf += "\r\n";
	SendData(pEntry->send_timeout);
	ReceiveData(pEntry);
	server.isConnected = true;
}

void SMTP::SayQuit()
{
	// ***** CLOSING CONNECTION *****

	Command_Entry* pEntry = FindCommandEntry(command_QUIT);
	// QUIT <CRLF>
	SendBuf = "QUIT\r\n";
	server.isConnected = false;
	SendData(pEntry->send_timeout);
	ReceiveData(pEntry);
}

RETCODE SMTP::ReceiveData(const Command_Entry* pEntry)
{
	int res = 0;
	fd_set fdread;
	timeval time;

	time.tv_sec = pEntry->recv_timeout;
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

	stringstream istr(RecvBuf);
	vector <string> ostr;
	string to;
	while (getline(istr, to, '\n')) {
		ostr.push_back(to);
	}
	string lastLine = ostr.back();

	int reply_code = lastLine[0] * 100 + lastLine[1] * 10 + lastLine[2];

	if (reply_code != pEntry->valid_reply_code)
	{
		return FAIL(pEntry->error);
	}

	return SUCCESS;
}
