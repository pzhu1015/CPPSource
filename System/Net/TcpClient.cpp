///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Net/TcpClient.h"
#include "System/Net/Sockets/Socket.h"
#include "System/Net/Sockets/NetworkStream.h"

namespace System
{
	namespace Net
	{
		TcpClient::TcpClient()
		{
			m_client = new Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
		}

		TcpClient::TcpClient(IPEndPoint * localEP)
		{
			m_client = new Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			m_client->Bind(localEP);
		}

		TcpClient::TcpClient(AddressFamily family)
		{
			m_client = new Socket(family, SocketType::Stream, ProtocolType::Tcp);
		}

		TcpClient::TcpClient(const std::string & hostname, int port)
		{
			m_client = new Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			m_client->Connect(hostname, port);
		}

		TcpClient::~TcpClient()
		{
			delete m_client;
		}

		int TcpClient::GetAvailable() const
		{
			return m_client->GetAvailable();
		}

		Socket* TcpClient::GetClient() const
		{
			return m_client;
		}

		void TcpClient::SetClient(Socket * client)
		{
			m_client = client;
		}

		bool TcpClient::GetConnected() const
		{
			return m_client->GetConnected();
		}

		int TcpClient::GetReceiveBuffSize() const
		{
			return m_client->GetReceiveBuffSize();
		}

		void TcpClient::SetReceiveBuffSize(int size)
		{
			m_client->SetReceiveBuffSize(size);
		}

		int TcpClient::GetSendBuffSize() const
		{
			return m_client->GetSendBuffSize();
		}

		void TcpClient::SetSendBuffSize(int size)
		{
			m_client->SetSendBuffSize(size);
		}

		int TcpClient::GetReceiveTimeout() const
		{
			return m_client->GetReceiveTimeout();
		}

		void TcpClient::SetReceiveTimeout(int timeout)
		{
			m_client->SetReceiveTimeout(timeout);
		}

		int TcpClient::GetSendTimeout() const
		{
			return m_client->GetSendTimeout();
		}

		void TcpClient::SetSendTimeout(int timeout)
		{
			m_client->SetSendTimeout(timeout);
		}

		bool TcpClient::GetActive() const
		{
			return m_active;
		}

		void TcpClient::SetActive(bool active)
		{
			m_active = active;
		}

		void TcpClient::Connect(IPEndPoint* remoteEP)
		{
			m_client->Connect(remoteEP);
		}

		void TcpClient::Connect(IPAddress* address, int port)
		{
			m_client->Connect(address, port);
		}

		void TcpClient::Connect(const std::string & ip, int port)
		{
			m_client->Connect(ip, port);
		}

		NetworkStream* TcpClient::GetStream()
		{
			return new NetworkStream();
		}

		void TcpClient::Dispose()
		{
			if (m_client)
			{
				m_client->Dispose();
			}
		}
	}
}