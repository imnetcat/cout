#pragma once
#include <vector>
#include <string>
#include "../../core/types/byte.h"
namespace Cout
{
	struct Binary : public std::vector<SignedByte>
	{
		Binary() {};
		Binary(const SignedByte* init, size_t size)
		{
			Assign(init, size);
		}
		Binary(const std::string& init)
		{
			Assign(init.data(), init.size());
		}
		void operator = (const std::string& init)
		{
			Assign(init.data(), init.size());
		}
		void operator += (const std::string& init)
		{
			Append(init.data(), init.size());
		}
		void Assign(const SignedByte* data, size_t size)
		{
			this->clear();
			Append(data, size);
		}
		void Append(const SignedByte* data, size_t size)
		{
			for (unsigned int i = 0; i < size; i++)
			{
				this->push_back(data[i]);
			}
		}
	};

	struct UnsignedBinary : public std::vector<UnsignedByte>
	{
		void Assign(const UnsignedByte* data, size_t size)
		{
			this->clear();
			for (unsigned int i = 0; i < size; i++)
			{
				this->push_back(data[i]);
			}
		}
	};
}