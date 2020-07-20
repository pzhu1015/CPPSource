///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_THREADING_PTRS_H
#define SYSTEM_THREADING_PTRS_H
#include <memory>
namespace System
{
	namespace Threading
	{
		class Thread;
		class ThreadPool;
		class Runnable;
		class Semaphore;
		typedef std::shared_ptr<Runnable> RunnablePtr;
		typedef std::shared_ptr<Thread> ThreadPtr;
		typedef std::shared_ptr<ThreadPool> ThreadPoolPtr;
		typedef std::shared_ptr<Semaphore> SemaphorePtr;
	}
}

#endif // !SYSTEM_THREADING_PTRS_H
