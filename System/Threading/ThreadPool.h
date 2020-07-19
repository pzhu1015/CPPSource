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
#include "System/Threading/Ptrs.h"
#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <vector>

namespace System
{
	namespace Threading
	{
		class Thread;
		typedef std::function<void()> Task;
		class SYSTEM_API ThreadPool
		{
		public:
			ThreadPool(size_t task_size = 256, size_t thread_size = 10);
			ThreadPool(const ThreadPool& other) = delete;
			ThreadPool& operator=(const ThreadPool& other) = delete;
			virtual ~ThreadPool();
			void Start();
			void Stop();
			void AddTask(const Task &task);
			ThreadPool::Task GetTask();
			bool IsStarted() const;
			void Run();
		private:
			std::mutex m_mutex;
			std::condition_variable m_empty_cond;
			std::condition_variable m_full_cond;
			size_t m_task_size;
			std::queue<Task> m_tasks;
			const size_t m_thread_size;
			std::vector<ThreadPtr> m_threads;
			std::atomic<bool> m_is_started;
		};
	}
}
#endif

