///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/ClientProcess.h"
#include "System/Threading/Thread.h"
#include "System/Net/TcpClient.h"
#include "System/Net/Sockets/Socket.h"
#include "System/HCN/ClientProcessStartEventArgs.h"
#include "System/HCN/ClientProcessStopEventArgs.h"
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
		ClientProcess::ClientProcess()
		{
			m_thread = std::make_shared<Thread>(std::bind(&ClientProcess::AsyncStart, this));
		}

		ClientProcess::~ClientProcess()
		{
		}

		void ClientProcess::Start()
		{
			m_thread->Start();
		}

		void ClientProcess::AsyncStart()
		{
			m_is_start = true;
			this->OnStart(ClientProcessStartEventArgs());
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
							m_clients.erase(itr);
							this->OnOffLine(TcpOffLineEventArgs((itr->second)->GetClient()));
						}
					}
				}
			}
			this->OnStop(ClientProcessStopEventArgs());
		}

		size_t ClientProcess::GetClients() const
		{
			return m_clients.size();
		}

		void ClientProcess::AddClient(const TcpClientPtr &client)
		{
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_tcpclients.push_back(client);
				m_cond.notify_one();
			}
			this->OnOnLine(TcpOnLineEventArgs(client));
		}

		void ClientProcess::Stop()
		{
			m_is_start = false;
		}

		void ClientProcess::OnStart(ClientProcessStartEventArgs& e)
		{
			if (this->ClientProcessStart != nullptr)
			{
				this->ClientProcessStart(e);
			}
		}

		void ClientProcess::OnStop(ClientProcessStopEventArgs & e)
		{
			if (this->ClientProcessStop != nullptr)
			{
				this->ClientProcessStop(e);
			}
		}

		void ClientProcess::OnOnLine(TcpOnLineEventArgs& e)
		{
			if (this->OnLine != nullptr)
			{
				this->OnLine(e);
			}
		}

		void ClientProcess::OnOffLine(TcpOffLineEventArgs& e)
		{
			if (this->OffLine != nullptr)
			{
				this->OffLine(e);
			}
		}

		void ClientProcess::OnSelectError(TcpSelectErrorEventArgs& e)
		{
			if (this->SelectError != nullptr)
			{
				this->SelectError(e);
			}
		}
	}
}