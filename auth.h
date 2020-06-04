#pragma once
#ifndef _AUTH_H_
#define _AUTH_H_
#include "core.h"

#include <string>
#include <ctime>
using string = std::string;

class Auth
{
public:
	static string Plain(string login, string pass);
	static string Login(string credentials);
	static string CramMD5(string encoded_challenge, string login, string pass);
	static string DigestMD5(string encoded_challenge, string charset, string addr, string login, string pass);
};

#endif