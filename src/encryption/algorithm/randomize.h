#pragma once
#include <string>
#include <sstream>
#include "md5.h"
namespace Cout
{
	namespace Encryption
	{
		namespace Algorithm
		{
			static std::string random(std::string seed);
		}

		std::string Algorithm::random(std::string seed)
		{
			MD5 md5;
			std::stringstream sseed(seed);

			md5.update(sseed);
			md5.finalize();

			return md5.hex_digest();
		}
	}
}