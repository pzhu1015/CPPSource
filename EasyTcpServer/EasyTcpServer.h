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

	//初始化Socket
	SOCKET Init();
	//绑定端口号
	int Bind(const char* ip, unsigned int port);
	//监听端口号
	int Listen(int n);
	//接收客户端连接
	SOCKET Accept();
	//关闭Socket
	void Close();
	//处理网络消息
	bool OnRun();
	//是否工作中
	//接收数据处理粘包拆分包
	//响应网络消息
	//发送数据

private:
	SOCKET m_sock;
	std::vector<SOCKET> m_clients;

};

#endif // !EASYTCPSERVER_EASYTCPSERVER_H
