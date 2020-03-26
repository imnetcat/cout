#include "email.h"
#include "test.h"

int main()
{
	if (!TEST::GMAIL::tls_test_text())
		std::cout << "gmail tls_test_text failed \n";

	if (!TEST::GMAIL::ssl_test_text())
		std::cout << "gmail ssl_test_text failed \n";

	return 0;
}
