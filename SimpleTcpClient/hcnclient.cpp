///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/SelectTcpClient.h"
#include "System/HCN/TcpConnectEventArgs.h"
#include "System/HCN/TcpSendEventArgs.h"
#include "System/HCN/Msg.h"
#include "System/Net/TcpClient.h"
#include "System/Net/Sockets/Socket.h"
#include "System/Logger/CLogger.h"
#include "System/Threading/Thread.h"
#include "System/DateTimes/DateTime.h"
#include "System/HCN/Ptrs.h"
#include <vector>
using namespace System::HCN;
using namespace System::Logger;
using namespace System::Threading;
using namespace System::DateTimes;

std::atomic<int> g_clients = 0;
std::atomic<int> g_send_msgs = 0;
std::atomic<int> g_receive_msgs = 0;
int64_t g_time = GetTimestamp();

void Connected(const TcpConnectEventArgs& e)
{
	//CLOG_CONSOLE_INFO("connect to <socket:%d>", e.GetClient()->GetClient()->GetHandle());
	g_clients++;
}

void Send(const TcpSendEventArgs& e)
{
	//CLOG_CONSOLE_INFO("send");
	g_send_msgs += 10;
}

void SendMsg()
{
	std::vector<SelectTcpClientPtr> clients;
	for (size_t i = 0; i < 250; i++)
	{
		clients.push_back(std::make_shared<SelectTcpClient>());
		clients[i]->Connected = std::bind(Connected, std::placeholders::_1);
		clients[i]->Send = std::bind(Send, std::placeholders::_1);
		clients[i]->Connect("127.0.0.1", 8888);
	}
	Thread::Sleep(5);
	TestMsg msgs[10];
	while (true)
	{
		for (auto client : clients)
		{
			client->Write((char*)msgs, sizeof(msgs));
		}
	}
}

int main(int args, char** argv)
{
	std::vector<ThreadPtr> threads;
	for (int i = 0; i < 4; i++)
	{
		threads.push_back(std::make_shared<Thread>(std::bind(SendMsg)));
		threads[i]->Start();
	}
	while (true)
	{
		int64_t crt_t = GetTimestamp();
		double t = (crt_t - g_time)*0.000001;
		if (t > 1.0)
		{
			printf("<time=%lf><clients=%d><receives=%d><sends=%d>\n", t, (int)g_clients, (int)(g_receive_msgs / t), (int)(g_send_msgs / t));
			g_time = crt_t;
			g_receive_msgs = 0;
			g_send_msgs = 0;
		}
		Thread::Sleep(1);
	}
	return 0;
}