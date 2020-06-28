///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN
//#define _WINSOCK_DEPRECATED_NO_WARNINGS//消除inet_ntoa警告，也可以在属性： C/C++ -> 预处理器 -> 预处理器定义中添加此宏定义

#include <windows.h>
#include <WinSock2.h>
#include <stdio.h>

//#pragma comment(lib, "ws2_32.lib") //在代码中链接库文件，也可以在工程中添加附加依赖项

enum CMD
{
	CMD_LOGIN,
	CMD_LOGOUT
};

struct DataHeader
{
	int dataLength;
	short cmd;
};

struct Login
{
	char userName[32];
	char passWord[32];
};

struct LoginResult
{
	int result;
};

struct Logout
{
	char userName[32];
};

struct LogoutResult
{
	int result;
};

struct DataPackage
{
	int age;
	char name[32];
};

int main()
{
	//启动Windows socket 2.x环境
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	//用Socket API建立简易Tcp服务端
	//1. 建立一个Socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == _sock)
	{
		printf("错误，建立套接字失败...\n");
	}
	else
	{
		printf("建立套接字成功...\n");
	}

	//2. bind绑定用于接受客户端连接的网络端口
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;// inet_addr("127.0.0.1");
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin)))
	{
		printf("错误, 绑定网络端口失败...\n");
	}
	else
	{
		printf("绑定网络端口成功[%d]...\n", 4567);
	}

	//3. listen 监听网络端口
	if (SOCKET_ERROR == listen(_sock, 5))
	{
		printf("错误,监听网络端口失败...\n");
	}
	else
	{
		printf("监听网络端口成功[%d]...\n", 4567);
	}

	//4. accept 等待接受客户端连接
	sockaddr_in clientAddr = {};
	int addr_len = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;

	while (true)
	{
		_cSock = accept(_sock, (sockaddr*)&clientAddr, &addr_len);
		if (INVALID_SOCKET == _cSock)
		{
			printf("错误,接受到无效客户端SOCKET...\n");
		}
		printf("新客户端加入: Sock=%d, IP = %s \n", (int)_cSock, inet_ntoa(clientAddr.sin_addr));
		char _recvBuf[128] = {};
		while (true)
		{
			//5. 接收客户端数据
			int nLen = recv(_cSock, _recvBuf, 128, 0);
			if (nLen <= 0)
			{
				printf("客户端已退出， 任务结束");
				break;
			}
			printf("接收到命令: %s\n", _recvBuf);
			//6. 处理请求
			if (0 == strcmp(_recvBuf, "getInfo"))
			{
				DataPackage dp = {80, "张国荣"};
				send(_cSock, (const char*)&dp, (int)sizeof(DataPackage), 0);
			}
			else
			{
				//7. send 向客户端发送一条数据
				char msgBuf[] = "???.";
				send(_cSock, msgBuf, (int)(strlen(msgBuf) + 1), 0);
			}
		}
	}

	//6. closesocket 关闭套节字
	closesocket(_cSock);

	//清除windows socket环境
	WSACleanup();
	return 0;
}

