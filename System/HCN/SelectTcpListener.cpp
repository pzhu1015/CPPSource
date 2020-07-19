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
#include "System/HCN/Process.h"
#include "System/HCN/TcpStartEventArgs.h"
#include "System/HCN/TcpStopEventArgs.h"
#include "System/HCN/TcpAcceptEventArgs.h"
#include "System/HCN/TcpReceiveEventArgs.h"
#include "System/HCN/TcpSendEventArgs.h"
#include "System/HCN/TcpSelectErrorEventArgs.h"
#include "System/HCN/ProcessStartEventArgs.h"
#include "System/HCN/OnLineEventArgs.h"
#include "System/HCN/OffLineEventArgs.h"
#include "System/Threading/Thread.h"
#include "System/Threading/ThreadPool.h"

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
			m_threadpool = std::make_shared<ThreadPool>(10000, 10);
			m_thread = std::make_shared<Thread>(std::bind(&SelectTcpListener::AsyncStart, this, port, threads));
			return true;
		}

		bool SelectTcpListener::Stop()
		{
			m_is_start = false;
			return true;
		}

		void SelectTcpListener::OnStart(TcpStartEventArgs * e)
		{
			if (this->Started != nullptr)
			{
				this->Started(e);
				delete e;
			}
		}

		void SelectTcpListener::OnStop(TcpStopEventArgs * e)
		{
			if (this->Stoped != nullptr)
			{
				this->Stoped(e);
				delete e;
			}
		}

		void SelectTcpListener::OnAccept(TcpAcceptEventArgs * e)
		{
			if (this->Accepted != nullptr)
			{
				this->Accepted(e);
				delete e;
			}
		}

		void SelectTcpListener::OnReceive(TcpReceiveEventArgs * e)
		{
			if (this->Received != nullptr)
			{
				this->Received(e);
				delete e;
			}
		}

		void SelectTcpListener::OnSend(TcpSendEventArgs * e)
		{
			if (this->Send != nullptr)
			{
				this->Send(e);
				delete e;
			}
		}

		void SelectTcpListener::OnSelectError(TcpSelectErrorEventArgs * e)
		{
			if (this->SelectError != nullptr)
			{
				this->SelectError(e);
				delete e;
			}
		}

		void SelectTcpListener::AsyncStart(int port, int threads)
		{
			m_server = std::make_shared<TcpListener>(port);
			m_server->Start();
			for (int i = 0; i < threads; i++)
			{
				m_clients.push_back(std::make_shared<Process>());
				m_clients[i]->ProcessStart = std::bind(&SelectTcpListener::ProcessStart, this, std::placeholders::_1);
				m_clients[i]->OnLine = std::bind(&SelectTcpListener::OnLine, this, std::placeholders::_1);
				m_clients[i]->OffLine = std::bind(&SelectTcpListener::OffLine, this, std::placeholders::_1);
				m_clients[i]->Start();
			}
			System::Threading::Sleep(1);
			m_is_start = true;
			OnStart(new TcpStartEventArgs(port, threads));

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
					this->OnSelectError(new TcpSelectErrorEventArgs());
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
		}

		void SelectTcpListener::AsyncAccept(const TcpClientPtr &client)
		{
			size_t min_size = -1;
			ProcessPtr min_clinet;
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
			this->OnAccept(new TcpAcceptEventArgs(client));
		}

		void SelectTcpListener::ProcessStart(ProcessStartEventArgs * e)
		{
			if (this->TcpProcessStart != nullptr)
			{
				this->TcpProcessStart(e);
				delete e;
			}
		}

		void SelectTcpListener::OnLine(OnLineEventArgs * e)
		{
			if (this->TcpClientOnLine != nullptr)
			{
				this->TcpClientOnLine(e);
				delete e;
			}
		}

		void SelectTcpListener::OffLine(OffLineEventArgs * e)
		{
			if (this->TcpClientOffLine != nullptr)
			{
				this->TcpClientOffLine(e);
				delete e;
			}
		}
	}
}
