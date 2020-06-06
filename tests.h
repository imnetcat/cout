#pragma once
#ifndef _TEST_H_
#define _TEST_H_

#include "core.h"
#include "email.h"
#include <iostream>

class TESTS {
public:
	static void text(EMAIL::MAIL &mail);
	static void attachments(EMAIL::MAIL &mail);
	struct GMAIL {
		static void tls_test_text();
		static void tls_test_attachments();
		static void ssl_test_text();
		static void ssl_test_attachments();
	};
private:
	struct AUTH {
		static const std::string email;
		static const std::string password;
	};
	static const std::string recipient_email;
};

#endif