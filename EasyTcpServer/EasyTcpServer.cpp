#include "EasyTcpServer/EasyTcpServer.h"

EasyTcpServer::EasyTcpServer()
{
}

EasyTcpServer::~EasyTcpServer()
{
}

SOCKET EasyTcpServer::Init()
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
		printf("错误，建立socket失败...\n");
	}
	else
	{
		printf("建立socket=<%d>成功...\n", (int)m_sock);
	}
	return m_sock;
}

int EasyTcpServer::Bind(const char * ip, unsigned int port)
{
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(port);
#ifdef _WIN32
	if (strcmp(ip, "") == 0)
	{
		_sin.sin_addr.S_un.S_addr = inet_addr(ip);
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
		//error
	}
	else
	{
		//success
	}
	return ret;
}

int EasyTcpServer::Listen(int n)
{
	int ret = listen(m_sock, n);
	if (SOCKET_ERROR == ret)
	{
		//error
	}
	else
	{
		//success
	}
	return ret;
}

SOCKET EasyTcpServer::Accept()
{
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
#ifdef _WIN32
	_cSock = accept(m_sock, (sockaddr*)&clientAddr, &nAddrLen);
#else
	_cSock = accept(m_sock, (sockaddr*)&clientAddr, (socket_t*)&nAddrLen);
#endif
	if (INVALID_SOCKET == _cSock)
	{
		printf("socket=<%d>错误，接收到无效客户端SOCKET...\n", (int)m_sock);
	}
	else
	{
		for (auto client : m_clients)
		{
			NewUserJoin userJOin;
			send(client, (const char*)&userJOin, sizeof(NewUserJoin), 0);
		}
		m_clients.push_back(_cSock);
		printf("socket=<%d>新客户端加入: socket = %d, IP = %s \n", (int)m_sock, (int)_cSock, inet_ntoa(clientAddr.sin_addr));
	}
	return _cSock;
}

void EasyTcpServer::Close()
{
	if (m_sock == INVALID_SOCKET)
	{
#ifdef _WIN32
		for (auto sock : m_clients)
		{
			closesocket(sock);
		}
		WSACleanup();
#else
		for (auto sock : m_clients)
		{
			close(sock);
		}
#endif

	}
}

bool EasyTcpServer::OnRun()
{
	return false;
}
