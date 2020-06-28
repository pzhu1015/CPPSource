///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "EasyTcpClient/EasyTcpClient.h"
#include <thread>

void cmdThread(EasyTcpClient* client)
{
	while (true)
	{
		char cmdBuf[256] = {};
		scanf("%s", cmdBuf);
		if (0 == strcmp(cmdBuf, "exit"))
		{
			client->Close();
			printf("退出cmdThread线程\n");
		}
		else if (0 == strcmp(cmdBuf, "login"))
		{
			Login login;
			strcpy(login.userName, "lyd");
			strcpy(login.passWord, "lydmm");
			client->SendData(&login);
		}
		else if (0 == strcmp(cmdBuf, "logout"))
		{
			Logout logout;
			strcpy(logout.userName, "lyd");
			client->SendData(&logout);
		}
	}
}

int main()
{
	EasyTcpClient client;
	client.Connect("127.0.0.1", 4567);
	std::thread t1(cmdThread, &client);
	t1.detach();
	while (client.IsRun())
	{
		client.OnRun();
	}

	client.Close();
	printf("已退出\n");
	getchar();
	return 0;
}