///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_THREADING_SEMAPHORE_H
#define SYSTEM_THREADING_SEMAPHORE_H
#include "System/Base/DllExport.h"
#include <mutex>
#include <condition_variable>
namespace System
{
	namespace Threading
	{
		class SYSTEM_API Semaphore final
		{
		public:
			Semaphore(int value = 0);
			~Semaphore();
			
			void wait();

			void signal();
		private:
			int m_count = 0;
			int m_wakeups = 0;
			std::mutex m_mutex;
			std::condition_variable m_condition;
		};
	}
}
#endif // !SYSTEM_THREADING_SEMAPHORE_H
