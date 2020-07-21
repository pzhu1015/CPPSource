///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/IOProcess.h"
#include "System/Threading/Thread.h"
#include "System/Net/TcpClient.h"
#include "System/Net/Sockets/Socket.h"
#include "System/HCN/IOProcessStartEventArgs.h"
#include "System/HCN/IOProcessStopEventArgs.h"
#include "System/HCN/TcpOnLineEventArgs.h"
#include "System/HCN/TcpOffLineEventArgs.h"
#include "System/HCN/TcpSelectErrorEventArgs.h"
#include "System/Net/Sockets/NetworkStream.h"
#include "System/IO/BufferedStream.h"
#include "System/HCN/SelectTcpClient.h"

using namespace System::Net::Sockets;

namespace System
{
	namespace HCN
	{
		IOProcess::IOProcess()
		{
			m_thread = std::make_shared<Thread>(std::bind(&IOProcess::AsyncStart, this));
		}

		IOProcess::~IOProcess()
		{
		}

		void IOProcess::Start()
		{
			m_thread->Start();
		}

		void IOProcess::AsyncStart()
		{
			m_is_start = true;
			this->OnStart(IOProcessStartEventArgs());
			while (m_is_start)
			{
				//TODO handle client to receive data
				if (!m_tcpclients.empty())
				{
					std::lock_guard<std::mutex> lock(m_mutex);
					if (!m_tcpclients.empty())
					{
						for (auto client : m_tcpclients)
						{
							SocketPtr socket = client->GetClient();
							SelectTcpClientPtr sclient = std::make_shared<SelectTcpClient>(client);
							sclient->Receive = this->Receive;
							sclient->Send = this->Send;
							m_clients[socket->GetHandle()] = sclient;
						}
						m_tcpclients.clear();
					}
				}
				if (m_clients.empty())
				{
					std::unique_lock <std::mutex> lock(m_mutex);
					if (m_clients.empty())
					{
						m_cond.wait_for(lock, std::chrono::milliseconds(1000));
						continue;
					}
				}

				fd_set checkRead;
				FD_ZERO(&checkRead);
				for (auto client : m_clients)
				{
					FD_SET(client.first, &checkRead);
				}
				int ret = Socket::Select(&checkRead, nullptr, nullptr, 100);
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
					for (size_t i = 0; i < checkRead.fd_count; i++)
					{
						SOCKET sock = checkRead.fd_array[i];
						auto itr = m_clients.find(sock);
						bool rslt = (itr->second)->Read();
						if (!rslt)
						{
							this->OnOffLine(TcpOffLineEventArgs((itr->second)->GetClient()));
							m_clients.erase(itr);
						}
					}
				}
			}
			this->OnStop(IOProcessStopEventArgs());
		}

		size_t IOProcess::GetClients() const
		{
			return m_clients.size();
		}

		void IOProcess::AddClient(const TcpClientPtr &client)
		{
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_tcpclients.push_back(client);
				m_cond.notify_one();
			}
			this->OnOnLine(TcpOnLineEventArgs(client));
		}

		void IOProcess::Stop()
		{
			m_is_start = false;
		}

		void IOProcess::OnStart(const IOProcessStartEventArgs& e)
		{
			if (this->IOProcessStart != nullptr)
			{
				this->IOProcessStart(e);
			}
		}

		void IOProcess::OnStop(const IOProcessStopEventArgs & e)
		{
			if (this->IOProcessStop != nullptr)
			{
				this->IOProcessStop(e);
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
	}
}