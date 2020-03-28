#include "email.h"
#include "test.h"

int main()
{
#ifdef INDEBUG
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif
	if (TEST::GMAIL::tls_test_text())
		std::cout << "failed \n";

	if (TEST::GMAIL::ssl_test_text())
		std::cout << "failed \n";

	return 0;
}
