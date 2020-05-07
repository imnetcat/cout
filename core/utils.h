#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_
#include <string>
#include "base64.h"
#include "md5.h"

class UTILS
{
public:
	static unsigned char* StringToUnsignedChar(std::string strIn);

private:
	static const std::string base64_chars;
};

#endif
