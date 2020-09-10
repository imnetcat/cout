#pragma once
#include <string>
#include <sstream>
#include <ctime>
namespace Authentication
{
	namespace Method
	{
		std::string Plain(const std::string& login, const std::string& pass);
		std::string Login(const std::string& credentials);
		std::string CramMD5(const std::string& encoded_challenge, const std::string& login, const std::string& pass);
		std::string DigestMD5(const std::string& encoded_challenge, const std::string& charset, const std::string& addr, const std::string& login, const std::string& pass);
	}
};