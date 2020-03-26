#include "email.h"
#include "test.h"

int main()
{
	if (TEST::GMAIL::tls_test_text())
		std::cout << "failed \n";

	if (TEST::GMAIL::ssl_test_text())
		std::cout << "failed \n";

	return 0;
}
