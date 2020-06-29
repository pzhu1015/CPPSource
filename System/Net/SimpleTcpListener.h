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
#include "System/Net/IPEndPoint.h"
#include "System/Net/SimpleTcpClient.h"
#include <memory>

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
