#pragma once
#ifndef _BASE64_H_
#define _BASE64_H_
#include <string>

class BASE64
{
public:
	static inline bool is_base64(unsigned char c);
	static std::string base64_encode(unsigned char const*, unsigned int len);
	static std::string base64_decode(std::string const& s);

private:
	static const std::string base64_chars;
};

#endif