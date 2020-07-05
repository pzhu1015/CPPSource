///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_SIMPLETCPCLIENT_H
#define SYSTEM_NET_SIMPLETCPCLIENT_H

#include "System/DllExport.h"
#include "System/Net/IPEndPoint.h"

namespace System
{
	namespace Net
	{
		class IPAddress;
		class SYSTEM_API SimpleTcpClient
		{
		public:
			SimpleTcpClient();
			~SimpleTcpClient();
			SimpleTcpClient(const std::string &ip, int port);
			SimpleTcpClient(IPEndPoint* endpoint);
			bool Connect(const std::string &ip, int port);
			bool Connect(IPEndPoint* endpoint);
			bool Connect();
			bool Close();
			bool Send(const char* data, int length);
			int Receive(char* data, int length);
			bool ReceiveAll(char* data, int length);

			void SetSocket(SOCKET sock);
			SOCKET GetSocket() const;

			void SetIPAddress(IPAddress* ipaddress);
			IPAddress* GetIPAddress() const;
			
			void SetIPEndPoint(IPEndPoint* endpoint);
			IPEndPoint* GetIPEndPoint() const;

		private:
			bool Init();

		private:
			SOCKET m_sock = INVALID_SOCKET;
			IPAddress* m_ipaddress = nullptr;
			IPEndPoint* m_endpoint = nullptr;
			bool m_connected = false;
		};
	}
}

#endif // !SYSTEM_NET_SIMPLETCPCLIENT_H
