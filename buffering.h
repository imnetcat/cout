#pragma once
#include "core.h"
#include <string>
#include <iostream>
#include <queue>

template <typename T>
class Buffer
{
public:
	Buffer();
	// TODO
	//Buffer(size_t maxSize);
	//Buffer(size_t minSize, size_t maxSize);

	std::string toString() const
	{
		string result;
		auto it = data.begin();
		while(it != data.end())
		{
			result += UTILS::to_string((*it));
			it++;
		}
		return result;
	}

	Buffer* Push(T new_data)
	{
		data.push(new_data);
		return this;
	}

	T Pop()
	{
		T firstElement = data.front();
		data.pop();
		return firstElement;
	}

	Buffer* Clear()
	{
		data = T();
		return this;
	}

	size_t size() const
	{
		return data.size();
	}
private:
	std::queue<T> data;
};

template <typename T>
std::ostream& operator << (std::ostream & out, const Buffer<T>& buf)
{
	return out << buf.toString();
}

template <typename T>
std::istream& operator >> (std::istream & in, Buffer<T>& buf)
{
	T data;
	while (in >> data)
	{
		buf.Push(data);
	}
	return in;
}
