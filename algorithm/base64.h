#pragma once
#ifndef _Base64_H_
#define _Base64_H_
#include <string>
namespace Core
{
	class Base64
	{
	private:
		// check for that is base64-char
		static inline bool check(unsigned char c);

	public:
		// decode and encode base64
		static std::string Encode(unsigned char const*, size_t len);
		static std::string Decode(std::string const& s);

	private:
		static const std::string base64_chars;
	};
}
#endif