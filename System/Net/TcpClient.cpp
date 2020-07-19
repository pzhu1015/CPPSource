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
#include "System/Net/IPEndPoint.h"
#include "System/Net/IPAddress.h"
#include "System/InvalidOperationException.h"
#include "System/ArgumentNullException.h"
#include "System/ArgumentOutOfRangeException.h"
#include "System/SocketException.h"

namespace System
{
	namespace Net
	{
		TcpClient::TcpClient()
		{
			m_family = AddressFamily::InterNetwork;
		}

		TcpClient::TcpClient(const IPEndPointPtr &localEP)
		{
			if (localEP == nullptr)
			{
				throw ArgumentNullException("localEP");
			}
			m_family = localEP->GetAddressFamily();
			Initialize();
			m_client->Bind(localEP);
		}

		TcpClient::TcpClient(AddressFamily family)
		{
			m_family = family;
			Initialize();
		}

		TcpClient::TcpClient(const std::string & hostname, int port)
		{
			if (hostname == "")
			{
				throw ArgumentNullException("hostname");
			}
			if (port > IPEndPoint::MAXPORT || port < IPEndPoint::MINPORT)
			{
				throw ArgumentOutOfRangeException("port");
			}
			Connect(hostname, port);
		}

		TcpClient::TcpClient(const SocketPtr &acceptedSocket)
		{
			m_client = acceptedSocket;
			m_active = true;
		}

		TcpClient::~TcpClient()
		{

		}

		int TcpClient::GetAvailable() const
		{
			return m_client->GetAvailable();
		}

		SocketPtr TcpClient::GetClient() const
		{
			return m_client;
		}

		void TcpClient::SetClient(const SocketPtr &client)
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

		void TcpClient::Dispose(bool disposing)
		{
			if (disposing)
			{
				IDisposable* stream = dynamic_cast<IDisposable*>(m_stream.get());
				if (stream != nullptr)
				{
					stream->Dispose();
				}
				else
				{
					if (m_client != nullptr)
					{
						m_client->Close();
						m_client = nullptr;
					}
				}
			}
		}

		void TcpClient::Initialize()
		{
			m_client = std::make_shared<Socket>(m_family, SocketType::Stream, ProtocolType::Tcp);
			m_active = false;
		}

		void TcpClient::Connect(const IPEndPointPtr &remoteEP)
		{
			if (remoteEP == nullptr)
			{
				throw ArgumentNullException("remoteEP");
			}
			m_client->Connect(remoteEP);
			m_active = true;
		}

		void TcpClient::Connect(const IPAddressPtr &address, int port)
		{
			if (address == nullptr)
			{
				throw ArgumentNullException("address");
			}
			if (port > IPEndPoint::MAXPORT || port < IPEndPoint::MINPORT)
			{
				throw ArgumentOutOfRangeException("port");
			}
			if (m_active)
			{
				throw SocketException("socket is conntcted");
			}
			IPEndPointPtr remoteEP = std::make_shared<IPEndPoint>(address, port);
			Connect(remoteEP);
			m_active = true;
		}

		void TcpClient::Connect(const std::string & ip, int port)
		{
			if (ip == "")
			{
				throw ArgumentNullException("ip");
			}
			if (port > IPEndPoint::MAXPORT || port < IPEndPoint::MINPORT)
			{
				throw ArgumentOutOfRangeException("port");
			}
			if (m_active)
			{
				throw SocketException("socket is connected");
			}
			m_client->Connect(ip, port);
			m_active = true;
		}

		NetworkStreamPtr TcpClient::GetStream()
		{
			if (!m_client->GetConnected())
			{
				throw InvalidOperationException("not connected");
			}
			if (m_stream == nullptr)
			{
				m_stream = std::make_shared<NetworkStream>(m_client, true);
			}
			return m_stream;
		}

		void TcpClient::Dispose()
		{
			Dispose(true);
		}
	}
}