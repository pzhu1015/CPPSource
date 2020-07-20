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
#include "System/HCN/ClientProcess.h"
#include "System/HCN/TcpStartEventArgs.h"
#include "System/HCN/TcpStopEventArgs.h"
#include "System/HCN/TcpAcceptEventArgs.h"
#include "System/HCN/TcpReceiveEventArgs.h"
#include "System/HCN/TcpSendEventArgs.h"
#include "System/HCN/TcpSelectErrorEventArgs.h"
#include "System/HCN/ClientProcessStartEventArgs.h"
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
			m_thread = std::make_shared<Thread>(std::bind(&SelectTcpListener::AsyncStart, this, port, threads));
			return true;
		}

		bool SelectTcpListener::Stop()
		{
			m_is_start = false;
			
			return true;
		}

		void SelectTcpListener::OnStart(TcpStartEventArgs& e)
		{
			if (this->Started != nullptr)
			{
				this->Started(e);
			}
		}

		void SelectTcpListener::OnStop(TcpStopEventArgs& e)
		{
			if (this->Stoped != nullptr)
			{
				this->Stoped(e);
			}
		}

		void SelectTcpListener::OnAccept(TcpAcceptEventArgs& e)
		{
			if (this->Accepted != nullptr)
			{
				this->Accepted(e);
			}
		}

		void SelectTcpListener::OnSelectError(TcpSelectErrorEventArgs& e)
		{
			if (this->SelectError != nullptr)
			{
				this->SelectError(e);
			}
		}

		void SelectTcpListener::OnClientProcessStart(ClientProcessStartEventArgs& e)
		{
			m_start_sem->signal();
		}

		void SelectTcpListener::OnClientProcessStop(ClientProcessStopEventArgs & e)
		{
			m_stop_sem->signal();
		}

		void SelectTcpListener::AsyncStart(int port, int threads)
		{
			m_server = std::make_shared<TcpListener>(port);
			m_server->Start();
			for (int i = 0; i < threads; i++)
			{
				m_clients.push_back(std::make_shared<ClientProcess>());
				m_clients[i]->ClientProcessStart = std::bind(&SelectTcpListener::OnClientProcessStart, this, std::placeholders::_1);
				m_clients[i]->ClientProcessStop = std::bind(&SelectTcpListener::OnClientProcessStop, this, std::placeholders::_1);
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
					m_threadpool->AddTask(std::bind(&SelectTcpListener::AsyncAccept, this, client));
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
			this->OnStop(TcpStopEventArgs());
		}

		void SelectTcpListener::AsyncAccept(const TcpClientPtr &client)
		{
			size_t min_size = 0;
			ClientProcessPtr min_clinet;
			for (auto c : m_clients)
			{
				size_t size = c->GetClients();
				if (min_size < size)
				{
					min_size = size;
					min_clinet = c;
				}
			}
			min_clinet->AddClient(client);
			this->OnAccept(TcpAcceptEventArgs(client));
		}
	}
}
