///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/SelectTcpListener.h"
#include "System/Net/TcpListener.h"
#include "System/Net/TcpClient.h"
#include "System/Net/Sockets/Socket.h"
#include "System/HCN/IOProcess.h"
#include "System/HCN/TcpStartEventArgs.h"
#include "System/HCN/TcpStopEventArgs.h"
#include "System/HCN/TcpReceiveEventArgs.h"
#include "System/HCN/TcpSendEventArgs.h"
#include "System/HCN/TcpSelectErrorEventArgs.h"
#include "System/HCN/IOProcessStartEventArgs.h"
#include "System/HCN/TcpOnLineEventArgs.h"
#include "System/HCN/TcpOffLineEventArgs.h"
#include "System/Threading/Thread.h"
#include "System/Threading/ThreadPool.h"
#include "System/Threading/Semaphore.h"

#include <future>
#include <thread>

using namespace System::Net::Sockets;

namespace System
{
	namespace HCN
	{
		SelectTcpListener::SelectTcpListener()
		{

		}

		SelectTcpListener::~SelectTcpListener()
		{
		}

		bool SelectTcpListener::Start(int port, int threads)
		{
			m_start_sem = std::make_shared<Semaphore>(0);
			m_stop_sem = std::make_shared<Semaphore>(0);
			m_threadpool = std::make_shared<ThreadPool>(10000, 10);
			m_threadpool->Start();
			m_thread = std::make_shared<Thread>(std::bind(&SelectTcpListener::AsyncStart, this, port, threads));
			m_thread->Start();
			return true;
		}

		bool SelectTcpListener::Stop()
		{
			m_is_start = false;
			return true;
		}

		void SelectTcpListener::OnStart(const TcpStartEventArgs& e)
		{
			if (this->Started != nullptr)
			{
				this->Started(e);
			}
		}

		void SelectTcpListener::OnStop(const TcpStopEventArgs& e)
		{
			if (this->Stoped != nullptr)
			{
				this->Stoped(e);
			}
		}

		void SelectTcpListener::OnSelectError(const TcpSelectErrorEventArgs& e)
		{
			if (this->SelectError != nullptr)
			{
				this->SelectError(e);
			}
		}

		void SelectTcpListener::OnIOProcessStart(const IOProcessStartEventArgs& e)
		{
			m_start_sem->signal();
		}

		void SelectTcpListener::OnIOProcessStop(const IOProcessStopEventArgs & e)
		{
			m_stop_sem->signal();
		}

		void SelectTcpListener::AsyncStart(int port, int threads)
		{
			m_server = std::make_shared<TcpListener>(port);
			m_server->Start();
			for (int i = 0; i < threads; i++)
			{
				m_clients.push_back(std::make_shared<IOProcess>());
				m_clients[i]->IOProcessStart = std::bind(&SelectTcpListener::OnIOProcessStart, this, std::placeholders::_1);
				m_clients[i]->IOProcessStop = std::bind(&SelectTcpListener::OnIOProcessStop, this, std::placeholders::_1);
				m_clients[i]->OnLine = this->OnLine;
				m_clients[i]->OffLine = this->OffLine;
				m_clients[i]->Receive = this->Receive;
				m_clients[i]->Send = this->Send;
				m_clients[i]->SelectError = this->SelectError;
				m_clients[i]->Start();
			}
			for (auto c : m_clients)
			{
				m_start_sem->wait();
			}
			m_is_start = true;
			OnStart(TcpStartEventArgs(port, threads));

			size_t idx = 0;
			bool set = false;
			SOCKET sock = m_server->GetServer()->GetHandle();
			fd_set checkReadBack;
			while (m_is_start)
			{
				fd_set checkRead;
				if (!set)
				{
					FD_ZERO(&checkRead);
					FD_SET(sock, &checkRead);
					memcpy(&checkReadBack, &checkRead, sizeof(fd_set));
					set = true;
				}
				else
				{
					memcpy(&checkRead, &checkReadBack, sizeof(fd_set));
				}

				int ret = Socket::Select(&checkRead, nullptr, nullptr, 1);

				if (ret < 0)
				{
					this->OnSelectError(TcpSelectErrorEventArgs());
					continue;
				}
				else if (ret == 0)
				{
					continue;
				}
				else
				{
					TcpClientPtr client = m_server->AcceptTcpClient();
					m_threadpool->AddTask(std::bind(&SelectTcpListener::AsyncAccept, this, client, idx++));
					if (idx == m_clients.size())
					{
						idx = 0;
					}
				}
			}
			for (auto c : m_clients)
			{
				c->Stop();
			}
			for (auto c : m_clients)
			{
				m_stop_sem->wait();
			}
			m_threadpool->Stop();
			this->OnStop(TcpStopEventArgs());
		}

		void SelectTcpListener::AsyncAccept(const TcpClientPtr &client, size_t idx)
		{
			IOProcessPtr io_process = m_clients[idx];
			io_process->AddClient(client);
		}
	}
}
