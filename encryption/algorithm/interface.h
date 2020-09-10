#pragma once
#include <vector>
#include "../../core/types/binary.h"
namespace Encryption
{
	namespace Algorithm
	{
		class IAlgorithm
		{
		public:
			// decode and encode
			virtual UnsignedBinary Encode(const UnsignedBinary& data_to_encode) = 0;
			virtual UnsignedBinary Decode(const UnsignedBinary& encoded_string) = 0;
		};
	}
}