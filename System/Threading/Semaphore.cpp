///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Threading/Semaphore.h"
namespace System
{
	namespace Threading
	{
		Semaphore::Semaphore(int value)
		{
			m_count = 0;
		}

		Semaphore::~Semaphore()
		{
		}

		void Semaphore::wait()
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			if (m_count-- < 0)
			{
				m_condition.wait(lock, [&]()->bool {return m_wakeups > 0; });
				m_wakeups--;
			}
		}


		void Semaphore::signal()
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_count++ <= 0)
			{
				m_wakeups++;
				m_condition.notify_one();
			}
		}
	}
}