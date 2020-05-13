#include "esmtpsa.h"


RETCODE ESMTPSA::Send(MAIL m, SMTP_SECURITY_TYPE sec)
{
	mail = m;
	if (Connect())
		return FAIL(STMP_CONNECT);

	DEBUG_LOG(1, "Инициализация openssl");
	InitOpenSSL();

	if (sec == USE_SSL)
	{
		SetUpSSL();
	}

	Handshake();

	if (sec == USE_TLS)
	{
		SetUpTLS();
	}

	DEBUG_LOG(1, "Отправка письма");

	if (SendMail())
		return FAIL(SMTP_SEND_MAIL);

	return SUCCESS;
}
