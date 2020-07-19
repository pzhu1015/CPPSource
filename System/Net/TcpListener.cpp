///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Net/TcpListener.h"
#include "System/Net/Sockets/Socket.h"
#include "System/Net/TcpClient.h"
#include "System/Net/IPAddress.h"
#include "System/Net/IPEndPoint.h"

namespace System
{
	namespace Net
	{
		TcpListener::TcpListener(const IPEndPointPtr &localEp)
		{
			m_server = std::make_shared<Socket>(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			m_server->Bind(localEp);
		}

		TcpListener::TcpListener(int port)
		{
			m_server = std::make_shared<Socket>(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			m_server->Bind(std::make_shared<IPEndPoint>(std::make_shared<IPAddress>("0.0.0.0"), port));
		}

		TcpListener::TcpListener(const IPAddressPtr &localaddr, int port)
		{
			m_server = std::make_shared<Socket>(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			m_server->Bind(std::make_shared<IPEndPoint>(localaddr, port));
		}

		EndPointPtr TcpListener::GetLocalEndPoint() const
		{
			return m_server->GetLocalEndPoint();
		}

		SocketPtr TcpListener::GetServer() const
		{
			return m_server;
		}

		SocketPtr TcpListener::AcceptSocket()
		{
			return m_server->Accept();
		}

		TcpClientPtr TcpListener::AcceptTcpClient()
		{
			SocketPtr socket = m_server->Accept();
			TcpClientPtr client = std::make_shared<TcpClient>(socket);
			return client;
		}

		void TcpListener::Start()
		{
			m_server->Listen(SOMAXCONN);
		}

		void TcpListener::Start(int backlog)
		{
			m_server->Listen(backlog);
		}

		void TcpListener::Stop()
		{
			m_server->Close();
			m_server->Dispose();
		}
	}
}
