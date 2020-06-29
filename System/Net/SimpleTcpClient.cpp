#include "System/Net/SimpleTcpClient.h"

namespace System
{
	namespace Net
	{
		SimpleTcpClient::SimpleTcpClient()
		{
			
		}

		SimpleTcpClient::~SimpleTcpClient()
		{
			delete m_ipaddress;
			delete m_endpoint;
			Close();
		}

		SimpleTcpClient::SimpleTcpClient(const std::string & ip, int port)
			:
			m_ipaddress(new IPAddress(ip)),
			m_endpoint(new IPEndPoint(m_ipaddress, port))
		{
			Connect(ip, port);
		}

		SimpleTcpClient::SimpleTcpClient(IPEndPoint* endpoint)
			:
			m_ipaddress(endpoint->GetIPAddress()),
			m_endpoint(endpoint)
		{
			Connect(endpoint);
		}

		bool SimpleTcpClient::Connect(const std::string &ip, int port)
		{
			if (m_connected)
			{
				return true;
			}
			if (port < 0 || ip == "")
			{
				return false;
			}

			bool rslt = Init();
			if (!rslt)
			{
				return false;
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

		bool SimpleTcpClient::Connect(IPEndPoint* endpoint)
		{
			int port = endpoint->GetPort();
			std::string ip = endpoint->GetIPAddress()->GetIPAddress();
			return Connect(ip, port);
		}

		bool SimpleTcpClient::Connect()
		{
			return Connect(m_endpoint);
		}

		bool SimpleTcpClient::Close()
		{
			if (INVALID_SOCKET == m_sock)
			{
				return true;
			}
			#ifdef _WIN32
			closesocket(m_sock);
			if (m_connected)
			{
				WSACleanup();
			}
			#else
			close(m_sock);
			#endif
			m_sock = INVALID_SOCKET;
			m_connected = false;
			return true;
		}

		bool SimpleTcpClient::Send(const char * data, int length)
		{
			if (INVALID_SOCKET == m_sock)
			{
				return false;
			}
			int ret = send(m_sock, data, length, 0);
			if (SOCKET_ERROR == ret)
			{
				return false;
			}
			return true;
		}

		int SimpleTcpClient::Receive(char * data, int length)
		{
			int ret = recv(m_sock, data, length, 0);
			return ret;
		}

		bool SimpleTcpClient::ReceiveAll(char * data, int length)
		{
			int ret, receieved, left;
			receieved = 0;
			left = length;
			while (left > 0)
			{
				ret = Receive(data + receieved, left);
				if (SOCKET_ERROR == ret)
				{
					return false;
				}
				receieved += ret;
				left -= ret;
			}
			return true;
		}

		void SimpleTcpClient::SetSocket(SOCKET sock)
		{
			m_sock = sock;
		}

		SOCKET SimpleTcpClient::GetSocket() const
		{
			return m_sock;
		}

		IPAddress* SimpleTcpClient::GetIPAddress() const
		{
			return m_ipaddress;
		}

		void SimpleTcpClient::SetIPAddress(IPAddress* ipaddress)
		{
			m_ipaddress = ipaddress;
		}

		void SimpleTcpClient::SetIPEndPoint(IPEndPoint* endpoint)
		{
			m_endpoint = endpoint;
		}

		IPEndPoint* SimpleTcpClient::GetIPEndPoint() const
		{
			return m_endpoint;
		}

		bool SimpleTcpClient::SetSendBuffSize(int buff_size)
		{
			m_send_buff_size = buff_size;
			if (INVALID_SOCKET == m_sock)
			{
				return false;
			}
			setsockopt(m_sock, SOL_SOCKET, SO_SNDBUF, (const char*)&m_send_buff_size, sizeof(m_send_buff_size));
			return true;
		}

		int SimpleTcpClient::GetSendBuffSize() const
		{
			return m_send_buff_size;
		}

		bool SimpleTcpClient::SetRecvBuffSize(int buff_size)
		{
			m_recv_buff_size = buff_size;
			if (INVALID_SOCKET == m_sock)
			{
				return false;
			}
			setsockopt(m_sock, SOL_SOCKET, SO_RCVBUF, (const char*)&m_recv_buff_size, sizeof(m_recv_buff_size));
			return true;
		}

		int SimpleTcpClient::GetRecvBuffSize() const
		{
			return m_recv_buff_size;
		}

		bool SimpleTcpClient::Init()
		{
			#ifdef _WIN32
			WORD ver = MAKEWORD(2, 2);
			WSADATA dat;
			WSAStartup(ver, &dat);
			#endif
			if (INVALID_SOCKET != m_sock)
			{
				Close();
			}
			m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (INVALID_SOCKET == m_sock)
			{
				return false;
			}
			return true;
		}
	}
}
