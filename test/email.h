#pragma once
#ifndef _TEST_H_
#define _TEST_H_
#include "utest.h"
#include "protocol/smtp/client.h"
#include <iostream>
/*
	TESTS SHOULD COVER THE FOLLOWING OPTIONS

	- default value

	- set value (if possible)
	- add value (if possible)
	- delete value (if possible)
	- modify value (if possible)

	- add value before deleting (if possible)
	- deleting value before modify (if possible)
	- add value before deleting (if possible)

	- exceptional situations (all that was previously 
	  considered impossible) such as
		- delete of empty
		- read of empty
		- modify of ompty
		- other exceptions
*/
struct TEST 
{
	struct Utils
	{
		static void ModMsgLine(Protocol::SMTP::MAIL& mail, unsigned int Line, const char* Text);
		static void DelMsgLine(Protocol::SMTP::MAIL& mail, unsigned int Line);
		static void AddRecipient(Protocol::SMTP::MAIL& mail, const char* email, const char* name = "");
		static void AddCCRecipient(Protocol::SMTP::MAIL& mail, const char* email, const char* name = "");
		static void AddBCCRecipient(Protocol::SMTP::MAIL& mail, const char* email, const char* name = "");
		static void AddAttachment(Protocol::SMTP::MAIL& mail, const char* path);
		static void SetAuth(Protocol::SMTP::Client& client, const char* login, const char* pass);
		static void ClientSend(Protocol::SMTP::Client client, Protocol::SMTP::MAIL& mail);
	};
	struct StructOfMail
	{
		static void SetSenderName();
		static void SetSenderMail();
		static void SetReplyTo();
		static void SetSubject();
		
		static void RecipientsDefault();
		static void AddRecipient();
		static void DelEmptyRecipients();
		static void DelRecipients();
		static void AddRecipientBeforeDel();

		static void CCRecipientsDefault();
		static void AddCCRecipient();
		static void DelEmptyCCRecipients();
		static void DelCCRecipients();
		static void AddCCRecipientBeforeDel();

		static void BCCRecipientsDefault();
		static void AddBCCRecipient();
		static void DelEmptyBCCRecipients();
		static void DelBCCRecipients();
		static void AddBCCRecipientBeforeDel();

		static void DefXPriority();
		static void SetXPriority();
		static void DefXMailer();
		static void SetXMailer();

		static void DefLetterBody();
		static void AddMsgLine();
		static void ModMsgLine();
		static void DelMsgLine();
		static void DelEmptyMsgLine();
		static void DelMsgLines();
		static void DelEmptyMsgLines();

		static void DefAttachment();
		static void AddAttachment();
		static void DelAttachments();
		static void DelEmptyAttachments();
	};
	struct Client
	{
		static void DefAuth();
		static void SetAuth();
		
		static void SendExceptionss();
	};
};
#endif