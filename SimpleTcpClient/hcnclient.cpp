///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/HCN/TcpClientChannel.h"
#include "System/HCN/TcpConnectEventArgs.h"
#include "System/HCN/TcpSendEventArgs.h"
#include "System/HCN/TcpReceiveEventArgs.h"
#include "System/HCN/IOProcess.h"
#include "System/HCN/SelectIOProcess.h"
#include "System/HCN/Msg.h"
#include "System/HCN/Ptrs.h"
#include "System/Net/TcpClient.h"
#include "System/Net/Sockets/Socket.h"
#include "System/Logger/CLogger.h"
#include "System/DateTimes/DateTime.h"
#include "System/Memory/ObjectPool.h"
#include "System/Threading/Thread.h"
#include "System/Threading/Semaphore.h"
#include "System/Threading/Ptrs.h"
#include <vector>
using namespace System::HCN;
using namespace System::Logger;
using namespace System::Threading;
using namespace System::DateTimes;
using namespace System::Memory;

std::atomic<int> g_clients = 0;
std::atomic<int> g_send_msgs = 0;
std::atomic<int> g_receive_msgs = 0;
int64_t g_time = GetTimestamp();
SemaphorePtr g_start_sem = std::make_shared<Semaphore>(0);
SemaphorePtr g_stop_sem = std::make_shared<Semaphore>(0);

//void SendMsg()
//{
//	TestMsg msgs[10];
//	while (true)
//	{
//		for (auto client : clients)
//		{
//			client->Write((char*)&msgs, sizeof(msgs));
//		}
//	}
//}

void IOProcessStart(const IOProcessStartEventArgs& e)
{
	g_start_sem->signal();
}

void IOProcessStop(const IOProcessStopEventArgs& e)
{
	g_stop_sem->signal();
}

void OnLine(const TcpOnLineEventArgs& e)
{
	g_clients++;
}

void OffLine(const TcpOffLineEventArgs& e)
{
	g_clients--;
}

void Receive(const TcpReceiveEventArgs& e)
{
	g_receive_msgs++;
}

void Send(const TcpSendEventArgs& e)
{
	g_send_msgs += 10;
}

void SelectError(const TcpSelectErrorEventArgs& e)
{

}

int main(int args, char** argv)
{
	std::vector<IOProcessPtr> io_processor;
	for (int i = 0; i < 4; i++)
	{
		io_processor.push_back(std::make_shared<SelectIOProcess>());
		io_processor[i]->IOProcessStart = std::bind(IOProcessStart, std::placeholders::_1);
		io_processor[i]->IOProcessStop = std::bind(IOProcessStop, std::placeholders::_1);
		io_processor[i]->OnLine = std::bind(OnLine, std::placeholders::_1);
		io_processor[i]->OffLine = std::bind(OffLine, std::placeholders::_1);
		io_processor[i]->Receive = std::bind(Receive, std::placeholders::_1);
		io_processor[i]->Send = std::bind(Send, std::placeholders::_1);
		io_processor[i]->SelectError = std::bind(SelectError, std::placeholders::_1);
		io_processor[i]->Start();
	}

	for (auto p : io_processor)
	{
		g_start_sem->wait();
	}

	int idx = 0;
	for (size_t i = 0; i < 1000; i++)
	{
		TcpClientChannelPtr client = std::make_shared<TcpClientChannel>();
		client->Connect("127.0.0.1", 8888);
		io_processor[idx++]->AddClient(client);
		if (idx == 4)
		{
			idx = 0;
		}
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