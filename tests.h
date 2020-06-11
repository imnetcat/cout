#pragma once
#ifndef _TEST_H_
#define _TEST_H_
#include "utest.h"
#include "email.h"
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
		static void DefServer();
		static void SetServer();

		static void DefAuth();
		static void SetAuth();

		static void DefSecurity();
		static void SetSecurity();

		static void SendExceptions();
		static void SendCorrectly();
	};
};
#endif