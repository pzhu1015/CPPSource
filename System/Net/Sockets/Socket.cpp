///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Net/Sockets/Socket.h"
#include "System/Net/EndPoint.h"
#include "System/Net/IPEndPoint.h"
#include "System/Net/IPAddress.h"
#include "System/Net/Sockets/SocketAsyncEventArgs.h"
#include "System/Threading/Thread.h"
#include "System/ArgumentException.h"
#include "System/ArgumentNullException.h"
#include "System/InvalidOperationException.h"
#include "System/ArgumentOutOfRangeException.h"
#include "System/NotSupportedException.h"
#include <assert.h>

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			Socket::Socket(SOCKET accecpedSocket)
			{
				if (INVALID_SOCKET == accecpedSocket)
				{
					throw ArgumentException("accecpedSocket");
				}
				m_address_family = AddressFamily::Unknown;
				m_socket_type = SocketType::Unknown;
				m_protocol_type = ProtocolType::Unknown;
				m_sock = accecpedSocket;
			}

			Socket::Socket(AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType)
			{
				m_address_family = addressFamily;
				m_socket_type = socketType;
				m_protocol_type = protocolType;
#ifdef _WIN32
				WORD ver = MAKEWORD(2, 2);
				WSADATA dat;
				WSAStartup(ver, &dat);
#endif
				m_sock = socket((int)m_address_family, m_socket_type, (int)m_protocol_type);
			}

			Socket::~Socket()
			{
				Close();
			}

			bool Socket::SupportIpv4()
			{
				return false;
			}

			bool Socket::SupportIpv6()
			{
				return false;
			}

			bool Socket::GetBlocking() const
			{
				return m_blocking;
			}

			void Socket::SetBlocking(bool blocking)
			{
				m_blocking = blocking;
#ifdef _WIN32
				int iMode = (int)!m_blocking;
				int ret = ioctlsocket(m_sock, FIONBIO, (u_long FAR*)&iMode);
#else
				ioctl(sockfd, FIONBIO, (int)blocking);
#endif 	
			}

			bool Socket::GetConnected() const
			{
				return m_connected;
			}

			int Socket::GetReceiveTimeout() const
			{
				return GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReceiveTimeout);
			}

			void Socket::SetReceiveTimeout(int timeout)
			{
				SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReceiveTimeout, timeout);
			}

			int Socket::GetSendTimeout() const
			{
				return GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::SendTimeout);
			}

			void Socket::SetSendTimeout(int timeout)
			{
				SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::SendTimeout, timeout);
			}

			int Socket::GetReceiveBuffSize() const
			{
				return GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReceiveBuffer);
			}

			void Socket::SetReceiveBuffSize(int size)
			{
				SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::ReceiveBuffer, size);
			}

			int Socket::GetSendBuffSize() const
			{
				return GetSocketOption(SocketOptionLevel::Socket, SocketOptionName::SendBuffer);
			}

			void Socket::SetSendBuffSize(int size)
			{
				SetSocketOption(SocketOptionLevel::Socket, SocketOptionName::SendBuffer, size);
			}

			int Socket::GetAvailable() const
			{
				return 0;
			}

			SOCKET Socket::GetHandle() const
			{
				return m_sock;
			}

			AddressFamily Socket::GetAddressFamily() const
			{
				return m_address_family;
			}

			EndPointPtr Socket::GetLocalEndPoint() const
			{
				return m_local_endpoint;
			}

			EndPointPtr Socket::GetRemoteEndPoint() const
			{
				return m_remote_endpoint;
			}

			ProtocolType Socket::GetProtocolType() const
			{
				return m_protocol_type;
			}

			SocketType Socket::GetSocketType() const
			{
				return m_socket_type;
			}

			SocketPtr Socket::Accept()
			{
				sockaddr_in client_addr = {};
				int len = sizeof(sockaddr_in);
				SOCKET sock = INVALID_SOCKET;
#ifdef _WIN32
				sock = accept(m_sock, (sockaddr*)&client_addr, &len);
#else
				sock = accept(m_sock, (sockaddr*)&client_addr, (socket_t*)&len);
#endif
				if (INVALID_SOCKET == sock)
				{
					return nullptr;
				}
				std::string ip = inet_ntoa(client_addr.sin_addr);
				int port = ntohs(client_addr.sin_port);
				SocketPtr socket = std::make_shared<Socket>(sock);
				socket->m_remote_endpoint = std::make_shared<IPEndPoint>(std::make_shared<IPAddress>(ip), port);
				return socket;
			}

			bool Socket::AcceptAsync(const SocketAsyncEventArgsPtr &e)
			{
				return false;
			}

			bool Socket::Bind(const EndPointPtr &endpoint)
			{
				if (endpoint == nullptr)
				{
					throw ArgumentNullException("endpoint");
				}
				if (INVALID_SOCKET == m_sock)
				{
					return false;
				}
				IPEndPointPtr ipendpoint = std::dynamic_pointer_cast<IPEndPoint>(endpoint);
				if (ipendpoint == nullptr)
				{
					return false;
				}
				IPAddressPtr ipaddress = ipendpoint->GetIPAddress();
				if (ipaddress == nullptr)
				{
					return false;
				}
				std::string ip = ipaddress->GetIPAddress();
				int port = ipendpoint->GetPort();
				sockaddr_in _sin = {};
				_sin.sin_family = (int)m_address_family;
				_sin.sin_port = htons(port);
#ifdef _WIN32
				if (strcmp(ip.c_str(), "") == 0)
				{
					_sin.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
				}
				else
				{
					_sin.sin_addr.S_un.S_addr = INADDR_ANY;
				}
#else
				if (strcmp(ip, "") == 0)
				{
					_sin.sin_addr.s_addr = inet_addr(ip);
				}
				else
				{
					_sin.sin_addr.s_addr = INADDR_ANY;
				}
#endif

				int ret = bind(m_sock, (sockaddr*)&_sin, sizeof(_sin));
				if (SOCKET_ERROR == ret)
				{
					return false;
				}
				return true;
			}

			bool Socket::Close()
			{
				if (INVALID_SOCKET == m_sock)
				{
					return true;
				}
#ifdef _WIN32
				closesocket(m_sock);
#else
				close(m_sock);
#endif
				if (m_connected)
				{
					m_sock = INVALID_SOCKET;
					m_connected = false;
				}
				return true;
			}

			bool Socket::Close(int timeout)
			{
				System::Threading::SleepMs(timeout);
				return Close();
			}

			bool Socket::Connect(const EndPointPtr &remoteEP)
			{
				if (remoteEP == nullptr)
				{
					throw ArgumentNullException("remoteEP");
				}

				if (m_connected)
				{
					throw InvalidOperationException("socket is connected");
				}

				IPEndPointPtr ipendpoint = std::dynamic_pointer_cast<IPEndPoint>(remoteEP);
				if (remoteEP == nullptr)
				{
					return false;
				}
				return Connect(ipendpoint->GetIPAddress(), ipendpoint->GetPort());
			}

			bool Socket::Connect(const IPAddressPtr &address, int port)
			{
				if (address == nullptr)
				{
					throw ArgumentNullException("address");
				}
				if (port > IPEndPoint::MAXPORT || port < IPEndPoint::MINPORT)
				{
					throw ArgumentOutOfRangeException("port");
				}
				return Connect(address->GetIPAddress(), port);
			}

			bool Socket::Connect(const std::string & ip, int port)
			{
				if (ip == "")
				{
					throw ArgumentNullException("ip");
				}
				if (port > IPEndPoint::MAXPORT || port < IPEndPoint::MINPORT)
				{
					throw ArgumentOutOfRangeException("port");
				}
				if (m_address_family != AddressFamily::InterNetwork)
				{
					throw NotSupportedException("invalid address family");
				}
				if (m_connected)
				{
					throw InvalidOperationException("socket is connected");
				}
				assert(INVALID_SOCKET != m_sock);
				assert(port <= IPEndPoint::MAXPORT && port > IPEndPoint::MINPORT);
				assert(ip != "");
				assert(!m_connected);
				sockaddr_in sin = {};
				sin.sin_family = (int)m_address_family;
				sin.sin_port = htons(port);
#ifdef _WIN32
				sin.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
#else
				sin.sin_addr.s_addr = inet_addr(ip);
#endif
				int ret = connect(m_sock, (sockaddr*)&sin, sizeof(sockaddr_in));
				if (SOCKET_ERROR == ret)
				{
					return false;
				}
				m_connected = true;
				return true;
			}

			bool Socket::ConnectAsync(const SocketAsyncEventArgsPtr &e)
			{
				return false;
			}

			void Socket::Disconnect(bool reuseSocket)
			{
			}

			bool Socket::DisconnectAsync(const SocketAsyncEventArgsPtr &e)
			{
				return false;
			}

			bool Socket::Listen(int backlog)
			{
				if (INVALID_SOCKET == m_sock)
				{
					return false;
				}
				int ret = listen(m_sock, backlog);
				if (SOCKET_ERROR == ret)
				{
					return false;
				}
				return true;
			}

			bool Socket::Poll(int microSeconds, SelectMode selectMode)
			{
				return false;
			}

			int Socket::Receive(char * buffer, int length)
			{
				assert(INVALID_SOCKET != m_sock);
				if (INVALID_SOCKET == m_sock)
				{
					return -1;
				}
				int ret = recv(m_sock, buffer, length, 0);
				return ret;
			}

			bool Socket::ReceiveAsync(const SocketAsyncEventArgsPtr &e)
			{
				return false;
			}

			int Socket::Send(char * buffer, int length)
			{
				assert(INVALID_SOCKET != m_sock);
				if (INVALID_SOCKET == m_sock)
				{
					return -1;
				}
				int ret = send(m_sock, buffer, length, 0);
				return ret;
			}

			bool Socket::SendAsync(const SocketAsyncEventArgsPtr &e)
			{
				return false;
			}

			int Socket::ReceiveFrom(char * buffer, int length, const EndPointPtr &remoteEP)
			{
				return 0;
			}

			bool Socket::ReceiveFromAsync(const SocketAsyncEventArgsPtr &e)
			{
				return false;
			}

			int Socket::SendTo(char * buffer, int length, const EndPointPtr &remoteEP)
			{
				return 0;
			}

			bool Socket::SendToAsync(const SocketAsyncEventArgsPtr &e)
			{
				return false;
			}

			int Socket::SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, const char * optValue, int optLength)
			{
				assert(INVALID_SOCKET != m_sock);
				return setsockopt(m_sock, (int)optionLevel, (int)optionName, optValue, optLength);
			}

			void Socket::SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, int optValue)
			{
				SetSocketOption(optionLevel, optionName, (const char*)&optValue, sizeof(optValue));
			}

			void Socket::SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, bool optValue)
			{
				SetSocketOption(optionLevel, optionName, (const char*)&optValue, sizeof(optValue));
			}

			int Socket::GetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName) const
			{
				assert(INVALID_SOCKET != m_sock);
				int result = 0;
				int length = sizeof(result);
				int ret = getsockopt(m_sock, (int)optionLevel, (int)optionName, (char*)&result, &length);
				if (SOCKET_ERROR == ret)
				{
					return -1;
				}
				return result;
			}

			void Socket::Dispose()
			{
#ifdef _WIN32
				WSACleanup();
#endif
			}

			int Socket::Select(fd_set* checkRead, fd_set* checkWrite, fd_set* checkError, int microSeconds)
			{
				timeval tv = { 0, microSeconds };
#ifdef _WIN32
				return select(0, checkRead, checkWrite, checkError, &tv);
#else
				int maxfd = -1;
				if (checkRead)
				{
					for (u_int i = 0; i < checkRead->fd_count; i++)
					{
						if (maxfd < (int)checkRead->fd_array[i])
						{
							maxfd = (int)checkRead->fd_array[i];
						}
					}
				}
				if (checkWrite)
				{
					for (u_int i = 0; i < checkWrite->fd_count; i++)
					{
						if (maxfd < (int)checkWrite->fd_array[i])
						{
							maxfd = (int)checkWrite->fd_array[i];
						}
					}
				}
				if (checkError)
				{
					for (u_int i = 0; i < checkError->fd_count; i++)
					{
						if (maxfd < (int)checkError->fd_array[i])
						{
							maxfd = (int)checkError->fd_array[i];
						}
					}
				}
				return select(maxfd + 1, checkRead, checkWrite, checkError, &tv);
#endif
			}
		}
	}
}
