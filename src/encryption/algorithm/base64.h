#pragma once
#include <string>
#include "interface.h"
#include "../../core/types/binary.h"
namespace Cout
{
	namespace Encryption
	{
		namespace Algorithm
		{
			class Base64 : public IAlgorithm
			{
			private:
				// check for that is base64-char
				static inline bool check(unsigned char c);

			public:
				// decode and encode base64
				UnsignedBinary Encode(const UnsignedBinary& data_to_encode) override;
				UnsignedBinary Decode(const UnsignedBinary& encoded_string) override;

			private:
				static const std::string base64_chars;
			};
		}
	}
}