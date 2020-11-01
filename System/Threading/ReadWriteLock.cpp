///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Threading/ReadWriteLock.h"
namespace System
{
	namespace Threading
	{
		ReadWriteLock::ReadWriteLock()
			: m_nReaderCount(0), m_hWriterEvent(NULL), m_hNoReadersEvent(NULL)
		{
			m_hWriterEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
			m_hNoReadersEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
			InitializeCriticalSection(&m_csLockWriter);
			InitializeCriticalSection(&m_csReaderCount);
		}


		ReadWriteLock::~ReadWriteLock()
		{
			DeleteCriticalSection(&m_csLockWriter);
			DeleteCriticalSection(&m_csReaderCount);
			CloseHandle(m_hWriterEvent);
			CloseHandle(m_hNoReadersEvent);
		}


		void ReadWriteLock::LockReader()
		{
			bool bLoop = true;
			while (bLoop)
			{
				WaitForSingleObject(m_hWriterEvent, INFINITE);
				IncrementReaderCount();
				if (WaitForSingleObject(m_hWriterEvent, 0) != WAIT_OBJECT_0)
				{
					DecrementReaderCount();
				}
				else
				{
					bLoop = false;
				}
			}
		}


		void ReadWriteLock::UnlockReader()
		{
			DecrementReaderCount();
		}


		void ReadWriteLock::LockWriter()
		{
			EnterCriticalSection(&m_csLockWriter);
			WaitForSingleObject(m_hWriterEvent, INFINITE);
			ResetEvent(m_hWriterEvent);
			WaitForSingleObject(m_hNoReadersEvent, INFINITE);
			LeaveCriticalSection(&m_csLockWriter);
		}


		void ReadWriteLock::UnlockWriter()
		{
			SetEvent(m_hWriterEvent);
		}


		void ReadWriteLock::IncrementReaderCount()
		{
			EnterCriticalSection(&m_csReaderCount);
			m_nReaderCount++;
			ResetEvent(m_hNoReadersEvent);
			LeaveCriticalSection(&m_csReaderCount);
		}


		void ReadWriteLock::DecrementReaderCount()
		{
			EnterCriticalSection(&m_csReaderCount);
			m_nReaderCount--;
			if (m_nReaderCount <= 0)
			{
				SetEvent(m_hNoReadersEvent);
			}
			LeaveCriticalSection(&m_csReaderCount);
		}
	}
}