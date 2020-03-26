#include "smtp.h"

Command_Entry command_list[] =
{
	{command_INIT,          0,		 5 * 60,  220, SERVER_NOT_RESPONDING},
	{command_EHLO,          5 * 60,  5 * 60,  250, COMMAND_EHLO},
	{command_AUTHPLAIN,     5 * 60,  5 * 60,  235, COMMAND_AUTH_PLAIN},
	{command_AUTHLOGIN,     5 * 60,  5 * 60,  334, COMMAND_AUTH_LOGIN},
	{command_AUTHCRAMMD5,   5 * 60,  5 * 60,  334, COMMAND_AUTH_CRAMMD5},
	{command_AUTHDIGESTMD5, 5 * 60,  5 * 60,  334, COMMAND_AUTH_DIGESTMD5},
	{command_DIGESTMD5,     5 * 60,  5 * 60,  335, COMMAND_DIGESTMD5},
	{command_USER,          5 * 60,  5 * 60,  334, UNDEF_XYZ_RESPONSE},
	{command_PASSWORD,      5 * 60,  5 * 60,  235, BAD_LOGIN_PASS},
	{command_MAILFROM,      5 * 60,  5 * 60,  250, COMMAND_MAIL_FROM},
	{command_RCPTTO,        5 * 60,  5 * 60,  250, COMMAND_RCPT_TO},
	{command_DATA,          5 * 60,  2 * 60,  354, COMMAND_DATA},
	{command_DATABLOCK,     3 * 60,  0,			0, COMMAND_DATABLOCK},	// Here the valid_reply_code is set to zero because there are no replies when sending data blocks
	{command_DATAEND,       3 * 60,  10 * 60, 250, MSG_BODY_ERROR},
	{command_QUIT,          5 * 60,  5 * 60,  221, COMMAND_QUIT},
	{command_STARTTLS,      5 * 60,  5 * 60,  220, COMMAND_EHLO_STARTTLS}
};

Command_Entry* SMTP::FindCommandEntry(SMTP_COMMAND command)
{
	Command_Entry* pEntry = NULL;
	for (size_t i = 0; i < sizeof(command_list) / sizeof(command_list[0]); ++i)
	{
		if (command_list[i].command == command)
		{
			pEntry = &command_list[i];
			break;
		}
	}
	assert(pEntry != NULL);
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

	Buf_Init();

}

SMTP::~SMTP()
{
	if (server.isConnected) DisconnectRemoteServer();

	if (RecvBuf)
	{
		delete[] RecvBuf;
		RecvBuf = NULL;
	}

	WSACleanup();
}


