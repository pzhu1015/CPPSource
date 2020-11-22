///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Redis/RedisClientPool.h"
#include "System/Applications/Application.h"
#include "System/Configurations/Configuration.h"
#include "System/Exceptions/RedisException.h"
#include "System/Exceptions/InvalidOperationException.h"
#include "System/Threading/Thread.h"
using namespace System::Exceptions;
namespace System
{
	namespace Redis
	{
		bool RedisClientPool::Start(int min_clients, int max_clients)
		{
			m_start = true;
			auto app_config = Application::GetInstance().GetConfiguration();
			m_min_clients = app_config->GetValue("redis", "min_clients", min_clients);
			m_max_clients = app_config->GetValue("redis", "max_clients", max_clients);
			if (m_min_clients <= 0 || m_max_clients <= 0 || m_min_clients > m_max_clients)
			{
				return false;
			}
			m_host = app_config->GetValue("redis", "host", "127.0.0.1");
			m_port = app_config->GetValue("redis", "port", 6379);
			m_database = app_config->GetValue("redis", "database", 0);
			m_password = app_config->GetValue("redis", "password", "12345");
			for (int i = 0; i < min_clients; i++)
			{
				auto client = CreateClient();
				if (client)
				{
					m_idles.push_back(client);
				}
				else
				{
					return false;
				}
			}
			return true;
		}

		bool RedisClientPool::Stop()
		{
			m_start = false;
			return true;
		}

		RedisClientPtr RedisClientPool::Allocate(int timeout)
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			while (m_idles.empty() && m_idles.size() + m_in_used.size() >= m_max_clients)
			{
				auto status = m_cond.wait_for(lock, std::chrono::microseconds(timeout));
				if (status == std::cv_status::timeout)
				{
					return nullptr;
				}
				continue;
			}
			RedisClientPtr client = nullptr;
			if (m_idles.empty())
			{
				client = CreateClient();
				if (client == nullptr) return nullptr;
			}
			else
			{
				client = m_idles.front();
				m_idles.pop_front();
			}
			m_in_used.insert(client);
			return client;
		}

		void RedisClientPool::Release(const RedisClientPtr & client)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			auto itr = m_in_used.find(client);
			if (itr == m_in_used.end())
			{
				throw InvalidOperationException("ReleaseClient faild");
			}
			m_in_used.erase(itr);
			m_idles.push_back(client);
		}

		RedisClientPtr RedisClientPool::CreateClient()
		{
			try
			{
				if (m_idles.size() + m_in_used.size() < m_max_clients)
				{
					RedisClientPtr client = std::make_shared<cpp_redis::client>();
					client->connect(m_host, m_port);
					if (client->is_connected())
					{
						if (!m_password.empty())
						{
							auto future = client->auth(m_password);
							client->sync_commit();
							if (future.get().ok())
							{
								future = client->select(m_database);
								client->sync_commit();
								if (future.get().ok())
								{
									return client;
								}
							}
						}
						else
						{
							return client;
						}
					}
				}
			}
			catch (std::exception &ex)
			{
				throw RedisException(ex.what());
			}
			return nullptr;
		}
	}
}
