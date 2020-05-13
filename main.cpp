#include "email.h"

int main()
{
	try 
	{
#ifdef INDEBUG
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
#endif
		//if (TEST::GMAIL::tls_test_text())
		//	std::cout << "failed \n";

		//if (TEST::GMAIL::ssl_test_text())
		//	std::cout << "failed \n";

		//if (TEST::GMAIL::tls_test_attachments())
		//	std::cout << "failed \n";

		//if (TEST::GMAIL::ssl_test_attachments())
		//	std::cout << "failed \n";
	}
	catch (ERR e) 
	{
		ERRORS::processing(e);
	}
	return 0;
}
