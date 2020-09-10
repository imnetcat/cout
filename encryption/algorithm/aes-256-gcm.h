#pragma once
#include <string>
#include "interface.h"
#include "../../core/types/binary.h"
namespace Encryption
{
	namespace Algorithm
	{
		class AES256gcm : public IAlgorithm
		{
		public:
			AES256gcm();
			UnsignedBinary Encode(const UnsignedBinary& data_to_encode) override;
			UnsignedBinary Decode(const UnsignedBinary& encoded_string) override;

			AES256gcm& Tag(const UnsignedBinary&);
			AES256gcm& Aad(const UnsignedBinary&);
			AES256gcm& Iv(const UnsignedBinary&);
			AES256gcm& Key(const UnsignedBinary&);

		private:
			unsigned char* _tag;
			int _tag_length;
			unsigned char* _aad;
			int _aad_length;
			unsigned char* _iv;
			int _iv_length;
			unsigned char* _key;
		};
	}
}