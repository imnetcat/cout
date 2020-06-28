#pragma once
#include "../config.h"
#ifdef INDEBUG
#include <iostream>
#include <vector>
namespace Core
{
	namespace Testing
	{
		template<typename T>
		std::ostream& operator << (std::ostream& out, const std::vector<T>& vec)
		{
			bool isFirst = true;
			out << "{ ";
			for (const T& elem : vec)
			{
				if (!isFirst)
					out << ", ";

				out << elem;
			}
			return out << " }";
		}
	}
}
#endif