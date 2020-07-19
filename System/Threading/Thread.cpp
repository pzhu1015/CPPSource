///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Threading/Thread.h"
#include "System/Threading/Runnable.h"
#include <sstream>

namespace System
{
	namespace Threading
	{
		Thread::Thread(const std::function<void()> &callback)
			:
			m_isInterript(false),
			m_function(callback),
			m_runnable(nullptr)
		{
		}

		Thread::Thread(RunnablePtr runnable)
			:
			m_isInterript(false),
			m_function(nullptr),
			m_runnable(runnable)
		{
		}

		Thread::~Thread()
		{
			if (!m_isInterript)
			{
				m_isInterript = true;
			}
			if (m_thread != nullptr && m_thread->joinable())
			{
				m_thread->join();
				delete m_thread;
			}
		}

		void Thread::Start()
		{
			m_thread = new std::thread(std::bind(&Thread::Run, this));
		}

		void Thread::Stop()
		{
		}

		std::thread::id Thread::GetID() const
		{
			return m_thread->get_id();
		}

		void Thread::Interrupt()
		{
			m_isInterript.store(true);
		}

		bool Thread::IsInterrupted() const
		{
			return m_isInterript;
		}

		void Thread::Join()
		{
			if (m_thread != nullptr)
			{
				m_thread->join();
			}
		}

		void Thread::Detach()
		{
			if (m_thread != nullptr)
			{
				m_thread->detach();
			}
		}

		void Thread::Run()
		{
			if (m_runnable != nullptr)
			{
				m_runnable->Run();
			}
			else if (m_function)
			{
				m_function();
			}
			else
			{
			}
		}

		std::thread::id CurrentThreadId()
		{
			return std::this_thread::get_id();
		}

		std::string CurrentThreadStrId()
		{
			std::thread::id id = std::this_thread::get_id();
			std::ostringstream oss;
			oss << std::this_thread::get_id();
			return std::string(oss.str());
		}

		void Sleep(const int seconds)
		{
			std::this_thread::sleep_for(std::chrono::seconds(seconds));
		}

		void SleepMs(const int millisecond)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));
		}
	}
}