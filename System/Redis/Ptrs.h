///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_REDIS_PTRS_H
#define SYSTEM_REDIS_PTRS_H
#include <memory>
namespace cpp_redis
{
	class client;
}
namespace System
{
	namespace Redis
	{
		class RedisConnection;
		typedef std::shared_ptr<cpp_redis::client> RedisClientPtr;
		typedef std::shared_ptr<RedisConnection> RedisConnectionPtr;
	}
}
#endif // !SYSTEM_REDIS_PTRS_H
