///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#define FD_SETSIZE      4096
#include "System/HCN/SelectTcpListener.h"
#include "System/Threading/Thread.h"
#include "System/Net/TcpClient.h"
#include "System/Net/Sockets/Socket.h"
#include "System/DateTimes/DateTime.h"
#include "System/Logger/CLogger.h"
#include "System/HCN/TcpStartEventArgs.h"
#include "System/HCN/TcpOnLineEventArgs.h"
#include "System/HCN/TcpOffLineEventArgs.h"

using namespace System::HCN;
using namespace System::Logger;
using namespace System::DateTimes;

int64_t g_time = GetTimestamp();
std::atomic<int> g_clients = 0;
std::atomic<int> g_receive_msgs = 0;
std::atomic<int> g_send_msgs = 0;

void Start(const TcpStartEventArgs& e)
{
	CLOG_CONSOLE_INFO("start <port: %d><threads: %d>", e.GetPort(), e.GetThreads());
}

void Stop(const TcpStopEventArgs& e)
{
	CLOG_CONSOLE_INFO("stop");
}

void OnLine(const TcpOnLineEventArgs& e)
{
	g_clients++;
	CLOG_CONSOLE_INFO("online <socket: %d><total: %d>", e.GetClient()->GetClient()->GetHandle(), e.GetTotalClients());
}

void OffLine(const TcpOffLineEventArgs& e)
{
	g_clients--;
	CLOG_CONSOLE_INFO("offline <socket: %d><total: %d>", e.GetClient()->GetClient()->GetHandle(), e.GetTotalClient());
}

void SelectError(const TcpSelectErrorEventArgs& e)
{
	CLOG_CONSOLE_INFO("select error");
}

void Receive(const TcpReceiveEventArgs& e)
{
	g_receive_msgs++;
	//CLOG_CONSOLE_INFO("receive");
}

void Send(const TcpSendEventArgs& e)
{
	g_send_msgs++;
	CLOG_CONSOLE_INFO("send");
}

int main(int argc, char** argv)
{
	SelectTcpListenerPtr server = std::make_shared<SelectTcpListener>();
	server->Started = std::bind(Start, std::placeholders::_1);
	server->Stoped = std::bind(Stop, std::placeholders::_1);
	server->OnLine = std::bind(OnLine, std::placeholders::_1);
	server->OffLine = std::bind(OffLine, std::placeholders::_1);
	server->SelectError = std::bind(SelectError, std::placeholders::_1);
	server->Receive = std::bind(Receive, std::placeholders::_1);
	server->Send = std::bind(Send, std::placeholders::_1);
	server->Start(8888, 4);

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
		System::Threading::Thread::Sleep(1);
	}
	return 0;
}