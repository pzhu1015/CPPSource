///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef THREADING_THREAD_H
#define THREADING_THREAD_H

#include "System/DllExport.h"
#include "System/Object.h"
#include "System/Threading/Runnable.h"
#include <thread>
#include <functional>
#include <atomic>

namespace System
{
	namespace Threading
	{
		
		class SYSTEM_API Thread
		{
		public:
			Thread() = default;
			explicit Thread(const Thread &thread) = delete;
			explicit Thread(const std::function<void()> &function);
			explicit Thread(const std::shared_ptr<Runnable> &runnable);
			virtual ~Thread();
			void Start();
			void Stop();
			void Interrupt();
			void Join();
			void Detach();
			std::thread::id GetID() const;
			bool IsInterrupted() const;
			virtual void Run();
		private:
			std::thread m_thread;
			std::function<void()> m_function;
			std::atomic<bool> m_isInterript = false;
			std::shared_ptr<Runnable> m_runnable = nullptr;
		};

		SYSTEM_API std::thread::id CurrentThreadId();
		SYSTEM_API std::string CurrentThreadStrId();
		SYSTEM_API void Sleep(const int seconds);
		SYSTEM_API void SleepMs(const int millisecond);
	}
}
#endif

