#pragma once
#ifndef _SECURITY_H_
#define _SECURITY_H_
#include "ssl.h"
namespace Security
{
	namespace Encryption
	{
		enum Type
		{
			TLS,
			SSL
		};
	}
}
#endif