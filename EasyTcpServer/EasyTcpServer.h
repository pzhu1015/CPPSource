///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef EASYTCPSERVER_EASYTCPSERVER_H
#define EASYTCPSERVER_EASYTCPSERVER_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<Windows.h>
#include<WinSock2.h>
#else
#include <unistd.h>
#include <arpa/net.h>
#include <string.h>

#define SOCKET int
#define INVALID_SOCKET	(SOCKET)(~0)
#define SOCKET_ERROR			(-1)
#endif

#include "EasyTcpServer/MessageHeader.h"
#include <stdio.h>
#include <vector>


class EasyTcpServer
{
public:
	EasyTcpServer();
	~EasyTcpServer();

	//��ʼ��Socket
	SOCKET Init();
	//�󶨶˿ں�
	int Bind(const char* ip, unsigned int port);
	//�����˿ں�
	int Listen(int n);
	//���տͻ�������
	SOCKET Accept();
	//�ر�Socket
	void Close();
	//����������Ϣ
	bool OnRun();
	//�Ƿ�����
	//�������ݴ���ճ����ְ�
	//��Ӧ������Ϣ
	//��������

private:
	SOCKET m_sock;
	std::vector<SOCKET> m_clients;

};

#endif // !EASYTCPSERVER_EASYTCPSERVER_H
