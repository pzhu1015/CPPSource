///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_TCPLISTENER_H
#define SYSTEM_NET_TCPLISTENER_H
#include "System/DllExport.h"
#include "System/Net/EndPoint.h"

namespace System
{
	namespace Net
	{
		class TcpClient;
		class IPAddress;
		class IPEndPoint;
		namespace Sockets
		{
			class Socket;
		}
		class SYSTEM_API TcpListener
		{
		public:
			TcpListener(IPEndPoint* localEp);
			TcpListener(int port);
			TcpListener(IPAddress* localaddr, int port);

			EndPoint* GetLocalEndPoint() const;
			Socket* GetServer() const;
			Socket* AcceptSocket();
			TcpClient* AcceptTcpClient();
			void Start();
			void Start(int backlog);
			void Stop();
		private:
			Socket* m_server;
		};
	}
}

#endif // !SYSTEM_NET_TCPLISTENER_H
