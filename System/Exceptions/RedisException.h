///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_EXCEPTIONS_REDISEXCEPTION_H
#define SYSTEM_EXCEPTIONS_REDISEXCEPTION_H
#include "System/Exceptions/Exception.h"
namespace System
{
	namespace Exceptions
	{
		class SYSTEM_API RedisException : public Exception
		{
		public:
			RedisException();
			RedisException(const std::string &msg);
			virtual ~RedisException();
		};
	}
}
#endif // !SYSTEM_EXCEPTIONS_REDISEXCEPTION_H