
#include "errors.h"
using namespace CORE;

#include <iostream>
using namespace std;

ERR ERRORS::ErrorCode;

int ERRORS::processing(ERR err_) {
	ErrorCode = err_;
	addtrace();
	return ErrorCode;
}

void ERRORS::addtrace() {
	cout << "Error (" << GetErrorText() << ")" << endl;
}

string ERRORS::GetErrorText()
{
	stringstream stream;
	stream << ErrorCode;
	return stream.str();
}
