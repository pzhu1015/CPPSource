///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/TcpListenerChannel.h"
#include "System/HCN/IOProcess.h"
#include "System/HCN/SelectIOProcess.h"
#include "System/HCN/TcpStartEventArgs.h"
#include "System/HCN/TcpStopEventArgs.h"
#include "System/HCN/TcpReceiveEventArgs.h"
#include "System/HCN/TcpSendEventArgs.h"
#include "System/HCN/TcpSelectErrorEventArgs.h"
#include "System/HCN/IOProcessStartEventArgs.h"
#include "System/HCN/TcpOnLineEventArgs.h"
#include "System/HCN/TcpOffLineEventArgs.h"
#include "System/HCN/TcpClientChannel.h"
#include "System/Threading/Thread.h"
#include "System/Threading/ThreadPool.h"
#include "System/Threading/Semaphore.h"
#include "System/Net/TcpListener.h"
#include "System/Net/Sockets/Socket.h"

#include <thread>

using namespace System::Net::Sockets;

namespace System
{
	namespace HCN
	{
		TcpListenerChannel::TcpListenerChannel()
		{

		}

		TcpListenerChannel::~TcpListenerChannel()
		{
		}

		bool TcpListenerChannel::Start(int port, int threads)
		{
			m_start_sem = std::make_shared<Semaphore>(0);
			m_stop_sem = std::make_shared<Semaphore>(0);
			m_threadpool = std::make_shared<ThreadPool>(10000, 10);
			m_threadpool->Start();
			m_thread = std::make_shared<Thread>(std::bind(&TcpListenerChannel::AsyncStart, this, port, threads));
			m_thread->Start();
			return true;
		}

		bool TcpListenerChannel::Stop()
		{
			m_is_start = false;
			return true;
		}

		void TcpListenerChannel::OnStart(const TcpStartEventArgs& e)
		{
			if (this->Started != nullptr)
			{
				this->Started(e);
			}
		}

		void TcpListenerChannel::OnStop(const TcpStopEventArgs& e)
		{
			if (this->Stoped != nullptr)
			{
				this->Stoped(e);
			}
		}

		void TcpListenerChannel::OnSelectError(const TcpSelectErrorEventArgs& e)
		{
			if (this->SelectError != nullptr)
			{
				this->SelectError(e);
			}
		}

		void TcpListenerChannel::OnIOProcessStart(const IOProcessStartEventArgs& e)
		{
			m_start_sem->signal();
		}

		void TcpListenerChannel::OnIOProcessStop(const IOProcessStopEventArgs & e)
		{
			m_stop_sem->signal();
		}

		void TcpListenerChannel::AsyncStart(int port, int threads)
		{
			m_server = std::make_shared<TcpListener>(port);
			m_server->Start();
			for (int i = 0; i < threads; i++)
			{
				m_io_processor.push_back(GetIOProcess());
				m_io_processor[i]->Start();
			}
			for (auto p : m_io_processor)
			{
				m_start_sem->wait();
			}
			m_is_start = true;
			OnStart(TcpStartEventArgs(port, threads));
			SOCKET sock = m_server->GetServer()->GetHandle();
			AcceptHandle(sock);
			for (auto p : m_io_processor)
			{
				p->Stop();
			}
			for (auto p : m_io_processor)
			{
				m_stop_sem->wait();
			}
			m_threadpool->Stop();
			this->OnStop(TcpStopEventArgs());
		}

		void TcpListenerChannel::AsyncAccept(const TcpClientPtr &client, size_t idx)
		{
			IOProcessPtr io_process = m_io_processor[idx];
			TcpClientChannelPtr channel = std::make_shared<TcpClientChannel>(client);
			io_process->AddClient(channel);
		}
	}
}
