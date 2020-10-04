///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Redis/RedisMgr.h"
#include "System/Redis/RedisClientPool.h"
#include "System/Exceptions/RedisException.h"
#include <assert.h>
using namespace System::Exceptions;

namespace System
{
	namespace Redis
	{

		bool RedisMgr::Start()
		{
			RedisClientPool::GetInstance().Start();
			return true;
		}

		bool RedisMgr::Stop()
		{
			return false;
		}

		bool RedisMgr::Set(const std::string & key, const std::string & value)
		{
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return false;
				auto future = client->set(key, value);
				client->sync_commit();
				return future.get().ok();
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		std::string RedisMgr::Get(const std::string & key)
		{
			std::string value;
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return value;
				auto future = client->get(key);
				client->sync_commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_string())
				{
					value = reply.as_string();
				}
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return std::move(value);
		}

		int RedisMgr::Delete(const std::string & key)
		{
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return false;
				auto future = client->del({ key });
				client->sync_commit();
				auto reply = future.get();
				if (reply.ok())
				{
					return reply.as_integer();
				}
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return -1;
		}

		bool RedisMgr::Exist(const std::string & key)
		{
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return false;
				auto future = client->exists({ key });
				client->sync_commit();
				auto reply = future.get();
				return (reply.ok() && reply.as_integer() == 1);
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisMgr::HSet(const std::string & key, const std::string & field, const std::string & value)
		{
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return false;
				auto future = client->hset(key, field, value);
				client->sync_commit();
				return future.get().ok();
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisMgr::HDel(const std::string & key, const std::vector<std::string>& fields)
		{
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return false;
				auto future = client->hdel(key, fields);
				client->sync_commit();
				return future.get().ok();
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisMgr::HExist(const std::string & key, const std::string & field)
		{
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return false;
				auto future = client->hexists(key, field);
				client->sync_commit();
				auto reply = future.get();
				return (reply.ok() && reply.as_integer() == 1);
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisMgr::HIncrement(const std::string & key, const std::string & field, int value)
		{
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return false;
				auto future = client->hincrby(key, field, value);
				client->sync_commit();
				return future.get().ok();
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisMgr::HIncrement(const std::string & key, const std::string & field, float value)
		{
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return false;
				auto future = client->hincrbyfloat(key, field, value);
				client->sync_commit();
				return future.get().ok();
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		int64_t RedisMgr::HLength(const std::string & key)
		{
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return false;
				auto future = client->hlen(key);
				client->sync_commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_integer())
				{
					return reply.as_integer();
				}
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return -1;
		}

		std::vector<std::string> RedisMgr::HKeys(const std::string & key)
		{
			std::vector<std::string> keys;
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return keys;
				auto future = client->hkeys(key);
				client->sync_commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_array())
				{
					auto arr = reply.as_array();
					for (auto &item : arr)
					{
						keys.push_back(item.as_string());
					}
				}
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return std::move(keys);
		}

		std::vector<std::string> RedisMgr::HValues(const std::string & key)
		{
			std::vector<std::string> values;
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return values;
				auto future = client->hvals(key);
				client->sync_commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_array())
				{
					auto arr = reply.as_array();
					for (auto &item : arr)
					{
						values.push_back(item.as_string());
					}
				}
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return std::move(values);
		}

		std::string RedisMgr::HGet(const std::string key, const std::string & field)
		{
			std::string value;
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return value;
				auto future = client->hget(key, field);
				client->sync_commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_string())
				{
					value = reply.as_string();
				}
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return std::move(value);
		}

		std::map<std::string, std::string> RedisMgr::HGetAll(const std::string & key)
		{
			std::map<std::string, std::string> values;
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return values;
				auto future = client->hgetall(key);
				client->sync_commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_array())
				{
					auto arr = reply.as_array();
					size_t count = arr.size();
					for (size_t i = 0; i < count; i++)
					{
						values.insert({arr.at(i).as_string(), arr.at(i+1).as_string()});
						i++;
					}
				}
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return std::move(values);
		}

		int64_t RedisMgr::BitCount(const std::string & key)
		{
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return false;
				auto future = client->bitcount(key);
				client->sync_commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_integer())
				{
					return reply.as_integer();
				}
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return -1;
		}

		int RedisMgr::SetBit(const std::string & key, int offset, int value)
		{
			try
			{
				assert(value == 0 || value == 1);
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return false;
				auto future = client->setbit_(key, offset, std::to_string(value));
				client->sync_commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_integer())
				{
					return (int)reply.as_integer();
				}
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		int RedisMgr::GetBit(const std::string & key, int offset)
		{
			int value = -1;
			try
			{
				RedisClientGuard guard;
				RedisClientPtr client = guard.GetClient();
				if (!client) return false;
				auto future = client->getbit(key, offset);
				client->sync_commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_integer())
				{
					value = (int)reply.as_integer();
				}
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return value;
		}
	}
}