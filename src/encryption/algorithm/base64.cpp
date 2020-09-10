#include "base64.h"

using namespace std;
using namespace Cout::Encryption::Algorithm;

const string Base64::base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


inline bool Base64::check(unsigned char c)
{
	return (isalnum(c) || (c == '+') || (c == '/'));
}

Cout::UnsignedBinary Base64::Encode(const Cout::UnsignedBinary& data_to_encode)
{
	Cout::UnsignedBinary res;
	auto ptr = data_to_encode.data();
	auto length = data_to_encode.size();
	unsigned int index = 0;
	int i = 0, j = 0;
	unsigned char char_array_3[3], char_array_4[4];

	while (length--)
	{
		char_array_3[i++] = *(ptr++);
		if (i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
			{
				res.push_back(base64_chars[char_array_4[i]]);
				index++;
			}
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
		{
			res.push_back(base64_chars[char_array_4[j]]);
			index++;
		}

		while ((i++ < 3))
		{
			res.push_back('=');
			index++;
		}

	}

	return res;
}

Cout::UnsignedBinary Base64::Decode(const Cout::UnsignedBinary& encoded_string)
{
	Cout::UnsignedBinary res;
	int i = 0, j = 0, in_ = 0;
	auto length = encoded_string.size();
	char char_array_4[4], char_array_3[3];

	while (length-- && (encoded_string[in_] != '=') && check(encoded_string[in_]))
	{
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i < 4; i++)
				char_array_4[i] = static_cast<char>(base64_chars.find(char_array_4[i]));

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
			{
				res.push_back(char_array_3[i]);
			}
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (j = 0; j < 4; j++)
			char_array_4[j] = static_cast<char>(base64_chars.find(char_array_4[j]));

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++)
		{
			res.push_back(char_array_3[j]);
		}
	}

	return res;
}