// A simple string match
bool SMTP::IsCommandSupported(const char* response, const char* command)
{
	assert(response != NULL && command != NULL);
	if (response == NULL || command == NULL)
		return false;
	int res_len = strlen(response);
	int key_len = strlen(command);
	if (res_len < key_len)
		return false;
	int pos = 0;
	for (; pos < res_len - key_len + 1; ++pos)
	{
		if (_strnicmp(command, response + pos, key_len) == 0)
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

RETCODE SMTP::Buf_Init()
{
	if ((RecvBuf = new char[BUFFER_SIZE]) == NULL)
		return FAIL(LACK_OF_MEMORY);

	return SUCCESS;
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

RETCODE SMTP::InitHandshake()
{
	Command_Entry* pEntry = FindCommandEntry(command_INIT);
	ReceiveResponse(pEntry);

	SayHello();

	return SUCCESS;
}

RETCODE SMTP::Handshake()
{
	Command_Entry* pEntry = nullptr;
	bool authenticate = server.isAuth;
	if (authenticate && IsCommandSupported(RecvBuf, "AUTH") == true)
	{
		if (!server.auth.login.size())
			return FAIL(UNDEF_LOGIN);

		if (!server.auth.password.size())
			return FAIL(UNDEF_PASSWORD);

		if (IsCommandSupported(RecvBuf, "LOGIN") == true)
		{
			pEntry = FindCommandEntry(command_AUTHLOGIN);
			SendBuf = "AUTH LOGIN\r\n";
			SendData(pEntry->send_timeout);
			ReceiveResponse(pEntry);

			// send login:
			std::string encoded_login = base64_encode(reinterpret_cast<const unsigned char*>(server.auth.login.c_str()), server.auth.login.size());
			pEntry = FindCommandEntry(command_USER);
			SendBuf = encoded_login + "\r\n";
			SendData(pEntry->send_timeout);
			ReceiveResponse(pEntry);

			// send password:
			std::string encoded_password = base64_encode(reinterpret_cast<const unsigned char*>(server.auth.password.c_str()), server.auth.password.size());
			pEntry = FindCommandEntry(command_PASSWORD);
			SendBuf = encoded_password + "\r\n";
			SendData(pEntry->send_timeout);
			ReceiveResponse(pEntry);
		}
		else if (IsCommandSupported(RecvBuf, "PLAIN") == true)
		{
			pEntry = FindCommandEntry(command_AUTHPLAIN);
			SendBuf = server.auth.login + "^" + server.auth.login + "^" + server.auth.password;
			unsigned int length = SendBuf.size();
			unsigned char *ustrLogin = CharToUnsignedChar(SendBuf.c_str());
			for (unsigned int i = 0; i < length; i++)
			{
				if (ustrLogin[i] == 94) ustrLogin[i] = 0;
			}
			std::string encoded_login = base64_encode(ustrLogin, length);
			delete[] ustrLogin;
			SendBuf = "AUTH PLAIN " + encoded_login + "\r\n";
			SendData(pEntry->send_timeout);
			ReceiveResponse(pEntry);
		}
		else if (IsCommandSupported(RecvBuf, "CRAM-MD5") == true)
		{
			pEntry = FindCommandEntry(command_AUTHCRAMMD5);
			SendBuf = "AUTH CRAM-MD5\r\n";
			SendData(pEntry->send_timeout);
			ReceiveResponse(pEntry);

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
			if (!ustrChallenge || !ustrPassword)
				return FAIL(BAD_LOGIN_PASSWORD);

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
			pEntry = FindCommandEntry(command_PASSWORD);
			SendData(pEntry->send_timeout);
			ReceiveResponse(pEntry);
		}
		else if (IsCommandSupported(RecvBuf, "DIGEST-MD5") == true)
		{
			pEntry = FindCommandEntry(command_DIGESTMD5);
			SendBuf = "AUTH DIGEST-MD5\r\n";
			SendData(pEntry->send_timeout);
			ReceiveResponse(pEntry);

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
			if (find < 0)
				return FAIL(BAD_DIGEST_RESPONSE);
			std::string nonce = decoded_challenge.substr(find + 7);
			find = nonce.find("\"");
			if (find < 0)
				return FAIL(BAD_DIGEST_RESPONSE);
			nonce = nonce.substr(0, find);

			//Get the realm (optional)
			std::string realm;
			find = decoded_challenge.find("realm");
			if (find >= 0) {
				realm = decoded_challenge.substr(find + 7);
				find = realm.find("\"");
				if (find < 0)
					return FAIL(BAD_DIGEST_RESPONSE);
				realm = realm.substr(0, find);
			}

			//Create a cnonce
			char cnonce[17], nc[9];
			snprintf(cnonce, 17, "%x", (unsigned int)time(NULL));

			//Set nonce count
			snprintf(nc, 9, "%08d", 1);

			//Set QOP
			std::string qop = "auth";

			//Get server address and set uri
			//Skip this step during test
#ifdef __linux__
			socklen_t len;
#else
			int len;
#endif
			struct sockaddr_storage addr;
			len = sizeof addr;
			if (!getpeername(hSocket, (struct sockaddr*)&addr, &len))
				return FAIL(BAD_SERVER_NAME);

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
			unsigned char *ustrCNonce = CharToUnsignedChar(cnonce);
			unsigned char *ustrUri = CharToUnsignedChar(uri.c_str());
			unsigned char *ustrNc = CharToUnsignedChar(nc);
			unsigned char *ustrQop = CharToUnsignedChar(qop.c_str());
			if (!ustrRealm || !ustrUsername || !ustrPassword || !ustrNonce || !ustrCNonce || !ustrUri || !ustrNc || !ustrQop)
				return FAIL(BAD_LOGIN_PASSWORD);

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
			md5a1b.update(ustrCNonce, strlen(cnonce));
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
			md5.update(ustrNc, strlen(nc));
			md5.update((unsigned char*)":", 1);
			md5.update(ustrCNonce, strlen(cnonce));
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

			//send the response
			if (strstr(RecvBuf, "charset") >= 0) SendBuf = "charset=utf-8,username=\"" + server.auth.login + "\"";
			else SendBuf = "username=\"" + server.auth.login + "\"";
			if (!realm.empty()) {
				snprintf(RecvBuf, BUFFER_SIZE, ",realm=\"%s\"", realm.c_str());
				SendBuf += RecvBuf;
			}
			snprintf(RecvBuf, BUFFER_SIZE, ",nonce=\"%s\"", nonce.c_str());
			SendBuf += RecvBuf;
			snprintf(RecvBuf, BUFFER_SIZE, ",nc=%s", nc);
			SendBuf += RecvBuf;
			snprintf(RecvBuf, BUFFER_SIZE, ",cnonce=\"%s\"", cnonce);
			SendBuf += RecvBuf;
			snprintf(RecvBuf, BUFFER_SIZE, ",digest-uri=\"%s\"", uri.c_str());
			SendBuf += RecvBuf;
			snprintf(RecvBuf, BUFFER_SIZE, ",response=%s", decoded_challenge.c_str());
			SendBuf += RecvBuf;
			snprintf(RecvBuf, BUFFER_SIZE, ",qop=%s", qop.c_str());
			SendBuf += RecvBuf;
			unsigned char *ustrDigest = CharToUnsignedChar(SendBuf.c_str());
			encoded_challenge = base64_encode(ustrDigest, SendBuf.size());
			delete[] ustrDigest;
			SendBuf = encoded_challenge + "\r\n";
			pEntry = FindCommandEntry(command_DIGESTMD5);
			SendData(pEntry->send_timeout);
			ReceiveResponse(pEntry);

			//Send completion carraige return
			SendBuf = "\r\n";
			pEntry = FindCommandEntry(command_PASSWORD);
			SendData(pEntry->send_timeout);
			ReceiveResponse(pEntry);
		}
		else return FAIL(LOGIN_NOT_SUPPORTED);
	}

	return SUCCESS;
}

void SMTP::DisconnectRemoteServer()
{
	if (server.isConnected) SayQuit();
	if (hSocket)
	{
		closesocket(hSocket);
	}
	hSocket = INVALID_SOCKET;
}

int SMTP::SmtpXYZdigits()
{
	assert(RecvBuf);
	if (RecvBuf == NULL)
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

RETCODE SMTP::Send(MAIL mail)
{
	Connect();
	InitHandshake();
	Handshake();
	WrappedSend(mail);
	return SUCCESS;
}

RETCODE SMTP::WrappedSend(MAIL mail)
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

	// MAIL <SP> FROM:<reverse-path> <CRLF>
	if (!mail.senderMail.size())
		return FAIL(UNDEF_MAIL_FROM);
	Command_Entry* pEntry = FindCommandEntry(command_MAILFROM);
	SendBuf = "MAIL FROM:<" + mail.senderMail + ">\r\n";
	SendData(pEntry->send_timeout);
	ReceiveResponse(pEntry);

	// RCPT <SP> TO:<forward-path> <CRLF>
	if (!(rcpt_count = mail.recipients.size()))
		return FAIL(UNDEF_RECIPIENTS);
	pEntry = FindCommandEntry(command_RCPTTO);
	for (i = 0; i < mail.recipients.size(); i++)
	{
		SendBuf = "RCPT TO:<" + mail.recipients.at(i).Mail + ">\r\n";
		SendData(pEntry->send_timeout);
		ReceiveResponse(pEntry);
	}

	for (i = 0; i < mail.ccrecipients.size(); i++)
	{
		SendBuf = "RCPT TO:<" + mail.ccrecipients.at(i).Mail + ">\r\n";
		SendData(pEntry->send_timeout);
		ReceiveResponse(pEntry);
	}

	for (i = 0; i < mail.bccrecipients.size(); i++)
	{
		SendBuf = "RCPT TO:<" + mail.bccrecipients.at(i).Mail + ">\r\n";
		SendData(pEntry->send_timeout);
		ReceiveResponse(pEntry);
	}

	pEntry = FindCommandEntry(command_DATA);
	// DATA <CRLF>
	SendBuf = "DATA\r\n";
	SendData(pEntry->send_timeout);
	ReceiveResponse(pEntry);

	pEntry = FindCommandEntry(command_DATABLOCK);
	// send header(s)
	SendBuf = mail.header;
	SendData(pEntry->send_timeout);

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
	ReceiveResponse(pEntry);

	return SUCCESS;
}

RETCODE SMTP::ReceiveData(int recv_timeout)
{
	int res = 0;
	fd_set fdread;
	timeval time;

	time.tv_sec = recv_timeout;
	time.tv_usec = 0;

	assert(RecvBuf);

	if (RecvBuf == NULL)
		return FAIL(RECVBUF_IS_EMPTY);

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
		res = recv(hSocket, RecvBuf, BUFFER_SIZE, 0);
		if (res == SOCKET_ERROR)
		{
			FD_CLR(hSocket, &fdread);
			return FAIL(WSA_RECV);
		}
	}

	FD_CLR(hSocket, &fdread);
	RecvBuf[res] = 0;
	if (res == 0)
	{
		return FAIL(CONNECTION_CLOSED);
	}

	return SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: SendData
// DESCRIPTION: Sends data from SendBuf buffer.
//   ARGUMENTS: none
// USES GLOBAL: SendBuf
// MODIFIES GL: none
//     RETURNS: void
//      AUTHOR: Jakub Piwowarczyk
// AUTHOR/DATE: JP 2010-01-28
////////////////////////////////////////////////////////////////////////////////
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

	OutputDebugStringA(SendBuf.c_str());
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
	ReceiveResponse(pEntry);
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
	ReceiveResponse(pEntry);
}

RETCODE SMTP::ReceiveResponse(Command_Entry* pEntry)
{
	std::string line;
	int reply_code = 0;
	bool bFinish = false;
	while (!bFinish)
	{
		ReceiveData(pEntry->send_timeout);
		line.append(RecvBuf);
		size_t len = line.length();
		size_t begin = 0;
		size_t offset = 0;

		while (1) // loop for all lines
		{
			while (offset + 1 < len)
			{
				if (line[offset] == '\r' && line[offset + 1] == '\n')
					break;
				++offset;
			}
			if (offset + 1 < len) // we found a line
			{
				// see if this is the last line
				// the last line must match the pattern: XYZ<SP>*<CRLF> or XYZ<CRLF> where XYZ is a string of 3 digits 
				offset += 2; // skip <CRLF>
				if (offset - begin >= 5)
				{
					if (isdigit(line[begin]) && isdigit(line[begin + 1]) && isdigit(line[begin + 2]))
					{
						// this is the last line
						if (offset - begin == 5 || line[begin + 3] == ' ')
						{
							reply_code = (line[begin] - '0') * 100 + (line[begin + 1] - '0') * 10 + line[begin + 2] - '0';
							bFinish = true;
							break;
						}
					}
				}
				begin = offset;	// try to find next line
			}
			else // we haven't received the last line, so we need to receive more data 
			{
				break;
			}
		}
	}
	snprintf(RecvBuf, BUFFER_SIZE, line.c_str());
	OutputDebugStringA(RecvBuf);
	if (reply_code != pEntry->valid_reply_code)
	{
		return FAIL(pEntry->error);
	}

	return SUCCESS;
}
