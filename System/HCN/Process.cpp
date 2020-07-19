///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/Process.h"
#include "System/Threading/Thread.h"
#include "System/Net/TcpClient.h"
#include "System/Net/Sockets/Socket.h"
#include "System/HCN/ProcessStartEventArgs.h"
#include "System/HCN/OnLineEventArgs.h"
#include "System/HCN/TcpSelectErrorEventArgs.h"
#include "System/Net/Sockets/NetworkStream.h"
#include "System/IO/BufferedStream.h"

using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;

namespace System
{
	namespace HCN
	{
		Process::Process()
		{
			m_thread = std::make_shared<Thread>(std::bind(&Process::AsyncStart, this));
		}

		Process::~Process()
		{
		}

		void Process::Start()
		{
			m_thread->Start();
		}

		void Process::AsyncStart()
		{
			m_is_start = true;
			this->OnStart(new ProcessStartEventArgs());
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
							m_clients[socket->GetHandle()] = std::make_shared<ClientWrapper>(client);
						}
					}
				}
				if (m_clients.empty())
				{
					std::unique_lock <std::mutex> lock(m_mutex);
					if (m_clients.empty())
					{
						m_cond.wait_for(lock, std::chrono::milliseconds(10000));
						continue;
					}
				}

				fd_set checkRead;
				int ret = Socket::Select(&checkRead, nullptr, nullptr, 100);
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
					for (size_t i = 0; i < checkRead.fd_count; i++)
					{
						SOCKET sock = checkRead.fd_array[i];
						auto itr = m_clients.find(sock);
						//TODO need client wraper to record receive's buff position
						//(itr->second)->m_stream->Read();
					}
				}
			}
		}

		size_t Process::GetClients() const
		{
			return m_clients.size();
		}

		void Process::AddClient(const TcpClientPtr &client)
		{
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_tcpclients.push_back(client);
			}
			this->OnOnLine(new OnLineEventArgs(client));
		}

		void Process::OnStart(ProcessStartEventArgs * e)
		{
			if (this->ProcessStart != nullptr)
			{
				this->ProcessStart(e);
				delete e;
			}
		}

		void Process::OnOnLine(OnLineEventArgs * e)
		{
			if (this->OnLine != nullptr)
			{
				this->OnLine(e);
				delete e;
			}
		}

		void Process::OnOffLine(OffLineEventArgs * e)
		{
			if (this->OffLine != nullptr)
			{
				this->OffLine(e);
			}
		}

		void Process::OnSelectError(TcpSelectErrorEventArgs * e)
		{
			if (this->SelectError != nullptr)
			{
				this->SelectError(e);
			}
		}
		ClientWrapper::ClientWrapper(const TcpClientPtr &client)
		{
			m_client = client;
			m_stream = std::make_shared<BufferedStream>(client->GetStream());
		}
		ClientWrapper::~ClientWrapper()
		{
		}
	}
}