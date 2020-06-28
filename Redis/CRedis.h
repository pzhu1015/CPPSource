///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef REDIS_CREDIS_H
#define REDIS_CREDIS_H
#include "Redis/DllExport.h"
#include <hiredis/hiredis.h>
#include <vector>

namespace System
{
	namespace Redis
	{
		enum class RedisResultType
		{
			E_REDIS_REPLY_INVALID = -1,
			E_REDIS_REPLY_STRING,
			E_REDIS_REPLY_INTEGER,
			E_REDIS_REPLY_ARRAY,
			E_REDIS_REPLY_NULL
		};

		struct RedisResult
		{
			RedisResultType type;
			int integer;
			std::string str;
			std::vector<std::string> datas;
		};

		class REDIS_API CRedis
		{
		public:
			CRedis();
			CRedis(const char* ip, const int port, const char* pwd, const int dbname);
			~CRedis();
			int Open();
			int Close();
			int SetRedis(const char* cmd);
			int SetRedis(const std::vector<std::string> &cmd);
			int GetRedis(const char* cmd, RedisResult &rslts);
			int GetRedis(const std::vector<std::string> &cmd, std::vector<RedisResult> &rslts);
			int SetConfig(const char* ip, const int port, const char* pwd, const int dbname);
		private:
			int FreeRedisReply(redisReply* reply);
			int AuthRedis(const char* pwd);
			int SetRedisPipeLine(const std::vector<std::string> &cmds, std::vector<int> &status);
			int GetRedisPipiLine(const std::vector<std::string> &cmds, std::vector<RedisResult> &rslts);
		private:
			redisContext* m_redis;
			std::string m_ip;
			std::string m_pwd;
			int m_port;
			int m_db;
			

		};
	}
}


#endif // !REDIS_CREDIS_H
