///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Threading/ThreadPool.h"
#include "System/Threading/Thread.h"

namespace System
{
	namespace Threading
	{
		ThreadPool::ThreadPool(size_t task_size, size_t thread_size)
			:
			m_task_size(task_size),
			m_thread_size(thread_size),
			m_is_started(false)
		{
		}

		ThreadPool::~ThreadPool()
		{
			if (m_is_started)
			{
				Stop();
			}
		}

		void ThreadPool::Start()
		{
			m_is_started = true;
			for (size_t i = 0; i < m_thread_size; i++)
			{
				m_threads.push_back(std::unique_ptr<Thread>(
					new Thread(
						std::bind(&ThreadPool::Run, this))));
			}

			for (size_t i = 0; i < m_thread_size; i++)
			{
				m_threads[i]->Start();
			}
		}

		void ThreadPool::Stop()
		{
			if (m_is_started == false)
			{
				return;
			}
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				m_is_started = false;
				while (!m_tasks.empty())
				{
					m_tasks.pop();
				}
			}
			m_full_cond.notify_all();
			m_empty_cond.notify_all();
			for (size_t i = 0; i < m_thread_size; i++)
			{
				m_threads[i]->Join();
			}
			m_threads.clear();
		}

		void ThreadPool::AddTask(const Task &task)
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			while (m_tasks.size() >= m_task_size)
			{
				m_empty_cond.wait(lock);
			}
			m_tasks.push(std::move(task));
			m_full_cond.notify_one();
		}

		Task ThreadPool::GetTask()
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			while (m_tasks.empty())
			{
				m_full_cond.wait(lock);
			}
			Task task = m_tasks.front();
			m_tasks.pop();
			m_empty_cond.notify_one();
			return task;
		}

		bool ThreadPool::IsStarted() const
		{
			return m_is_started;
		}

		void ThreadPool::Run()
		{
			while (m_is_started)
			{
				Task task = std::move(GetTask());
				if (task != nullptr)
				{
					task();
				}
			}
		}
	}

}