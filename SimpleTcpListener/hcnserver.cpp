///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#define FD_SETSIZE      4096
#include "System/HCN/TcpListenerChannel.h"
#include "System/HCN/SelectTcpListenerChannel.h"
#include "System/Threading/Thread.h"
#include "System/Net/TcpClient.h"
#include "System/Net/Sockets/Socket.h"
#include "System/DateTimes/DateTime.h"
#include "System/Logger/CLogger.h"
#include "System/HCN/TcpStartEventArgs.h"
#include "System/HCN/TcpOnLineEventArgs.h"
#include "System/HCN/TcpOffLineEventArgs.h"
#include "System/HCN/TcpReceiveEventArgs.h"

using namespace System::HCN;
using namespace System::Logger;
using namespace System::DateTimes;

int64_t g_time = GetTimestamp();
std::atomic<int> g_clients = 0;
std::atomic<int> g_receive_msgs = 0;
std::atomic<int> g_send_msgs = 0;
TcpListenerChannelPtr g_server = nullptr;
ThreadPtr g_proc_thread;

void ProcMsg()
{
	g_server->ConsumeRead();
	Thread::SleepMs(1);
}

void Start(const TcpStartEventArgs& e)
{
	printf("start <port: %d><threads: %d>\n", e.GetPort(), e.GetThreads());
	g_proc_thread = std::make_shared<Thread>(std::bind(ProcMsg));
	g_proc_thread->Start();
}

void Stop(const TcpStopEventArgs& e)
{
	printf("stop\n");
}

void OnLine(const TcpOnLineEventArgs& e)
{
	g_clients++;
	printf("online <socket: %d><total: %lld>\n", (int)e.GetClient()->GetClient()->GetHandle(), e.GetTotalClients());
}

void OffLine(const TcpOffLineEventArgs& e)
{
	g_clients--;
	printf("offline <socket: %d><total: %lld>\n", (int)e.GetClient()->GetClient()->GetHandle(), e.GetTotalClient());
}

void SelectError(const TcpSelectErrorEventArgs& e)
{
	printf("select error\n");
}

void Receive(const TcpReceiveEventArgs& e)
{
	Msg* msg = e.GetMsg();
	delete msg;
	g_receive_msgs++;
}

void Send(const TcpSendEventArgs& e)
{
	g_send_msgs++;
}



int main(int argc, char** argv)
{
	g_server = std::make_shared<SelectTcpListenerChannel>();
	g_server->Started = std::bind(Start, std::placeholders::_1);
	g_server->Stoped = std::bind(Stop, std::placeholders::_1);
	g_server->OnLine = std::bind(OnLine, std::placeholders::_1);
	g_server->OffLine = std::bind(OffLine, std::placeholders::_1);
	g_server->SelectError = std::bind(SelectError, std::placeholders::_1);
	g_server->Receive = std::bind(Receive, std::placeholders::_1);
	g_server->Send = std::bind(Send, std::placeholders::_1);
	g_server->Start(8888, 4);

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