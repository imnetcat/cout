#pragma once
#ifndef _TEST_H_
#define _TEST_H_

#include "core.h"
#include "email.h"
#include <iostream>

class TESTS {
public:
	static void text(EMAIL &mail);
	static void attachments(EMAIL &mail);
	struct GMAIL {
		static void tls_test_text();
		static void tls_test_attachments();
		static void ssl_test_text();
		static void ssl_test_attachments();
	};
private:
	struct AUTH {
		static const string email;
		static const string password;
	};
	static const string recipient_email;
};

#endif