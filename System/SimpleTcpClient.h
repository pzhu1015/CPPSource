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
#include "System/IPEndPoint.h"
#define MAX_SEND_BUFF_SIZE (8192);
#define MAX_RECV_BUFF_SIZE (8192);

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#else
#include <unistd.h>
#include <arpa/net.h>
#include <string.h>
#define SOCKET int
#define INVALID_SOCKET	(SOCKET)(~0)
#define SOCK_ERROR				(-1)
#endif

namespace System
{
	namespace Net
	{
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

			bool SetSendBuffSize(int buff_size);
			int GetSendBuffSize() const;

			bool SetRecvBuffSize(int buff_size);
			int GetRecvBuffSize() const;
		private:
			bool Init();

		private:
			SOCKET m_sock = INVALID_SOCKET;
			IPAddress* m_ipaddress = nullptr;
			IPEndPoint* m_endpoint = nullptr;
			bool m_connected = false;
			int m_send_buff_size = MAX_SEND_BUFF_SIZE;
			int m_recv_buff_size = MAX_RECV_BUFF_SIZE;
		};
	}
}

#endif // !SYSTEM_NET_SIMPLETCPCLIENT_H
