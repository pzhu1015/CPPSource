///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_THREADING_THREADPOOL_H
#define SYSTEM_THREADING_THREADPOOL_H

#include "System/DllExport.h"
#include "System/Threading/Thread.h"
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>

namespace System
{
	namespace Threading
	{
		class SYSTEM_API ThreadPool
		{
		public:
			typedef std::function<void()> Task;
			ThreadPool(size_t task_size = 256, size_t thread_size = 10);
			virtual ~ThreadPool();
			void Start();
			void Stop();
			void AddTask(const ThreadPool::Task &task);
			ThreadPool::Task GetTask();
			bool IsStarted() const;
			void Run();
		private:
			std::mutex m_mutex;
			std::condition_variable m_empty_cond;
			std::condition_variable m_full_cond;
			size_t m_task_size;
			std::queue<ThreadPool::Task> m_tasks;
			const size_t m_thread_size;
			std::vector<std::unique_ptr<Thread>> m_threads;
			std::atomic<bool> m_is_started;
		};
	}
}
#endif

