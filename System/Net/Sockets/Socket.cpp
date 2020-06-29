#include "System/Net/Sockets/Socket.h"

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			Socket::Socket(AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType)
			{
				m_address_family = addressFamily;
				m_socket_type = socketType;
				m_protocol_type = protocolType;
			}

			Socket::~Socket()
			{
				delete m_local_endpoint;
				delete m_remote_endpoint;
			}

			bool Socket::SupportIpv4()
			{
				return false;
			}

			bool Socket::SupportIpv6()
			{
				return false;
			}

			void Socket::Select(fd_set* checkRead, fd_set* checkWrite, fd_set* checkError, int microSeconds)
			{
				timeval tv = { 0, microSeconds };
				select(0, checkRead, checkWrite, checkError, &tv);
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
				return SOCKET();
			}

			AddressFamily Socket::GetAddressFamily() const
			{
				return AddressFamily();
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
				return nullptr;
			}

			bool Socket::AcceptAsync()
			{
				return false;
			}

			void Socket::Bind(EndPoint * endpoint)
			{
			}

			void Socket::Close()
			{
			}

			void Socket::Close(int timeout)
			{
			}

			void Socket::Connect(EndPoint * remoteEP)
			{
			}

			void Socket::Connect(IPAddress * address, int port)
			{
			}

			void Socket::Connect(const std::string & ip, int port)
			{
			}

			bool Socket::ConnectAsync()
			{
				return false;
			}

			void Socket::Disconnect(bool reuseSocket)
			{
			}

			bool Socket::DisconnectAsync()
			{
				return false;
			}

			void Socket::Listen(int backlog)
			{
			}

			bool Socket::Poll(int microSeconds, SelectMode selectMode)
			{
				return false;
			}

			int Socket::Receive(char * buffer, int length)
			{
				return 0;
			}

			bool Socket::ReceiveAsync()
			{
				return false;
			}

			int Socket::Send(char * buffer, int length)
			{
				return 0;
			}

			bool Socket::SendAsync()
			{
				return false;
			}

			int Socket::ReceiveFrom(char * buffer, int length, EndPoint * remoteEP)
			{
				return 0;
			}

			bool Socket::ReceiveFromAsync()
			{
				return false;
			}

			int Socket::SendTo(char * buffer, int length, EndPoint * remoteEP)
			{
				return 0;
			}

			void Socket::SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, const char * optValue, int optLength)
			{
			}

			void Socket::SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, int optValue)
			{
			}

			void Socket::SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName, bool optValue)
			{
			}
		}
	}
}
