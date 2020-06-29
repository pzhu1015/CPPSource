///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_TCPCLIENT_H
#define SYSTEM_NET_TCPCLIENT_H
#include "System/DllExport.h"
#include "System/Net/IPEndPoint.h"
#include "System/Net/Sockets/Socket.h"
#include "System/Net/Sockets/NetworkStream.h"

using namespace System::Net::Sockets;
namespace System
{
	namespace Net
	{
		class SYSTEM_API TcpClient
		{
		public:
			TcpClient();
			TcpClient(IPEndPoint* localEP);
			TcpClient(AddressFamily family);
			TcpClient(const std::string &hostname, int port);
			~TcpClient();

			int GetAvailable() const;
			Socket* GetClient() const;
			void SetClient(Socket* client);
			bool GetConnected() const;
			int GetReceiveBuffSize() const;
			void SetReceiveBuffSize(int size);
			int GetSendBuffSize() const;
			void SetSendBuffSize(int size);
			int GetReceiveTimeout() const;
			void SetReceiveTimeout(int timeout);
			int GetSendTimeout() const;
			void SetSendTimeout(int timeout);
			bool GetActive() const;
			void SetActive(bool active);

			void Connect(IPEndPoint* remoteEP);
			void Connect(IPAddress* address, int port);
			void Connect(const std::string &ip, int port);

			NetworkStream* GetStream();
		private:
			Socket* m_client;
			bool m_active;
		};
	}
}

#endif // !SYSTEM_NET_TCPCLIENT_H
