///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef EASYTCPCLIENT_EASYTCPCLIENT_H
#define EASYTCPCLIENT_EASYTCPCLIENT_H

#include "EasyTcpClient/MessageHeader.h"

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#include <WinSock2.h>
#else
	#include <unistd.h>
	#include <arpa/net.h>
	#include <string.h>
	#define SOCKET int
	#define INVALID_SOCKET	(SOCKET)(~0)
	#define SOCK_ERROR				(-1)
#endif


class EasyTcpClient
{
public:
	EasyTcpClient();
	virtual ~EasyTcpClient();

	void Init();

	int Connect(const char* ip, unsigned short port);

	void Close();

	bool OnRun();

	int RecveData();

	void OnNetMsg(DataHeader* header);

	int SendData(DataHeader* header);

	bool IsRun();
private:
	SOCKET m_sock;
};

#endif
