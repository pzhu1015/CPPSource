///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/SelectTcpListenerChannel.h"
#include "System/HCN/SelectIOProcess.h"
#include "System/HCN/TcpSelectErrorEventArgs.h"
#include "System/Net/TcpListener.h"
#include "System/Net/Sockets/Socket.h"
#include "System/Threading/ThreadPool.h"
using namespace System::Net::Sockets;
namespace System
{
	namespace HCN
	{
		SelectTcpListenerChannel::SelectTcpListenerChannel()
			:
			TcpListenerChannel()
		{
		}

		SelectTcpListenerChannel::~SelectTcpListenerChannel()
		{
		}

		IOProcessPtr SelectTcpListenerChannel::GetIOProcess()
		{
			IOProcessPtr io_process = std::make_shared<SelectIOProcess>();
			io_process->IOProcessStart = std::bind(&TcpListenerChannel::OnIOProcessStart, this, std::placeholders::_1);
			io_process->IOProcessStop = std::bind(&TcpListenerChannel::OnIOProcessStop, this, std::placeholders::_1);
			io_process->OnLine = this->OnLine;
			io_process->OffLine = this->OffLine;
			io_process->Receive = this->Receive;
			io_process->Send = this->Send;
			io_process->SelectError = this->SelectError;
			return io_process;
		}
		void SelectTcpListenerChannel::AcceptHandle(SOCKET sock)
		{
			size_t idx = 0;
			bool set = false;
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
					m_threadpool->AddTask(std::bind(&TcpListenerChannel::AsyncAccept, this, client, idx++));
					if (idx == m_io_processor.size())
					{
						idx = 0;
					}
				}
			}
		}
	}
}