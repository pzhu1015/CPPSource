///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Net/Sockets/Socket.h"
#include "System/Net/IPEndPoint.h"
#include "System/Net/IPAddress.h"
#include "System/Net/Sockets/SocketAsyncEventArgs.h"

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			Socket::Socket(SOCKET sock, AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType)
			{
				m_address_family = addressFamily;
				m_socket_type = socketType;
				m_protocol_type = protocolType;
				m_sock = sock;
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
				m_sock = socket(m_address_family, m_socket_type, m_protocol_type);
			}

			Socket::~Socket()
			{
				delete m_local_endpoint;
				delete m_remote_endpoint;
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

			int Socket::Select(fd_set* checkRead, fd_set* checkWrite, fd_set* checkError, int microSeconds)
			{
				timeval tv = { 0, microSeconds };
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
			}

			bool Socket::GetBlocking() const
			{
				return m_blocking;
			}

			void Socket::SetBlocking(bool blocking)
			{
				m_blocking = blocking;
			}

			bool Socket::GetConnected() const
			{
				return m_connected;
			}

			int Socket::GetReceiveTimeout() const
			{
				return m_receive_buffsize;
			}

			void Socket::SetReceiveTimeout(int timeout)
			{
				m_receive_timeout = timeout;
			}

			int Socket::GetSendTimeout() const
			{
				return m_send_timeout;
			}

			void Socket::SetSendTimeout(int timeout)
			{
				m_send_timeout = timeout;
			}

			int Socket::GetReceiveBuffSize() const
			{
				return m_receive_buffsize;
			}

			void Socket::SetReceiveBuffSize(int size)
			{
				m_receive_buffsize = size;
			}

			int Socket::GetSendBuffSize() const
			{
				return 0;
			}

			void Socket::SetSendBuffSize(int size)
			{
				m_send_buffsize = size;
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

			EndPoint* Socket::GetLocalEndPoint() const
			{
				return m_local_endpoint;
			}

			EndPoint* Socket::GetRemoteEndPoint() const
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

			Socket* Socket::Accept()
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
				Socket* socket = new Socket(sock, AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
				socket->m_remote_endpoint = new IPEndPoint(new IPAddress(ip), port);
				return socket;
			}

			bool Socket::AcceptAsync(SocketAsyncEventArgs* e)
			{
				return false;
			}

			bool Socket::Bind(EndPoint * endpoint)
			{
				if (INVALID_SOCKET == m_sock)
				{
					return false;
				}
				IPEndPoint* ipendpoint = dynamic_cast<IPEndPoint*>(endpoint);
				if (ipendpoint == nullptr)
				{
					return false;
				}
				IPAddress* ipaddress = ipendpoint->GetIPAddress();
				if (ipaddress == nullptr)
				{
					return false;
				}
				std::string ip = ipaddress->GetIPAddress();
				int port = ipendpoint->GetPort();
				sockaddr_in _sin = {};
				_sin.sin_family = AF_INET;
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
				return false;
			}

			bool Socket::Connect(EndPoint * remoteEP)
			{
				if (remoteEP == nullptr)
				{
					return false;
				}

				IPEndPoint* ipendpoint = dynamic_cast<IPEndPoint*>(remoteEP);
				if (remoteEP == nullptr)
				{
					return false;
				}
				return Connect(ipendpoint->GetIPAddress(), ipendpoint->GetPort());
			}

			bool Socket::Connect(IPAddress * address, int port)
			{
				if (address == nullptr || port < 0)
				{
					return false;
				}
				return Connect(address->GetIPAddress(), port);
			}

			bool Socket::Connect(const std::string & ip, int port)
			{
				if (INVALID_SOCKET == m_sock || port < 0 || ip == "")
				{
					return false;
				}

				if (m_connected)
				{
					return true;
				}
				sockaddr_in sin = {};
				sin.sin_family = AF_INET;
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

			bool Socket::ConnectAsync(SocketAsyncEventArgs* e)
			{
				return false;
			}

			void Socket::Disconnect(bool reuseSocket)
			{
			}

			bool Socket::DisconnectAsync(SocketAsyncEventArgs* e)
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
				if (INVALID_SOCKET == m_sock)
				{
					return -1;
				}
				int ret = recv(m_sock, buffer, length, 0);
				return ret;
			}

			bool Socket::ReceiveAsync(SocketAsyncEventArgs* e)
			{
				return false;
			}

			int Socket::Send(char * buffer, int length)
			{
				if (INVALID_SOCKET == m_sock)
				{
					return false;
				}
				int ret = send(m_sock, buffer, length, 0);
				return ret;
			}

			bool Socket::SendAsync(SocketAsyncEventArgs* e)
			{
				return false;
			}

			int Socket::ReceiveFrom(char * buffer, int length, EndPoint * remoteEP)
			{
				return 0;
			}

			bool Socket::ReceiveFromAsync(SocketAsyncEventArgs* e)
			{
				return false;
			}

			int Socket::SendTo(char * buffer, int length, EndPoint * remoteEP)
			{
				return 0;
			}

			bool Socket::SendToAsync(SocketAsyncEventArgs * e)
			{
				return false;
			}

			int Socket::SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, const char * optValue, int optLength)
			{
				if (INVALID_SOCKET == m_sock)
				{
					return -1;
				}
				int ret = setsockopt(m_sock, (int)optionLevel, (int)optionName, optValue, optLength);
				return ret;
			}

			void Socket::SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, int optValue)
			{
			}

			void Socket::SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, bool optValue)
			{
			}

			void Socket::Dispose()
			{
#ifdef _WIN32
				WSACleanup();
#endif
			}
		}
	}
}
