#pragma once
#ifndef _AUTH_H_
#define _AUTH_H_
#include "core.h"
#include <string>
#include <sstream>
#include <ctime>
#include "core.h"
namespace Auth
{
	using string = std::string;
	string Plain(const string& login, const string& pass);
	string Login(const string& credentials);
	string CramMD5(const string& encoded_challenge, const string& login, const string& pass);
	string DigestMD5(const string& encoded_challenge, const string& charset, const string& addr, const string& login, const string& pass);
};
#endif