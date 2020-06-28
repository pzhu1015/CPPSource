///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "Redis/CRedis.h"
#ifdef _WIN32
#include <winsock2.h>
#endif

namespace System
{
	namespace Redis
	{
		CRedis::CRedis()
			:
			m_redis(nullptr)
		{
		}
		CRedis::CRedis(const char * ip, const int port, const char * pwd, const int dbname)
			:
			m_redis(nullptr)
		{
			SetConfig(ip, port, pwd, dbname);
		}
		CRedis::~CRedis()
		{
			Close();
		}
		int CRedis::Open()
		{
			int ret = -1;
			if (m_redis)
			{
				return ret;
			}
			struct timeval timeout = { 1, 500000 };
			m_redis = redisConnectWithTimeout(m_ip.c_str(), m_port, timeout);
			if (m_redis == nullptr || m_redis->err)
			{
				if (m_redis)
				{
					printf("connection redis %s: %d error: %s\n", m_ip.c_str(), m_port, m_redis->errstr);
					Close();
				}
				else
				{
					printf("connection redis %s: %d error:can't allocate redis context\n", m_ip.c_str(), m_port);
				}
				return ret;
			}
			else
			{
				if (AuthRedis(m_pwd.c_str()))
				{
					Close();
					printf("connection redis %s: %d error: auth error\n", m_ip.c_str(), m_port);
				}
				else
				{
					printf("connection redis %s: %d success \n", m_ip.c_str(), m_port);
					char cmd[64] = {0};
					snprintf(cmd, sizeof(cmd), "select %d", m_db);
					printf("select db: %d\n", m_db);
					SetRedis(cmd);
					ret = 0;
				}
			}
			return ret;
		}
		int CRedis::Close()
		{
			if (m_redis)
			{
				redisFree(m_redis);
				m_redis = nullptr;
			}
			return 0;
		}
		int CRedis::SetRedis(const char * cmd)
		{
			if (cmd == nullptr)
			{
				return -1;
			}

			if (m_redis == nullptr)
			{
				if (Open())
				{
					return -1;
				}
			}

			redisReply *reply = (redisReply *)redisCommand(m_redis, cmd);
			if (reply == nullptr)
			{
				Close();
				Open();
				reply = (redisReply *)redisCommand(m_redis, cmd);
				if (reply == nullptr)
				{
					printf("exec [%s] error\n", cmd);
					return -1;
				}
			}

			//printf("##########################exec [%s]\n", szcmd);
			int ret = 0;
			switch (reply->type)
			{
			case REDIS_REPLY_STATUS:
				if (strcmp(reply->str, "OK") == 0)
					ret = 0;
				else
					ret = -1;
				printf("[%s] status [%s]\n", cmd, reply->str);
				break;
			case REDIS_REPLY_ERROR:
				ret = -1;
				printf("[%s] error [%s]\n", cmd, reply->str);
				break;
			case REDIS_REPLY_STRING:
				ret = 0;
				printf("[%s] set result type:string\n", cmd);
				break;
			case REDIS_REPLY_INTEGER:
				ret = 0;
				printf("[%s] set result type:integer:%d\n", cmd, (int)reply->integer);
				break;
			case REDIS_REPLY_ARRAY:
				ret = 0;
				printf("[%s] set result type:array\n", cmd);
				break;
			case REDIS_REPLY_NIL:
				ret = 0;
				printf("[%s] set result type:null\n", cmd);
				break;
			default:
				ret = -1;
				printf("[%s] set error\n", cmd);
				break;
			}

			FreeRedisReply(reply);

			return ret;
		}
		int CRedis::SetRedis(const std::vector<std::string>& cmd)
		{
			std::vector<int> vstatus;
			if (SetRedisPipeLine(cmd, vstatus))
			{
				Close();
				Open();
				if (SetRedisPipeLine(cmd, vstatus))
				{
					printf("exec set redises error\n");
					return -1;
				}
			}
			return 0;
		}
		int CRedis::GetRedis(const char * cmd, RedisResult & rslts)
		{
			if (cmd == nullptr)
			{
				return -1;
			}

			if (m_redis == NULL)
			{
				if (Open())
				{
					return -1;
				}
			}

			rslts.type = RedisResultType::E_REDIS_REPLY_INVALID;
			rslts.integer = 0;

			redisReply *reply = (redisReply *)redisCommand(m_redis, cmd);
			if (reply == NULL)
			{
				Close();
				Open();
				reply = (redisReply *)redisCommand(m_redis, cmd);
				if (reply == NULL)
				{
					printf("exec [%s] error\n", cmd);
					return -1;
				}
			}

			//printf("##########################exec [%s]\n", szcmd);
			int ret = 0;
			switch (reply->type)
			{
			case REDIS_REPLY_STATUS:
				ret = -1;
				printf("[%s] status [%s]\n", cmd, reply->str);
				break;
			case REDIS_REPLY_ERROR:
				ret = -1;
				printf("[%s] error [%s]\n", cmd, reply->str);
				break;
			case REDIS_REPLY_STRING:
				ret = 0;
				rslts.type = RedisResultType::E_REDIS_REPLY_STRING;
				rslts.str = reply->str;
				printf("[%s] get string\n", cmd);
				break;
			case REDIS_REPLY_INTEGER:
				ret = 0;
				rslts.type = RedisResultType::E_REDIS_REPLY_INTEGER;
				rslts.integer = (int)reply->integer;
				printf("[%s] get integer\n", cmd);
				break;
			case REDIS_REPLY_ARRAY:
				ret = 0;
				rslts.type = RedisResultType::E_REDIS_REPLY_ARRAY;
				for (int i = 0; i < reply->elements; i++)
				{
					rslts.datas.push_back(reply->element[i]->str);
				}
				printf("[%s] get array\n", cmd);
				break;
			case REDIS_REPLY_NIL:
				ret = 0;
				rslts.type = RedisResultType::E_REDIS_REPLY_NULL;
				printf("[%s] get null\n", cmd);
				break;
			default:
				ret = -1;
				rslts.type = RedisResultType::E_REDIS_REPLY_INVALID;
				printf("[%s] get error\n", cmd);
				break;
			}

			FreeRedisReply(reply);

			return ret;
		}
		int CRedis::GetRedis(const std::vector<std::string>& cmds, std::vector<RedisResult>& rslts)
		{
			if (GetRedisPipiLine(cmds, rslts))
			{
				Close();
				Open();
				if (GetRedisPipiLine(cmds, rslts))
				{
					printf("exec get redises error\n");
					return -1;
				}
			}
			return 0;
		}
		int CRedis::SetConfig(const char * ip, const int port, const char * pwd, const int dbname)
		{
			m_ip = ip;
			m_pwd = pwd;
			m_port = port;
			m_db = dbname;
			return 0;
		}
		int CRedis::FreeRedisReply(redisReply * reply)
		{
			if (reply)
			{
				freeReplyObject(reply);
				reply = nullptr;
			}
			return 0;
		}
		int CRedis::AuthRedis(const char * pwd)
		{
			int ret = 0;
			redisReply *reply = (redisReply *)redisCommand(m_redis, "AUTH %s", pwd);
			if (reply == nullptr)
			{
				printf("AUTH error\n");
				return -1;
			}

			if (reply->type != REDIS_REPLY_STATUS)
			{
				printf("AUTH error: type [%d]\n", reply->type);
				ret = -1;
			}
			else
			{
				if (strcmp(reply->str, "OK") == 0)
				{
					printf("AUTH success [%s]\n", reply->str);
				}
				else
				{
					printf("AUTH error: [%s]\n", reply->str);
					ret = -1;
				}
			}
			return ret;
		}
		int CRedis::SetRedisPipeLine(const std::vector<std::string>& cmds, std::vector<int>& status)
		{
			if (cmds.empty())
				return 0;

			if (m_redis == nullptr)
			{
				if (Open())
					return -1;
			}

			for (int i = 0; i < cmds.size(); i++)
			{
				redisAppendCommand(m_redis, cmds[i].c_str());
			}

			for (int i = 0; i < cmds.size(); i++)
			{
				int ret = -1;
				redisReply *reply = NULL;
				if (redisGetReply(m_redis, (void **)&reply) == REDIS_OK && reply != NULL)
					if (ret == REDIS_OK && reply != NULL)
					{
						switch (reply->type)
						{
						case REDIS_REPLY_STATUS:
							if (strcmp(reply->str, "OK") == 0)
								ret = 0;
							else
								ret = -1;
							printf("[%s] status [%s]\n", cmds[i].c_str(), reply->str);
							break;
						case REDIS_REPLY_ERROR:
							ret = -1;
							printf("[%s] error [%s]\n", cmds[i].c_str(), reply->str);
							break;
						case REDIS_REPLY_STRING:
							ret = 0;
							printf("[%s] set result type:string\n", cmds[i].c_str());
							break;
						case REDIS_REPLY_INTEGER:
							ret = 0;
							printf("[%s] set result type:integer:%d\n", cmds[i].c_str(), (int)reply->integer);
							break;
						case REDIS_REPLY_ARRAY:
							ret = 0;
							printf("[%s] set result type:array\n", cmds[i].c_str());
							break;
						case REDIS_REPLY_NIL:
							ret = 0;
							printf("[%s] set result type:null\n", cmds[i].c_str());
							break;
						default:
							ret = -1;
							printf("[%s] set error\n", cmds[i].c_str());
							break;
						}
					}
					else
					{
						freeReplyObject(reply);
						reply = NULL;
						return -1;
					}

				freeReplyObject(reply);
				reply = NULL;

				status.push_back(ret);
			}

			return 0;
		}
		int CRedis::GetRedisPipiLine(const std::vector<std::string>& cmds, std::vector<RedisResult>& rslts)
		{
			if (cmds.empty())
				return -1;
			if (m_redis == NULL)
			{
				if (Open())
					return -1;
			}

			for (int i = 0; i < cmds.size(); i++)
			{
				redisAppendCommand(m_redis, cmds[i].c_str());
			}

			for (int i = 0; i < cmds.size(); i++)
			{
				int ret = -1;
				RedisResult result;
				result.type = RedisResultType::E_REDIS_REPLY_INVALID;
				result.integer = 0;

				redisReply *reply = NULL;
				if (redisGetReply(m_redis, (void **)&reply) == REDIS_OK && reply != NULL)
				{
					switch (reply->type)
					{
					case REDIS_REPLY_STATUS:
						if (strcmp(reply->str, "OK") == 0)
							ret = 0;
						else
							ret = -1;
						printf("[%s] status [%s]\n", cmds[i].c_str(), reply->str);
						break;
					case REDIS_REPLY_ERROR:
						ret = -1;
						printf("[%s] error [%s]\n", cmds[i].c_str(), reply->str);
						break;
					case REDIS_REPLY_STRING:
						ret = 0;
						result.type = RedisResultType::E_REDIS_REPLY_STRING;
						result.str = reply->str;
						printf("[%s] get string\n", cmds[i].c_str());
						break;
					case REDIS_REPLY_INTEGER:
						ret = 0;
						result.type = RedisResultType::E_REDIS_REPLY_INTEGER;
						result.integer = (int)reply->integer;
						printf("[%s] get integer\n", cmds[i].c_str());
						break;
					case REDIS_REPLY_ARRAY:
						ret = 0;
						result.type = RedisResultType::E_REDIS_REPLY_ARRAY;
						for (int i = 0; i < reply->elements; i++)
						{
							result.datas.push_back(reply->element[i]->str);
						}
						printf("[%s] get array\n", cmds[i].c_str());
						break;
					case REDIS_REPLY_NIL:
						ret = 0;
						result.type = RedisResultType::E_REDIS_REPLY_NULL;
						printf("[%s] get null\n", cmds[i].c_str());
						break;
					default:
						ret = -1;
						result.type = RedisResultType::E_REDIS_REPLY_INVALID;
						printf("[%s] get error\n", cmds[i].c_str());
						break;
					}
				}
				else
				{
					freeReplyObject(reply);
					reply = NULL;
					return -1;
				}
				freeReplyObject(reply);
				reply = NULL;

				rslts.push_back(result);
			}

			return 0;
		}
	}
}