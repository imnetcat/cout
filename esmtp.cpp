#include "esmtp.h"

using namespace std;

ESMTP::ESMTP()
{

}
ESMTP::~ESMTP()
{

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

RETCODE ESMTP::Command(COMMAND command)
{
	ERR	error;

	switch (command)
	{
	case ESMTP::EHLO:
		if (Ehlo())
			return FAIL(EHLO_FAILED);
		break;
	default:
		return SMTP::Command(command);
		break;
	}

	return SUCCESS;
}

RETCODE ESMTP::Handshake()
{
	DEBUG_LOG(1, "Рукопожатие с сервером по протоколу ESMTP");
	if (Command(INIT))
		return FAIL(SMTP_COMM);
	if (Command(EHLO))
		return FAIL(SMTP_COMM);

	return SUCCESS;
}

RETCODE ESMTP::Send(MAIL m)
{
	mail = m;
	if (Connect())
		return FAIL(STMP_CONNECT);

	Handshake();
	
	if (SendMail())
		return FAIL(SMTP_SEND_MAIL);

	return SUCCESS;
}
