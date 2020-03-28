#include "utils.h"

unsigned char* UTILS::StringToUnsignedChar(string strIn)
{
	int length = strIn.size();
	unsigned char * temp = new unsigned char[length];

	for (int i = 0; i < length; ++i)
	{
		temp[i] = static_cast<unsigned char>(strIn[i]);
	}

	return temp;
}