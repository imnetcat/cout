#pragma once
#ifndef _TEST_H_
#define _TEST_H_

#include "email.h"
#include <iostream>

class TEST {
public:
	static void text(EMAIL mail);
	static void attachments(EMAIL mail);
	struct GMAIL {
		static bool tls_test_text();
		static bool tls_test_attachments();
		static bool ssl_test_text();
		static bool ssl_test_attachments();
	};
private:
	struct AUTH {
		static const string email;
		static const string password;
	};
	static const string recipient_email;
};

#endif
