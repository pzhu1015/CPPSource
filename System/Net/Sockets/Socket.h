///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_SOCKET_H
#define SYSTEM_NET_SOCKET_H

#include "System/DllExport.h"
#include "System/IDisposable.h"
#include "System/Net/Sockets/AddressFamily.h"
#include "System/Net/Sockets/ProtocolType.h"
#include "System/Net/Sockets/SocketType.h"
#include "System/Net/Sockets/SelectMode.h"
#include "System/Net/Sockets/SocketOptionLevel.h"
#include "System/Net/Sockets/SocketOptionName.h"
#include "System/Net/Sockets/SocketAsyncEventArgs.h"
#include "System/Net/EndPoint.h"
#include "System/Net/IPAddress.h"

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			class SocketAsyncEventArgs;
			class SYSTEM_API Socket : public IDisposable
			{
			public:
				Socket(SOCKET sock, AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType);
				Socket(AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType);
				~Socket();

				static bool SupportIpv4();
				static bool SupportIpv6();
				static void Select(fd_set* checkRead, fd_set* checkWrite, fd_set* checkError, int microSeconds);

				bool GetBlocking() const;
				void SetBlocking(bool blocking);
				bool GetConnected() const;
				int GetReceiveTimeout() const;
				void SetReceiveTimeout(int timeout);
				int GetSendTimeout() const;
				void SetSendTimeout(int timeout);
				int GetReceiveBuffSize() const;
				void SetReceiveBuffSize(int size);
				int GetSendBuffSize() const;
				void SetSendBuffSize(int size);
				int GetAvailable() const;
				SOCKET GetHandle() const;
				AddressFamily GetAddressFamily() const;
				EndPoint* GetLocalEndPoint() const;
				EndPoint* GetRemoteEndPoint() const;
				ProtocolType GetProtocolType() const;
				SocketType GetSocketType() const;

				Socket* Accept();
				bool AcceptAsync(SocketAsyncEventArgs* e);
				bool Bind(EndPoint* endpoint);
				bool Close();
				bool Close(int timeout);
				bool Connect(EndPoint* remoteEP);
				bool Connect(IPAddress* address, int port);
				bool Connect(const std::string &ip, int port);
				bool ConnectAsync(SocketAsyncEventArgs* e);
				void Disconnect(bool reuseSocket);
				bool DisconnectAsync(SocketAsyncEventArgs* e);
				bool Listen(int backlog);
				bool Poll(int microSeconds, SelectMode selectMode);

				//for tcp
				int Receive(char* buffer, int length);
				bool ReceiveAsync(SocketAsyncEventArgs* e);
				int Send(char* buffer, int length);
				bool SendAsync(SocketAsyncEventArgs* e);

				//for udp
				int ReceiveFrom(char* buffer, int length, EndPoint* remoteEP);
				bool ReceiveFromAsync(SocketAsyncEventArgs* e);
				int SendTo(char* buffer, int length, EndPoint* remoteEP);
				bool SendToAsync(SocketAsyncEventArgs* e);

				int SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, const char* optValue, int optLength);
				void SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, int optValue);
				void SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, bool optValue);

				virtual void Dispose() override;

			private:
				bool m_blocking;
				bool m_connected;
				int m_receive_timeout;
				int m_send_timeout;
				int m_receive_buffsize;
				int m_send_buffsize;
				AddressFamily m_address_family;
				EndPoint* m_local_endpoint;
				EndPoint* m_remote_endpoint;
				ProtocolType m_protocol_type;
				SocketType m_socket_type;
				SOCKET m_sock;

			};
		}
	}
}
#endif // !SYSTEM_NET_SOCKET_H
