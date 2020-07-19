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
#include "System/Net/Ptrs.h"
#include "System/Net/Sockets/Ptrs.h"
#include <string>

using namespace System::Net::Sockets;

namespace System
{
	namespace Net
	{
		class SYSTEM_API TcpClient: public IDisposable
		{
		public:
			TcpClient();
			TcpClient(const IPEndPointPtr &localEP);
			TcpClient(AddressFamily family);
			TcpClient(const std::string &hostname, int port);
			TcpClient(const SocketPtr &acceptedSocket);
			virtual ~TcpClient();

			int GetAvailable() const;
			SocketPtr GetClient() const;
			void SetClient(const SocketPtr &client);
			bool GetConnected() const;
			int GetReceiveBuffSize() const;
			void SetReceiveBuffSize(int size);
			int GetSendBuffSize() const;
			void SetSendBuffSize(int size);
			int GetReceiveTimeout() const;
			void SetReceiveTimeout(int timeout);
			int GetSendTimeout() const;
			void SetSendTimeout(int timeout);
			void Connect(const IPEndPointPtr &remoteEP);
			void Connect(const IPAddressPtr &address, int port);
			void Connect(const std::string &ip, int port);

			NetworkStreamPtr GetStream();

			virtual void Dispose() override;
		protected:
			bool GetActive() const;
			void SetActive(bool active);
			virtual void Dispose(bool disposing);
		private:
			void Initialize();
		private:
			SocketPtr m_client = nullptr;
			NetworkStreamPtr m_stream = nullptr;
			AddressFamily m_family = AddressFamily::InterNetwork;
			bool m_active = false;
		};
	}
}

#endif // !SYSTEM_NET_TCPCLIENT_H
