///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Net/TcpListener.h"

namespace System
{
	namespace Net
	{
		TcpListener::TcpListener(IPEndPoint * localEp)
		{
			m_server = new Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			m_server->Bind(localEp);
		}

		TcpListener::TcpListener(int port)
		{
			m_server = new Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			m_server->Bind(new IPEndPoint(new IPAddress("0.0.0.0"), port));
		}

		TcpListener::TcpListener(IPAddress * localaddr, int port)
		{
			m_server = new Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			m_server->Bind(new IPEndPoint(localaddr, port));
		}

		EndPoint * TcpListener::GetLocalEndPoint() const
		{
			return m_server->GetLocalEndPoint();
		}

		Socket * TcpListener::GetServer() const
		{
			return m_server;
		}

		Socket * TcpListener::AcceptSocket()
		{
			return m_server->Accept();
		}

		TcpClient * TcpListener::AcceptTcpClient()
		{
			Socket* socket = m_server->Accept();
			TcpClient* client = new TcpClient();
			client->SetClient(socket);
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
