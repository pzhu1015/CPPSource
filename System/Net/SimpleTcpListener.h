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
#include "System/Net/Sockets/SocketInclude.h"
#include "System/Net/Ptrs.h"

#include <string>

namespace System
{
	namespace Net
	{
		class SYSTEM_API SimpleTcpListener
		{
		public:
			SimpleTcpListener();
			SimpleTcpListener(const IPEndPointPtr &endpoint);
			SimpleTcpListener(int port);
			SimpleTcpListener(const IPAddressPtr &ipaddress, int port);

			bool Start();
			bool Start(int backlog);
			bool Stop();
			SimpleTcpClientPtr AcceptTcpClient();
			SOCKET AcceptSocket();
			void AcceptSocket(std::string &ip, SOCKET &sock);
			IPEndPointPtr GetEndPoint() const;
			void SetEndPoint(const IPEndPointPtr &endpoint);
			SOCKET GetSocket() const;
		private:
			bool Init();
			bool Close();
		private:
			SOCKET m_sock = INVALID_SOCKET;
			IPEndPointPtr m_endpoint;
		};
	}
}

#endif // !SYSTEM_NET_SIMPLETCPCLITENER_H
