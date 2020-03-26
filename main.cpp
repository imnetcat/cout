#include "email.h"
#include "test.h"

int main()
{
	if (!TEST::GMAIL::tls_test_text())
		return 1;

	if (!TEST::GMAIL::ssl_test_text())
		return 1;

	return 0;
}
