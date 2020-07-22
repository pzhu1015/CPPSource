///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/SelectTcpClient.h"
#include "System/Net/TcpClient.h"
#include "System/Net/Sockets/Socket.h"
#include "System/HCN/TcpReceiveEventArgs.h"
#include "System/HCN/TcpSendEventArgs.h"
#include "System/HCN/TcpConnectEventArgs.h"
#include "System/HCN/Msg.h"
namespace System
{
	namespace HCN
	{
		SelectTcpClient::SelectTcpClient()
		{
			m_client = std::make_shared<TcpClient>();
		}
		SelectTcpClient::SelectTcpClient(const TcpClientPtr& client)
		{
			m_client = client;
		}

		SelectTcpClient::~SelectTcpClient()
		{
			delete[] m_buff;
		}

		bool SelectTcpClient::Read()
		{
			char* szRecv = m_buff + m_read_pos;
			int length = m_client->GetClient()->Receive(szRecv, BUFF_SIZE);
			if (length <= 0)
			{
				return false;
			}

			m_read_pos += length;
			while (m_read_pos >= sizeof(Msg))
			{
				Msg* msg = (Msg*)m_buff;
				OnReceive(TcpReceiveEventArgs(m_client, msg));
				if (m_read_pos >= msg->GetLength())
				{
					int last_size = m_read_pos - msg->GetLength();
					memcpy(m_buff, m_buff + msg->GetLength(), last_size);
					m_read_pos = last_size;
				}
				else
				{
					break;
				}
			}
			return true;
		}

		void SelectTcpClient::Write(char* data, int length)
		{
			m_client->GetClient()->Send(data, length);
			this->OnSend(TcpSendEventArgs());
		}

		void SelectTcpClient::Connect(const std::string & ip, int port)
		{
			m_client->Connect(ip, port);
			this->OnConnect(TcpConnectEventArgs(m_client));
		}

		TcpClientPtr SelectTcpClient::GetClient() const
		{
			return m_client;
		}

		void SelectTcpClient::OnReceive(const TcpReceiveEventArgs & e)
		{
			if (Receive != nullptr)
			{
				this->Receive(e);
			}
		}

		void SelectTcpClient::OnSend(const TcpSendEventArgs & e)
		{
			if (Send != nullptr)
			{
				this->Send(e);
			}
		}
		void SelectTcpClient::OnConnect(const TcpConnectEventArgs & e)
		{
			if (Connected != nullptr)
			{
				this->Connected(e);
			}
		}
	}
}