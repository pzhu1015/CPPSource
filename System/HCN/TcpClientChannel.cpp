///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/TcpClientChannel.h"
#include "System/HCN/TcpSendEventArgs.h"
#include "System/HCN/TcpConnectEventArgs.h"
#include "System/HCN/TcpReceiveEventArgs.h"
#include "System/HCN/TcpSendEventArgs.h"
#include "System/HCN/Msg.h"
#include "System/Net/TcpClient.h"
#include "System/Net/Sockets/Socket.h"
#include "System/Memory/ObjectPool.h"
namespace System
{
	namespace HCN
	{
		TcpClientChannel::TcpClientChannel()
		{
			m_client = std::make_shared<TcpClient>();
		}

		TcpClientChannel::TcpClientChannel(const TcpClientPtr& client)
		{
			m_client = client;
		}

		TcpClientChannel::~TcpClientChannel()
		{
			delete[] m_recv_buff;
		}

		bool TcpClientChannel::ProduceRead()
		{
			char* szRecv = m_recv_buff + m_read_pos;
			int length = m_client->GetClient()->Receive(szRecv, RECV_BUFF_SIZE);
			if (length <= 0)
			{
				return false;
			}

			m_read_pos += length;
			std::vector<Msg*> msgs;
			while (m_read_pos >= sizeof(Msg))
			{
				Msg* msg = (Msg*)m_recv_buff;
				if (m_read_pos >= msg->GetLength())
				{
					char* copy_msg = new char[msg->GetLength()];
					memcpy(copy_msg, m_recv_buff, msg->GetLength());
					Msg* recv_msg = (Msg*)copy_msg;
					msgs.push_back(recv_msg);
					
					int last_size = m_read_pos - msg->GetLength();
					memcpy(m_recv_buff, m_recv_buff + msg->GetLength(), last_size);
					m_read_pos = last_size;
				}
				else
				{
					break;
				}
			}
			if (!msgs.empty())
			{
				std::lock_guard<std::mutex> lock(m_recv_mutex);
				for (auto msg : msgs)
				{
					m_recv_msgs.push_back(msg);
				}
			}
			return true;
		}

		bool TcpClientChannel::ConsumeRead()
		{
			std::vector<Msg*> msgs;
			if (!m_recv_msgs.empty())
			{
				std::lock_guard<std::mutex> lock(m_recv_mutex);
				msgs.swap(m_recv_msgs);
			}
			for (auto msg: msgs)
			{
				//TODO another thread to handle OnReceive
				TcpReceiveEventArgs args = m_recv_event_pool->Allocate();
				args.SetChannel(TcpClientChannelPtr(this));
				args.SetMsg(msg);
				this->OnReceive(args);
				m_recv_event_pool->Release(args);
			}
			return true;
		}

		void TcpClientChannel::ProduceWrite(Msg * msg)
		{
			std::lock_guard<std::mutex> lock(m_send_mutex);
			m_send_msgs.push_back(msg);
		}

		bool TcpClientChannel::ConsumeWrite()
		{
			std::vector<Msg*> msgs;
			if (!m_send_msgs.empty())
			{
				std::lock_guard<std::mutex> lock(m_send_mutex);
				msgs.swap(m_send_msgs);
			}
			for (auto msg : msgs)
			{
				const char* data = (const char*)msg;
				int send_length = msg->GetLength();
				while (true)
				{
					if (m_write_pos + send_length >= SEND_BUFF_SIZE)
					{
						int copy_length = SEND_BUFF_SIZE - m_write_pos;
						memcpy(m_send_buff + m_write_pos, data, copy_length);
						data += copy_length;
						send_length -= copy_length;
						int ret = m_client->GetClient()->Send(m_send_buff, SEND_BUFF_SIZE);
						if (ret < 0)
						{
							return false;
						}
						TcpSendEventArgs args = m_send_event_pool->Allocate();
						this->OnSend(args);
						m_send_event_pool->Release(args);

						m_write_pos = 0;
					}
					else
					{
						memcpy(m_send_buff + m_write_pos, data, send_length);
						m_write_pos += send_length;
						break;
					}
				}
			}
			return true;
		}

		void TcpClientChannel::Connect(const std::string & ip, int port)
		{
			m_client->Connect(ip, port);
			this->OnConnect(TcpConnectEventArgs(m_client));
		}

		TcpClientPtr TcpClientChannel::GetClient() const
		{
			return m_client;
		}

		void TcpClientChannel::SetSendEventPool(ObjectPool<TcpSendEventArgs>* pool)
		{
			m_send_event_pool = pool;
		}

		void TcpClientChannel::SetRecvEventPool(ObjectPool<TcpReceiveEventArgs>* pool)
		{
			m_recv_event_pool = pool;
		}

		void TcpClientChannel::OnReceive(const TcpReceiveEventArgs & e)
		{
			if (Receive != nullptr)
			{
				this->Receive(e);
			}
		}

		void TcpClientChannel::OnSend(const TcpSendEventArgs & e)
		{
			if (Send != nullptr)
			{
				this->Send(e);
			}
		}
		void TcpClientChannel::OnConnect(const TcpConnectEventArgs & e)
		{
			if (Connected != nullptr)
			{
				this->Connected(e);
			}
		}
	}
}