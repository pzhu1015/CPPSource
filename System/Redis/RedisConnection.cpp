///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Redis/RedisConnection.h"
#include "System/Threading/Semaphore.h"
#include "System/Exceptions/RedisException.h"
#include "System/Exceptions/OverflowException.h"
#include "System/Threading/Timer.h"
#include <functional>
#include <cpp_redis/core/client.hpp>
#include <cpp_redis/misc/error.hpp>
using namespace System::Exceptions;
using namespace System::Threading;
namespace System
{
	namespace Redis
	{
		RedisConnection::RedisConnection(const std::string & host, int port, const std::string & pwd, int database, int timeout)
		{
			m_host = host;
			m_port = port;
			m_password = pwd;
			m_database = database;
			m_timeout = timeout;
			m_sem = std::make_shared<Semaphore>();
		}

		RedisConnection::~RedisConnection()
		{
		}

		bool RedisConnection::Commit()
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return false;
				}
				m_client->commit();
				return true;
			}
			catch (cpp_redis::redis_error &ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisConnection::Open()
		{
			try
			{
				using namespace std::placeholders;
				cpp_redis::client::connect_callback_t callback = std::bind(&RedisConnection::ConnectCb, this, _1, _2, _3);
				m_client = std::make_shared<cpp_redis::client>();
				m_client->connect(m_host, m_port, callback, m_timeout, m_max_reconnects, m_reconnect_interval);
				m_sem->wait(m_timeout);
				return m_client->is_connected();
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisConnection::Close(bool wait_for_removal)
		{
			try
			{
				if (m_client->is_connected())
				{
					m_client->disconnect(wait_for_removal);
				}
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisConnection::Ping()
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return false;
				}
				auto future = m_client->ping();
				m_client->commit();
				return future.get().ok();
			}
			catch (cpp_redis::redis_error &ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		void RedisConnection::ConnectCb(const std::string & host, std::size_t port, cpp_redis::client::connect_state status)
		{
			//!  * dropped: connection has dropped
			//!  * start: attempt of connection has started
			//!  * sleeping: sleep between two attempts
			//!  * ok: connected
			//!  * failed: failed to connect
			//!  * lookup failed: failed to retrieve master sentinel
			//!  * stopped: stop to try to reconnect
			if (status == cpp_redis::client::connect_state::ok)
			{
				std::cout << "ok" << std::endl;
				auto future = m_client->auth(m_password);
				m_client->sync_commit();
				if (future.get().ok())
				{
					future = m_client->select(m_database);
					m_client->sync_commit();
					if (future.get().ok())
					{
						m_sem->signal();
					}
				}
			}
			else if (status == cpp_redis::client::connect_state::dropped)
			{
				std::cout << "dropped" << std::endl;
			}
			else if (status == cpp_redis::client::connect_state::failed)
			{
				std::cout << "failed" << std::endl;
			}
			else if (status == cpp_redis::client::connect_state::lookup_failed)
			{
				std::cout << "lookup_failed" << std::endl;
			}
			else if (status == cpp_redis::client::connect_state::sleeping)
			{
				std::cout << "sleeping" << std::endl;
			}
			else if (status == cpp_redis::client::connect_state::start)
			{
				std::cout << "start" << std::endl;
			}
			else if (status == cpp_redis::client::connect_state::stopped)
			{
				std::cout << "stopped" << std::endl;
			}
		}

		bool RedisConnection::Set(const std::string & key, const std::string & value)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return false;
				}
				auto future = m_client->set(key, value);
				m_client->commit();
				return future.get().ok();
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		std::string RedisConnection::Get(const std::string & key)
		{
			std::string value;
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return std::move(value);
				}
				auto future = m_client->get(key);
				m_client->commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_string())
				{
					value = reply.as_string();
				}
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return std::move(value);
		}

		int RedisConnection::Delete(const std::string & key)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return -1;
				}
				auto future = m_client->del({ key });
				m_client->commit();
				auto reply = future.get();
				if (reply.ok())
				{
					__int64 result = reply.as_integer();
					if (result > INT_MAX || result < INT_MIN)
					{
						throw OverflowException("result is " + result);
					}
					return (int)result;
				}
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return -1;
		}

		bool RedisConnection::Exist(const std::string & key)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return false;
				}
				auto future = m_client->exists({ key });
				m_client->commit();
				auto reply = future.get();
				return (reply.ok() && reply.as_integer() == 1);
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisConnection::HSet(const std::string & key, const std::string & field, const std::string & value)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return false;
				}
				auto future = m_client->hset(key, field, value);
				m_client->commit();
				return future.get().ok();
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisConnection::HDel(const std::string & key, const std::string & field)
		{
			std::vector<std::string> fields = { field };
			return HDel(key, fields);
		}

		bool RedisConnection::HDel(const std::string & key, const std::vector<std::string>& fields)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return false;
				}
				auto future = m_client->hdel(key, fields);
				m_client->commit();
				return future.get().ok();
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisConnection::HExist(const std::string & key, const std::string & field)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return false;
				}
				auto future = m_client->hexists(key, field);
				m_client->commit();
				auto reply = future.get();
				return (reply.ok() && reply.as_integer() == 1);
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisConnection::HIncrement(const std::string & key, const std::string & field, int value)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return false;
				}
				auto future = m_client->hincrby(key, field, value);
				m_client->commit();
				return future.get().ok();
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisConnection::HIncrement(const std::string & key, const std::string & field, float value)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return false;
				}
				auto future = m_client->hincrbyfloat(key, field, value);
				m_client->commit();
				return future.get().ok();
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		__int64 RedisConnection::HLength(const std::string & key)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return -1;
				}
				auto future = m_client->hlen(key);
				m_client->commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_integer())
				{
					return reply.as_integer();
				}
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return -1;
		}

		std::vector<std::string> RedisConnection::HKeys(const std::string & key)
		{
			std::vector<std::string> keys;
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return std::move(keys);
				}
				auto future = m_client->hkeys(key);
				m_client->commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_array())
				{
					auto arr = reply.as_array();
					for (auto &item : arr)
					{
						keys.push_back(std::move(item.as_string()));
					}
				}
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return std::move(keys);
		}

		std::vector<std::string> RedisConnection::HValues(const std::string & key)
		{
			std::vector<std::string> values;
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return std::move(values);
				}
				auto future = m_client->hvals(key);
				m_client->commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_array())
				{
					auto arr = reply.as_array();
					for (auto &item : arr)
					{
						values.push_back(std::move(item.as_string()));
					}
				}
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return std::move(values);
		}

		std::string RedisConnection::HGet(const std::string key, const std::string & field)
		{
			std::string value;
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return std::move(value);
				}
				auto future = m_client->hget(key, field);
				m_client->commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_string())
				{
					value = reply.as_string();
				}
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return std::move(value);
		}

		std::map<std::string, std::string> RedisConnection::HGetAll(const std::string & key)
		{
			std::map<std::string, std::string> values;
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return std::move(values);
				}
				auto future = m_client->hgetall(key);
				m_client->commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_array())
				{
					auto arr = reply.as_array();
					size_t count = arr.size();
					for (size_t i = 0; i < count; i++)
					{
						values.insert({ arr.at(i).as_string(), arr.at(i + 1).as_string() });
						i++;
					}
				}
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return std::move(values);
		}

		__int64 RedisConnection::BitCount(const std::string & key)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return 0;
				}
				auto future = m_client->bitcount(key);
				m_client->commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_integer())
				{
					return reply.as_integer();
				}
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return 0;
		}

		int RedisConnection::SetBit(const std::string & key, int offset, int value)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return -1;
				}
				auto future = m_client->setbit_(key, offset, std::to_string(value));
				m_client->commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_integer())
				{
					return (int)reply.as_integer();
				}
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return -1;
		}

		int RedisConnection::GetBit(const std::string & key, int offset)
		{
			int value = -1;
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return -1;
				}
				auto future = m_client->getbit(key, offset);
				m_client->commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_integer())
				{
					value = (int)reply.as_integer();
				}
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return value;
		}

		bool RedisConnection::SAdd(const std::string & key, const std::vector<std::string>& members)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return false;
				}
				auto future = m_client->sadd(key, members);
				m_client->commit();
				return future.get().ok();
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		bool RedisConnection::SIsMember(const std::string & key, const std::string & member)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return false;
				}
				auto future = m_client->sismember(key, member);
				m_client->commit();
				auto reply = future.get();
				return (reply.ok() && reply.as_integer() == 1);
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return false;
		}

		__int64 RedisConnection::SCard(const std::string & key)
		{
			try
			{
				if (!m_client || !m_client->is_connected())
				{
					return -1;
				}
				auto future = m_client->scard(key);
				m_client->commit();
				auto reply = future.get();
				if (reply.ok() && reply.is_integer())
				{
					return reply.as_integer();
				}
			}
			catch (cpp_redis::redis_error& ex)
			{
				throw RedisException(ex.what());
			}
			return -1;
		}
	}
}