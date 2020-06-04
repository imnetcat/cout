#include "email.h"
#include "utest.h"
#include "tests.h"

int main()
{
	try 
	{
#ifdef INDEBUG
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		TESTS::GMAIL::tls_test_text();
		TESTS::GMAIL::ssl_test_text();
		TESTS::GMAIL::tls_test_attachments();
		TESTS::GMAIL::ssl_test_attachments();
#endif
	}
	catch (ERR e) 
	{
		ERRORS::processing(e);
	}
	catch (...)
	{
		// TODO: all standart exception proccesing
	}
	return 0;
}
