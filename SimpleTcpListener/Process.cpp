///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "SimpleTcpListener/Process.h"
#include "System/Threading/Thread.h"
#include "System/Net/TcpClient.h"
#include "System/Net/Sockets/Socket.h"
#include "SimpleTcpListener/ProcessStartEventArgs.h"
#include "SimpleTcpListener/OnLineEventArgs.h"
#include "SimpleTcpListener/TcpSelectErrorEventArgs.h"

using namespace System::Threading;
using namespace System::Net::Sockets;

Process::Process()
{
	m_thread = new Thread(std::bind(&Process::AsyncStart, this));
}

Process::~Process()
{
	for (auto client : m_clients)
	{
		delete client.second;
	}
	m_clients.clear();
	for (auto tcp_client : m_tcpclients)
	{
		delete tcp_client;
	}
	m_tcpclients.clear();
	delete m_thread;
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
					Socket* socket = client->GetClient();
					m_clients[socket->GetHandle()] = client;
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
				//(itr->second)->GetClient()->Receive();
			}
		}
	}
}

size_t Process::GetClients() const
{
	return m_clients.size();
}

void Process::AddClient(System::Net::TcpClient * client)
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
