///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_REDIS_REDISCONNECTION_H
#define SYSTEM_REDIS_REDISCONNECTION_H
#include "System/Base/DllExport.h"
#include "System/Redis/Ptrs.h"
#include "System/Threading/Ptrs.h"
#include <cpp_redis/core/client.hpp>
#include <string>
#define IS_DIGITAL_TYPE \
std::is_same<T, bool>::value || \
std::is_same<T, float>::value ||\
std::is_same<T, double>::value ||\
std::is_same<T, __int8>::value ||\
std::is_same<T, __int16>::value ||\
std::is_same<T, __int32>::value ||\
std::is_same<T, __int64>::value ||\
std::is_same<T, unsigned __int8>::value ||\
std::is_same<T, unsigned __int16>::value ||\
std::is_same<T, unsigned __int32>::value ||\
std::is_same<T, unsigned __int64>::value

using namespace System::Threading;
namespace System
{
	namespace Redis
	{
		
		class SYSTEM_API RedisConnection final
		{
		public:
			RedisConnection(const std::string &host, int port = 6379, const std::string &pwd = "", int database = 0, int timeout = 5000);

			~RedisConnection();

			bool Commit();

			bool Open();

			bool Close(bool wait_for_removal = false);

			bool Ping();

			bool Set(const std::string &key, const std::string &value);

			template <class T, class = typename std::enable_if<IS_DIGITAL_TYPE>::type>
			bool Set(const std::string &key, T value)
			{
				return Set(key, std::to_string(value));
			}

			template <class T, class = typename std::enable_if<IS_DIGITAL_TYPE>::type>
			bool Set(T key, T value)
			{
				return Set(std::to_string(key), std::to_string(value));
			}

			template <class T, class = typename std::enable_if<IS_DIGITAL_TYPE>::type>
			bool Set(T key, const std::string &value)
			{
				return Set(std::to_string(key), value);
			}

			std::string Get(const std::string &key);

			template <class T, class = typename std::enable_if<IS_DIGITAL_TYPE>::type>
			std::string Get(T key)
			{
				return Get(std::to_string(key));
			}

			/*return 1: key exist, 0: key not exist, -1: error*/
			int Delete(const std::string &key);

			bool Exist(const std::string &key);

			bool HSet(const std::string &key, const std::string &field, const std::string &value);

			bool HDel(const std::string &key, const std::string &field);

			bool HDel(const std::string &key, const std::vector<std::string> &fields);

			bool HExist(const std::string &key, const std::string &field);

			bool HIncrement(const std::string &key, const std::string &field, int value);

			bool HIncrement(const std::string &key, const std::string &field, float value);

			__int64 HLength(const std::string &key);

			std::vector<std::string> HKeys(const std::string &key);

			std::vector<std::string> HValues(const std::string &key);

			std::string HGet(const std::string key, const std::string &field);

			std::map<std::string, std::string> HGetAll(const std::string &key);

			__int64 BitCount(const std::string &key);

			/*return old value*/
			int SetBit(const std::string &key, int offset, int value);

			/*return 0,1*/
			int GetBit(const std::string &key, int offset);

			bool SAdd(const std::string& key, const std::vector<std::string>& members);

			bool SIsMember(const std::string& key, const std::string& member);

			__int64 SCard(const std::string& key);
		private:
			void ConnectCb(const std::string& host, std::size_t port, cpp_redis::client::connect_state status);
			std::string		m_host;
			int				m_port;
			std::string		m_password;
			int				m_database;
			int				m_timeout = 5000;
			int				m_max_reconnects = -1;
			int				m_reconnect_interval = 2000;
			RedisClientPtr	m_client;
			SemaphorePtr	m_sem;
		};
	}
}
#endif // !SYSTEM_REDIS_REDISCONNECTION_H
