///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/IOProcess.h"

#include "System/HCN/IOProcessReadStartEventArgs.h"
#include "System/HCN/IOProcessReadStopEventArgs.h"
#include "System/HCN/IOProcessWriteStartEventArgs.h"
#include "System/HCN/IOProcessWriteStopEventArgs.h"
#include "System/HCN/TcpOnLineEventArgs.h"
#include "System/HCN/TcpOffLineEventArgs.h"
#include "System/HCN/TcpSelectErrorEventArgs.h"
#include "System/HCN/TcpReceiveEventArgs.h"
#include "System/HCN/TcpSendEventArgs.h"
#include "System/HCN/TcpClientChannel.h"
#include "System/Memory/ObjectPool.h"
#include "System/Threading/Thread.h"

namespace System
{
	namespace HCN
	{
		
		IOProcess::IOProcess()
		{	
		}

		IOProcess::~IOProcess()
		{

		}

		void IOProcess::Start()
		{
			m_is_start = true;
			m_read_thread = std::make_shared<Thread>(std::bind(&IOProcess::AsyncStartRead, this));
			m_read_thread->Start();

			m_write_thread = std::make_shared<Thread>(std::bind(&IOProcess::AsyncStartWrite, this));
			m_write_thread->Start();
		}

		size_t IOProcess::GetClients() const
		{
			return m_clients.size();
		}

		void IOProcess::ConsumeRead()
		{
			for (auto itr : m_clients)
			{
				(itr.second)->ConsumeRead();
			}
		}

		void IOProcess::Stop()
		{
			m_is_start = false;
		}

		void IOProcess::OnReadStart(const IOProcessReadStartEventArgs& e)
		{
			if (this->IOProcessReadStart != nullptr)
			{
				this->IOProcessReadStart(e);
			}
		}

		void IOProcess::OnReadStop(const IOProcessReadStopEventArgs & e)
		{
			if (this->IOProcessReadStop != nullptr)
			{
				this->IOProcessReadStop(e);
			}
		}

		void IOProcess::OnWriteStart(const IOProcessWriteStartEventArgs& e)
		{
			if (this->IOProcessWriteStart != nullptr)
			{
				this->IOProcessWriteStart(e);
			}
		}

		void IOProcess::OnWriteStop(const IOProcessWriteStopEventArgs & e)
		{
			if (this->IOProcessWriteStop != nullptr)
			{
				this->IOProcessWriteStop(e);
			}
		}

		void IOProcess::OnOnLine(const TcpOnLineEventArgs& e)
		{
			if (this->OnLine != nullptr)
			{
				this->OnLine(e);
			}
		}

		void IOProcess::OnOffLine(const TcpOffLineEventArgs& e)
		{
			if (this->OffLine != nullptr)
			{
				this->OffLine(e);
			}
		}

		void IOProcess::OnSelectError(const TcpSelectErrorEventArgs& e)
		{
			if (this->SelectError != nullptr)
			{
				this->SelectError(e);
			}
		}

		void IOProcess::AsyncStartRead()
		{
			t_recv_event_pool = new ObjectPool<TcpReceiveEventArgs>(250000);
			m_recv_event_pool = t_recv_event_pool;
			
			this->OnReadStart(IOProcessReadStartEventArgs());
			IOReadHandle();
			this->OnReadStop(IOProcessReadStopEventArgs());
			delete t_recv_event_pool;
		}

		void IOProcess::AsyncStartWrite()
		{
			t_send_event_pool = new ObjectPool<TcpSendEventArgs>(250000);
			m_send_event_pool = t_send_event_pool;

			this->OnWriteStart(IOProcessWriteStartEventArgs());
			IOWriteHandle();
			this->OnWriteStop(IOProcessWriteStopEventArgs());
			delete t_send_event_pool;
		}
	}
}