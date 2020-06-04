#pragma once
#ifndef _AUTH_H_
#define _AUTH_H_
#include "core.h"

#include <string>
#include <sstream>
#include <ctime>
using string = std::string;

class Auth
{
public:
	static string Plain(const string& login, const string& pass);
	static string Login(const string& credentials);
	static string CramMD5(const string& encoded_challenge, const string& login, const string& pass);
	static string DigestMD5(const string& encoded_challenge, const string& charset, const string& addr, const string& login, const string& pass);
};

#endif