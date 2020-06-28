///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN
//#define _WINSOCK_DEPRECATED_NO_WARNINGS//����inet_ntoa���棬Ҳ���������ԣ� C/C++ -> Ԥ������ -> Ԥ��������������Ӵ˺궨��

#include <windows.h>
#include <WinSock2.h>
#include <stdio.h>

//#pragma comment(lib, "ws2_32.lib") //�ڴ��������ӿ��ļ���Ҳ�����ڹ�������Ӹ���������

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
	//����Windows socket 2.x����
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	//��Socket API��������Tcp�����
	//1. ����һ��Socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == _sock)
	{
		printf("���󣬽����׽���ʧ��...\n");
	}
	else
	{
		printf("�����׽��ֳɹ�...\n");
	}

	//2. bind�����ڽ��ܿͻ������ӵ�����˿�
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;// inet_addr("127.0.0.1");
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin)))
	{
		printf("����, ������˿�ʧ��...\n");
	}
	else
	{
		printf("������˿ڳɹ�[%d]...\n", 4567);
	}

	//3. listen ��������˿�
	if (SOCKET_ERROR == listen(_sock, 5))
	{
		printf("����,��������˿�ʧ��...\n");
	}
	else
	{
		printf("��������˿ڳɹ�[%d]...\n", 4567);
	}

	//4. accept �ȴ����ܿͻ�������
	sockaddr_in clientAddr = {};
	int addr_len = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;

	while (true)
	{
		_cSock = accept(_sock, (sockaddr*)&clientAddr, &addr_len);
		if (INVALID_SOCKET == _cSock)
		{
			printf("����,���ܵ���Ч�ͻ���SOCKET...\n");
		}
		printf("�¿ͻ��˼���: Sock=%d, IP = %s \n", (int)_cSock, inet_ntoa(clientAddr.sin_addr));
		char _recvBuf[128] = {};
		while (true)
		{
			//5. ���տͻ�������
			int nLen = recv(_cSock, _recvBuf, 128, 0);
			if (nLen <= 0)
			{
				printf("�ͻ������˳��� �������");
				break;
			}
			printf("���յ�����: %s\n", _recvBuf);
			//6. ��������
			if (0 == strcmp(_recvBuf, "getInfo"))
			{
				DataPackage dp = {80, "�Ź���"};
				send(_cSock, (const char*)&dp, (int)sizeof(DataPackage), 0);
			}
			else
			{
				//7. send ��ͻ��˷���һ������
				char msgBuf[] = "???.";
				send(_cSock, msgBuf, (int)(strlen(msgBuf) + 1), 0);
			}
		}
	}

	//6. closesocket �ر��׽���
	closesocket(_cSock);

	//���windows socket����
	WSACleanup();
	return 0;
}

