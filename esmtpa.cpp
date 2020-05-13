#include "esmtpa.h"


RETCODE ESMTPA::AuthPlain()
{
	DEBUG_LOG(1, "Аунтификация AUTH PLAIN");
	string s = server.auth.login + "^" + server.auth.login + "^" + server.auth.password;
	unsigned int length = s.size();
	unsigned char *ustrLogin = UTILS::StringToUnsignedChar(s);
	for (unsigned int i = 0; i < length; i++)
	{
		if (ustrLogin[i] == 94) ustrLogin[i] = 0;
	}
	std::string encoded_login = BASE64::base64_encode(ustrLogin, length);
	delete[] ustrLogin;
	SendBuf = "AUTH PLAIN " + encoded_login + "\r\n";

	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(235))
		return FAIL(AUTH_PLAIN_FAILED);

	return SUCCESS;
}

RETCODE ESMTPA::AuthLogin()
{
	DEBUG_LOG(1, "Аунтификация AUTH LOGIN");
	SendBuf = "AUTH LOGIN\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(334))
		return FAIL(AUTH_LOGIN_FAILED);

	DEBUG_LOG(1, "Отправка логина");
	string encoded_login = BASE64::base64_encode(reinterpret_cast<const unsigned char*>(server.auth.login.c_str()), server.auth.login.size());
	SendBuf = encoded_login + "\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(334))
		return FAIL(UNDEF_XYZ_RESPONSE);

	DEBUG_LOG(1, "Отправка пароля");
	string encoded_password = BASE64::base64_encode(reinterpret_cast<const unsigned char*>(server.auth.password.c_str()), server.auth.password.size());
	SendBuf = encoded_password + "\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(235))
	{
		DEBUG_LOG(1, "Неверный пароль/логин или не запрещён доступ из небезопасных приложений");
		return FAIL(BAD_LOGIN_PASS);
	}

	return SUCCESS;
}

RETCODE ESMTPA::CramMD5()
{
	DEBUG_LOG(1, "Аунтификация AUTH CRAM-MD5");
	SendBuf = "AUTH CRAM-MD5\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(334))
		return FAIL(AUTH_CRAMMD5_FAILED);

	DEBUG_LOG(1, "Генерация токена");

	std::string encoded_challenge = RecvBuf;
	encoded_challenge = encoded_challenge.substr(4);
	std::string decoded_challenge = BASE64::base64_decode(encoded_challenge);

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
	encoded_challenge = BASE64::base64_encode(reinterpret_cast<const unsigned char*>(decoded_challenge.c_str()), decoded_challenge.size());

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(1, "Оправка токена " + encoded_challenge);

	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(334))
		return FAIL(AUTH_CRAMMD5_FAILED);

	return SUCCESS;
}

RETCODE ESMTPA::DigestMD5()
{
	DEBUG_LOG(1, "Аунтификация AUTH DIGEST-MD5");
	SendBuf = "AUTH DIGEST-MD5\r\n";
	if (SendData(5 * 60))
		return FAIL(SMTP_SEND_DATA);
	if (ReceiveData(5 * 60))
		return FAIL(SMTP_RECV_DATA);

	if (!isRetCodeValid(335))
		return FAIL(DIGESTMD5_FAILED);

	DEBUG_LOG(1, "Генерация токена");

	string encoded_challenge = RecvBuf;
	encoded_challenge = encoded_challenge.substr(4);
	string decoded_challenge = BASE64::base64_decode(encoded_challenge);

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
	encoded_challenge = BASE64::base64_encode(ustrDigest, resstr.size());
	delete[] ustrDigest;

	SendBuf = encoded_challenge + "\r\n";

	DEBUG_LOG(1, "Оправка токена " + encoded_challenge);

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

RETCODE ESMTPA::Command(COMMAND command)
{
	ERR	error;

	switch (command)
	{
	case AUTHPLAIN:
		if (AuthPlain())
			return FAIL(AUTH_PLAIN_FAILED);
		break;
	case AUTHLOGIN:
		if (AuthLogin())
			return FAIL(AUTH_LOGIN_FAILED);
		break;
	case AUTHCRAMMD5:
		if (CramMD5())
			return FAIL(AUTH_CRAMMD5_FAILED);
		break;
	case AUTHDIGESTMD5:
		if (DigestMD5())
			return FAIL(AUTH_DIGESTMD5_FAILED);
		break;
	default:
		return ESMTP::Command(command);
		break;
	}

	return SUCCESS;
}
