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
#include <Windows.h>
namespace System
{
	namespace Threading
	{
		struct SemaphoreHandle;
		class SYSTEM_API Semaphore final
		{
		public:
			Semaphore(const int &value = 0);
			~Semaphore();

			void wait();                       // semaphore - 1
			bool wait(const unsigned int &ms); // semaphore - 1 , timeout ms
			void signal();                    // semaphore + 1

		private:
			SemaphoreHandle *semaphoreHandle;
		};
	}
}
#endif // !SYSTEM_THREADING_SEMAPHORE_H
