///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_SIMPLETCPCLITENER_H
#define SYSTEM_NET_SIMPLETCPCLITENER_H
#include "System/DllExport.h"
#include "System/IPEndPoint.h"
#include "System/SimpleTcpClient.h"
#include <memory>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define FD_SETSIZE      10240
#include<Windows.h>
#include<WinSock2.h>
#else
#include <unistd.h>
#include <arpa/net.h>
#include <string.h>

#define SOCKET int
#define INVALID_SOCKET	(SOCKET)(~0)
#define SOCKET_ERROR			(-1)
#endif

namespace System
{
	namespace Net
	{
		class SYSTEM_API SimpleTcpListener
		{
		public:
			SimpleTcpListener();
			SimpleTcpListener(IPEndPoint* endpoint);
			SimpleTcpListener(int port);
			SimpleTcpListener(IPAddress* ipaddress, int port);

			bool Start();
			bool Start(int backlog);
			bool Stop();
			SimpleTcpClient* AcceptTcpClient();
			SOCKET AcceptSocket();
			void AcceptSocket(std::string &ip, SOCKET &sock);
			IPEndPoint* GetEndPoint() const;
			void SetEndPoint(IPEndPoint* endpoint);
			SOCKET GetSocket() const;
		private:
			bool Init();
			bool Close();
		private:
			SOCKET m_sock = INVALID_SOCKET;
			IPEndPoint* m_endpoint;
		};
	}
}

#endif // !SYSTEM_NET_SIMPLETCPCLITENER_H
