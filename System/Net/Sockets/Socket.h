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
#include "System/Net/Ptrs.h"
#include "System/Net/Sockets/Ptrs.h"
#include <string>

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			class SYSTEM_API Socket final : public IDisposable
			{
			public:
				//for client
				Socket(SOCKET accecpedSocket);
				Socket(AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType);
				~Socket();

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
				EndPointPtr GetLocalEndPoint() const;
				EndPointPtr GetRemoteEndPoint() const;
				AddressFamily GetAddressFamily() const;
				ProtocolType GetProtocolType() const;
				SocketType GetSocketType() const;

				SocketPtr Accept();
				bool AcceptAsync(const SocketAsyncEventArgsPtr &e);
				bool Bind(const EndPointPtr &endpoint);
				bool Close();
				bool Close(int timeout);
				bool Connect(const EndPointPtr &remoteEP);
				bool Connect(const IPAddressPtr &address, int port);
				bool Connect(const std::string &ip, int port);
				bool ConnectAsync(const SocketAsyncEventArgsPtr &e);
				void Disconnect(bool reuseSocket);
				bool DisconnectAsync(const SocketAsyncEventArgsPtr &e);
				bool Listen(int backlog);
				bool Poll(int microSeconds, SelectMode selectMode);

				//for tcp
				int Receive(char* buffer, int length);
				bool ReceiveAsync(const SocketAsyncEventArgsPtr &e);
				int Send(char* buffer, int length);
				bool SendAsync(const SocketAsyncEventArgsPtr &e);

				//for udp
				int ReceiveFrom(char* buffer, int length, const EndPointPtr &remoteEP);
				bool ReceiveFromAsync(const SocketAsyncEventArgsPtr &e);
				int SendTo(char* buffer, int length, const EndPointPtr &remoteEP);
				bool SendToAsync(const SocketAsyncEventArgsPtr &e);

				int SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, const char* optValue, int optLength);
				void SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, int optValue);
				void SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, bool optValue);
				int GetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName) const;

				virtual void Dispose() override;
				static bool SupportIpv4();
				static bool SupportIpv6();
				static int Select(fd_set* checkRead, fd_set* checkWrite, fd_set* checkError, int microSeconds);

			private:
				//for server
				bool m_blocking = false;
				bool m_connected = false;
				EndPointPtr m_local_endpoint = nullptr;
				EndPointPtr m_remote_endpoint = nullptr;
				AddressFamily m_address_family;
				ProtocolType m_protocol_type;
				SocketType m_socket_type;
				SOCKET m_sock;
			};
		}
	}
}
#endif // !SYSTEM_NET_SOCKET_H
