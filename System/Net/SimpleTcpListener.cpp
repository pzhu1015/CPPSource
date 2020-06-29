#include "System/Net/SimpleTcpListener.h"
namespace System
{
	namespace Net
	{
		SimpleTcpListener::SimpleTcpListener()
		{
			Init();
		}
		SimpleTcpListener::SimpleTcpListener(IPEndPoint* endpoint)
			:
			m_endpoint(endpoint)
		{
			Init();
		}

		SimpleTcpListener::SimpleTcpListener(int port)
			:
			m_endpoint(new IPEndPoint(new IPAddress("0.0.0.0"), port))
		{
			Init();
		}

		SimpleTcpListener::SimpleTcpListener(IPAddress* ipaddress, int port)
			:
			m_endpoint(new IPEndPoint(ipaddress, port))
		{
			Init();
		}

		bool SimpleTcpListener::Start()
		{
			return Start(SOMAXCONN);
		}

		bool SimpleTcpListener::Start(int backlog)
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

		bool SimpleTcpListener::Stop()
		{
			return Close();
		}

		SOCKET SimpleTcpListener::AcceptSocket()
		{
			SOCKET sock;
			std::string ip;
			AcceptSocket(ip, sock);
			return sock;
		}

		void SimpleTcpListener::AcceptSocket(std::string & ip, SOCKET & sock)
		{
			sockaddr_in clientAddr = {};
			int nAddrLen = sizeof(sockaddr_in);
			sock = INVALID_SOCKET;
#ifdef _WIN32
			sock = accept(m_sock, (sockaddr*)&clientAddr, &nAddrLen);
#else
			sock = accept(m_sock, (sockaddr*)&clientAddr, (socket_t*)&nAddrLen);
#endif
			ip = inet_ntoa(clientAddr.sin_addr);
		}

		SimpleTcpClient* SimpleTcpListener::AcceptTcpClient()
		{
			SOCKET sock;
			std::string ip;
			AcceptSocket(ip, sock);
			SimpleTcpClient* client = new SimpleTcpClient();
			client->SetIPAddress(new IPAddress(ip));
			client->SetSocket(sock);
			return client;
		}

		IPEndPoint* SimpleTcpListener::GetEndPoint() const
		{
			return m_endpoint;
		}
		void SimpleTcpListener::SetEndPoint(IPEndPoint* endpoint)
		{
			m_endpoint = endpoint;
		}
		SOCKET SimpleTcpListener::GetSocket() const
		{
			return m_sock;
		}
		bool SimpleTcpListener::Close()
		{
			if (INVALID_SOCKET == m_sock)
			{
				return true;
			}
#ifdef _WIN32
			closesocket(m_sock);
			WSACleanup();
#else
			close(m_sock);
#endif
			m_sock = INVALID_SOCKET;
			return true;
		}
		bool SimpleTcpListener::Init()
		{

			if (INVALID_SOCKET != m_sock)
			{
				Close();
				return true;
			}
#ifdef _WIN32
			WORD ver = MAKEWORD(2, 2);
			WSADATA dat;
			WSAStartup(ver, &dat);
#endif
			m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (INVALID_SOCKET == m_sock)
			{
				return false;
			}

			IPAddress* ipaddress = m_endpoint->GetIPAddress();
			std::string ip = ipaddress->GetIPAddress();
			int port = m_endpoint->GetPort();
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
			int n = 1;
			int ret = setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&n, sizeof(int));
			if (SOCKET_ERROR == ret)
			{
				return false;
			}
			ret = bind(m_sock, (sockaddr*)&_sin, sizeof(_sin));
			if (SOCKET_ERROR == ret)
			{
				return false;
			}
			return true;
		}
	}
}
