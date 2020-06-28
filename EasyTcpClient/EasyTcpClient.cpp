///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "EasyTcpClient/EasyTcpClient.h"
#include <stdio.h>

EasyTcpClient::EasyTcpClient()
	:
	m_sock(INVALID_SOCKET)
{
}

EasyTcpClient::~EasyTcpClient()
{
	Close();
}

void EasyTcpClient::Init()
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
		//error
	}
	else
	{
		//success
	}
}

int EasyTcpClient::Connect(const char * ip, unsigned short port)
{
	if (INVALID_SOCKET == m_sock)
	{
		Init();
	}
	sockaddr_in sin = {};
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
#ifdef _WIN32
	sin.sin_addr.S_un.S_addr = inet_addr(ip);
#else
	sin.sin_addr.s_addr = inet_addr(ip);
#endif
	int ret = connect(m_sock, (sockaddr*)&sin, sizeof(sockaddr_in));
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

void EasyTcpClient::Close()
{
	if (INVALID_SOCKET == m_sock)
	{
		return;
	}
#ifdef _WIN32
	closesocket(m_sock);
	WSACleanup();
#else
	close(m_sock);
#endif
	m_sock = INVALID_SOCKET;
}


bool EasyTcpClient::OnRun()
{
	if (INVALID_SOCKET == m_sock)
	{
		return false;
	}
	fd_set fd_reads;
	FD_ZERO(&fd_reads);
	FD_SET(m_sock, &fd_reads);
	timeval t = { 1, 0 };
	int ret = select((int)m_sock + 1, &fd_reads, 0, 0, &t);
	if (ret < 0)
	{
		printf("<socket=%d>select任务结束1\n", (int)m_sock);
		return false;
	}
	if (FD_ISSET(m_sock, &fd_reads))
	{
		FD_CLR(m_sock, &fd_reads);
		if (-1 == RecveData())
		{
			printf("<socket=%d>select任务结束2\n", (int)m_sock);
			return false;
		}
	}
	return true;
}

int EasyTcpClient::RecveData()
{
	char szRecv[4096] = {};
	int nLen = (int)recv(m_sock, szRecv, sizeof(DataHeader), 0);
	DataHeader* header = (DataHeader*)szRecv;
	if (nLen <= 0)
	{
		printf("与服务器断开连接， 任务结束\n");
		return -1;
	}
	recv(m_sock, szRecv + sizeof(DataHeader), header->dataLength - sizeof(DataHeader), 0);
	OnNetMsg(header);
	return 0;
}

void EasyTcpClient::OnNetMsg(DataHeader* header)
{
	switch (header->cmd)
	{
	case CMD_LOGIN_RESULT:
	{
		LoginResult* login = (LoginResult*)header;
		printf("收到服务端消息: CMD_LOGIN_RESULT, 数据长度: %d\n", login->dataLength);
	}
	break;
	case CMD_LOGOUT_RESULT:
	{
		LogoutResult* logout = (LogoutResult*)header;
		printf("收到服务端消息: CMD_LOGOUT_RESULT, 数据长度: %d\n", logout->dataLength);
	}
	break;
	case CMD_NEW_USER_JOIN:
	{
		NewUserJoin* userJoin = (NewUserJoin*)header;
		printf("收到服务端消息: CMD_NEW_USER_JOIN, 数据长度: %d\n", userJoin->dataLength);
	}
	break;
	}
}

int EasyTcpClient::SendData(DataHeader * header)
{
	if (INVALID_SOCKET != m_sock && header)
	{
		return send(m_sock, (const char*)header, header->dataLength, 0);
	}
	return -1;
}

bool EasyTcpClient::IsRun()
{
	return (INVALID_SOCKET != m_sock);
}
