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
#include "System/IDisposable.h"
#include "System/Net/Sockets/AddressFamily.h"
#include <string>

using namespace System::Net::Sockets;

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			class Socket;
			class NetworkStream;
		}
		class IPEndPoint;
		class IPAddress;
		class SYSTEM_API TcpClient: public IDisposable
		{
		public:
			TcpClient();
			TcpClient(IPEndPoint* localEP);
			TcpClient(AddressFamily family);
			TcpClient(const std::string &hostname, int port);
			virtual ~TcpClient();

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
			void Connect(IPEndPoint* remoteEP);
			void Connect(IPAddress* address, int port);
			void Connect(const std::string &ip, int port);

			NetworkStream* GetStream();

			virtual void Dispose();
		protected:
			bool GetActive() const;
			void SetActive(bool active);
		private:
			Socket* m_client;
			bool m_active;
		};
	}
}

#endif // !SYSTEM_NET_TCPCLIENT_H
