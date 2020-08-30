///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/SelectIOProcess.h"
#include "System/HCN/TcpOnLineEventArgs.h"
#include "System/HCN/TcpOffLineEventArgs.h"
#include "System/HCN/TcpSelectErrorEventArgs.h"
#include "System/HCN/TcpClientChannel.h"
#include "System/Net/Sockets/Socket.h"
#include "System/Net/TcpClient.h"
#include "System/Threading/Thread.h"
using namespace System::Net::Sockets;
namespace System
{
	namespace HCN
	{
		SelectIOProcess::SelectIOProcess()
			:
			IOProcess()
		{
		}

		SelectIOProcess::~SelectIOProcess()
		{
		}

		void SelectIOProcess::AddClient(const TcpClientChannelPtr& channel)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			channel->Receive = this->Receive;
			channel->Send = this->Send;
			channel->SetRecvEventPool(m_recv_event_pool);
			channel->SetSendEventPool(m_send_event_pool);
			m_clients[channel->GetClient()->GetClient()->GetHandle()] = channel;
			this->OnOnLine(TcpOnLineEventArgs(channel->GetClient(), m_clients.size()));
			m_change = true;
			m_cond.notify_one();
		}


		void SelectIOProcess::IOReadHandle()
		{
			while (m_is_start)
			{
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
				if (m_change)
				{
					m_change = false;
					FD_ZERO(&checkRead);
					for (auto client : m_clients)
					{
						FD_SET(client.first, &checkRead);
					}
					memcpy(&m_check_read_back, &checkRead, sizeof(fd_set));
				}
				else
				{
					memcpy(&checkRead, &m_check_read_back, sizeof(fd_set));
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
						bool rslt = (itr->second)->ProduceRead();
						if (!rslt)
						{
							m_change = true;
							TcpClientPtr client = (itr->second)->GetClient();
							m_clients.erase(itr);
							this->OnOffLine(TcpOffLineEventArgs(client, m_clients.size()));
						}
					}
				}
			}
		}

		void SelectIOProcess::IOWriteHandle()
		{
			while (m_is_start)
			{
				if (m_clients.empty())
				{
					std::unique_lock <std::mutex> lock(m_mutex);
					if (m_clients.empty())
					{
						m_cond.wait_for(lock, std::chrono::milliseconds(1000));
						continue;
					}
				}
				Thread::Sleep(10);
				for (auto itr : m_clients)
				{
					itr.second->ConsumeWrite();
				}
			}
		}
	}
}