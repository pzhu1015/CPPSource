///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_REDIS_REDISCLIENTPOOL_H
#define SYSTEM_REDIS_REDISCLIENTPOOL_H
#include "System/Base/DllExport.h"
#include "System/Threading/Ptrs.h"
#include <cpp_redis/core/client.hpp>
#include <unordered_set>
#include <deque>
#define MIN_REDIS_CLIENTS 10
#define MAX_REDIS_CLIENTS 255
using namespace System::Threading;
namespace System
{
	namespace Redis
	{
		typedef std::shared_ptr<cpp_redis::client> RedisClientPtr;
		class SYSTEM_API RedisClientPool
		{
		public:
			static RedisClientPool & GetInstance()
			{
				static RedisClientPool instance;
				return instance;
			}
			
			bool Start(int min_clients = MIN_REDIS_CLIENTS, int max_clients = MAX_REDIS_CLIENTS);

			bool Stop();

			RedisClientPtr Allocate(int timeout = 60);

			void Release(const RedisClientPtr &client);

		private:
			RedisClientPtr CreateClient();
		private:
			bool								m_start = true;
			int									m_max_clients = 0;
			int									m_min_clients = 0;
			std::string							m_host;
			int									m_port = 6379;
			int									m_database = 0;
			std::string							m_password;
			std::mutex							m_mutex;
			std::condition_variable				m_cond;
			ThreadPtr							m_monitor_thrd;
			std::deque<RedisClientPtr>			m_waits;
			std::unordered_set<RedisClientPtr>	m_idles;
		};

		class RedisClientGuard
		{
		public:
			RedisClientGuard()
			{
				m_client = RedisClientPool::GetInstance().Allocate();
			}
			~RedisClientGuard()
			{
				if (m_client)
				{
					RedisClientPool::GetInstance().Release(m_client);
				}
				m_client = nullptr;
			}
			const RedisClientPtr &GetClient() const
			{
				return m_client;
			}
		private:
			RedisClientPtr m_client;
		};
	}
}
#endif // !SYSTEM_REDIS_REDISCLIENTPOOL_H
