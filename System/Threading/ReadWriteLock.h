///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_THREADING_READWRITELOCK_H
#define SYSTEM_THREADING_READWRITELOCK_H
#include "System/Base/DllExport.h"
#include <Windows.h>
namespace System
{
	namespace Threading
	{
		class ReadWriteLock final
		{
		public:
			ReadWriteLock();
			ReadWriteLock(const ReadWriteLock &cReadWriteLock) = delete;
			const ReadWriteLock& operator=(const ReadWriteLock &cReadWriteLock) = delete;
			~ReadWriteLock();
			void LockReader();
			void UnlockReader();
			void LockWriter();
			void UnlockWriter();
		private:
			void IncrementReaderCount();
			void DecrementReaderCount();
			HANDLE m_hWriterEvent;
			HANDLE m_hNoReadersEvent;
			int m_nReaderCount;

			//! Critical section for protecting lock writer method.

			CRITICAL_SECTION m_csLockWriter;
			//! Critical section for protecting reader count.

			CRITICAL_SECTION m_csReaderCount;
		};
	}
}
#endif // !SYSTEM_THREADING_READWRITELOCK_H
