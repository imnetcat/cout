#pragma once
#ifndef _ERRORS_H_
#define _ERRORS_H_
#include <string>
#include <sstream>
using namespace std;

#define SUCCESS 0
#define FAIL(code) ERRORS::processing(code)

using RETCODE = unsigned int;

enum ERR
{
	CSMTP_NO_ERROR = 0,
	//Unable to initialise winsock2
	WSA_STARTUP,
	//Wrong version of the winsock2
	WSA_VER,
	//Function send() failed
	WSA_SEND,
	//Function recv() failed
	WSA_RECV,
	//Function connect failed
	WSA_CONNECT,
	//Unable to determine remote server
	WSA_GETHOSTBY_NAME_ADDR,
	//Invalid winsock2 socket
	WSA_INVALID_SOCKET,
	//Function hostname() failed
	WSA_HOSTNAME,
	//Function ioctlsocket() failed
	WSA_IOCTLSOCKET,
	//Improper IPv4 address
	BAD_IPV4_ADDR,
	// 
	SELECT_TIMEOUT,
	// 
	WSA_SELECT,
	//Undefined message header
	UNDEF_MSG_HEADER,
	//Undefined mail sender
	UNDEF_MAIL_FROM,
	//Undefined message subject
	UNDEF_SUBJECT,
	//Undefined at least one reciepent
	UNDEF_RECIPIENTS,
	//Undefined recipent mail
	UNDEF_RECIPIENT_MAIL,
	//Undefined user login
	UNDEF_LOGIN,
	//Undefined user password
	UNDEF_PASSWORD,
	//Invalid user login or password
	BAD_LOGIN_PASSWORD,
	//Server returned a bad digest MD5 response
	BAD_DIGEST_RESPONSE,
	//Unable to determine server name for digest MD5 response
	BAD_SERVER_NAME,

	INIT_FAILED,
	//Server returned error after sending MAIL FROM
	MAIL_FROM_FAILED,
	//Server returned error after sending EHLO
	EHLO_FAILED,
	//Server returned error after sending AUTH PLAIN
	AUTH_PLAIN_FAILED,
	//Server returned error after sending AUTH LOGIN
	AUTH_LOGIN_FAILED,
	//Server returned error after sending AUTH CRAM-MD5
	AUTH_CRAMMD5_FAILED,
	//Server returned error after sending AUTH DIGEST-MD5
	AUTH_DIGESTMD5_FAILED,
	//Server returned error after sending MD5 DIGEST
	DIGESTMD5_FAILED,
	//Server returned error after sending DATA
	DATA_FAILED,
	//Server returned error after sending QUIT
	QUIT_FAILED,
	//Server returned error after sending RCPT TO
	RCPT_TO_FAILED,
	//Server returned error after sending STARTTLS
	STARTTLS_FAILED,
	//Failed to send data block
	DATABLOCK_FAILED,
	//Error in message body
	MSG_BODY_ERROR,
	//Server has closed the connection
	CONNECTION_CLOSED,
	//Server is not ready
	SERVER_NOT_READY,
	//Server not responding
	SERVER_NOT_RESPONDING,
	//Attachment file does not exist
	FILE_NOT_EXIST,
	//Message is too big
	MSG_TOO_BIG,
	//Bad login or password
	BAD_LOGIN_PASS,
	//Undefined xyz SMTP response
	UNDEF_XYZ_RESPONSE,
	//Lack of memory
	LACK_OF_MEMORY,
	//time() error
	TIME_ERROR,
	//SendBuf is empty
	SENDBUF_IS_EMPTY,
	// Specified element index is out of vector size
	OUT_OF_VECTOR_RANGE,
	//SSL problem
	SSL_PROBLEM,
	//The STARTTLS command is not supported by the server
	STARTTLS_NOT_SUPPORTED,
	//AUTH LOGIN is not supported by the server
	LOGIN_NOT_SUPPORTED,

	STMP_CONNECT = 100,
	SMTP_COMM,
	SMTP_AUTH,
	SMTP_WRAPPED_SEND,
	SMTP_SEND,
	SMTP_SEND_DATA,
	SMTP_RECV_DATA,
	SMTP_SEND_DATA_NOSEC,
	SMTP_RECV_DATA_NOSEC,
	SMTP_SEND_DATA_SEC,
	SMTP_RECV_DATA_SEC,
	SMTP_CREATE_HEADER,
	SMTP_UNDEF_COMM,

	EMAIL_SEND = 150,
	EMAIL_UNDEF_SENDER,
	EMAIL_UNDEF_RECEIVER
};

class ERRORS
{
public:
	static int processing(ERR err_);
	static string GetErrorText(void);
	static void addtrace();
private:
	static ERR ErrorCode;
};

#endif
