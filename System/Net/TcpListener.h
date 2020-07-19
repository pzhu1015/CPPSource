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
#include "System/Net/Ptrs.h"
#include "System/Net/Sockets/Ptrs.h"

namespace System
{
	namespace Net
	{
		class SYSTEM_API TcpListener
		{
		public:
			TcpListener(const IPEndPointPtr &localEp);
			TcpListener(int port);
			TcpListener(const IPAddressPtr &localaddr, int port);

			EndPointPtr GetLocalEndPoint() const;
			SocketPtr GetServer() const;
			SocketPtr AcceptSocket();
			TcpClientPtr AcceptTcpClient();
			void Start();
			void Start(int backlog);
			void Stop();
		private:
			SocketPtr m_server;
		};
	}
}

#endif // !SYSTEM_NET_TCPLISTENER_H
