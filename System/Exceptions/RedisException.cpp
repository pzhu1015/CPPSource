///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Exceptions/RedisException.h"
namespace System
{
	namespace Exceptions
	{
		RedisException::RedisException()
			:
			Exception(ExceptionId::Redis)
		{
		}
		RedisException::RedisException(const std::string & msg)
			:
			Exception(msg, ExceptionId::Redis)
		{
		}
		RedisException::~RedisException()
		{
		}
	}
}