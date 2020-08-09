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
std::vector<IOProcessPtr> g_io_processor;
int64_t g_time = GetTimestamp();
SemaphorePtr g_startread_sem = std::make_shared<Semaphore>(0);
SemaphorePtr g_stopread_sem = std::make_shared<Semaphore>(0);
SemaphorePtr g_startwrite_sem = std::make_shared<Semaphore>(0);
SemaphorePtr g_stopwrite_sem = std::make_shared<Semaphore>(0);

void SendMsg(int idx)
{
	std::vector<TcpClientChannelPtr> channels;
	for (size_t i = 0; i < 250; i++)
	{
		TcpClientChannelPtr channel = std::make_shared<TcpClientChannel>();
		channel->Connect("127.0.0.1", 8888);
		g_io_processor[idx]->AddClient(channel);
		channels.push_back(channel);
	}
	//TODO start thread send msg
	TestMsg msg;
	while (true)
	{
		for (auto channel : channels)
		{
			channel->Write((Msg*)&msg);
		}
	}
}

void IOProcessReadStart(const IOProcessReadStartEventArgs& e)
{
	g_startread_sem->signal();
}

void IOProcessReadStop(const IOProcessReadStopEventArgs& e)
{
	g_stopread_sem->signal();
}

void IOProcessWriteStart(const IOProcessWriteStartEventArgs& e)
{
	g_startwrite_sem->signal();
}

void IOProcessWriteStop(const IOProcessWriteStopEventArgs& e)
{
	g_stopwrite_sem->signal();
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
	for (int i = 0; i < 4; i++)
	{
		g_io_processor.push_back(std::make_shared<SelectIOProcess>());
		g_io_processor[i]->IOProcessReadStart = std::bind(IOProcessReadStart, std::placeholders::_1);
		g_io_processor[i]->IOProcessReadStop = std::bind(IOProcessReadStop, std::placeholders::_1);

		g_io_processor[i]->IOProcessWriteStart = std::bind(IOProcessWriteStart, std::placeholders::_1);
		g_io_processor[i]->IOProcessWriteStop = std::bind(IOProcessWriteStop, std::placeholders::_1);

		g_io_processor[i]->OnLine = std::bind(OnLine, std::placeholders::_1);
		g_io_processor[i]->OffLine = std::bind(OffLine, std::placeholders::_1);
		g_io_processor[i]->Receive = std::bind(Receive, std::placeholders::_1);
		g_io_processor[i]->Send = std::bind(Send, std::placeholders::_1);
		g_io_processor[i]->SelectError = std::bind(SelectError, std::placeholders::_1);
		g_io_processor[i]->Start();
	}

	for (auto p : g_io_processor)
	{
		g_startread_sem->wait();
		g_startwrite_sem->wait();
	}


	std::vector<ThreadPtr> threads;
	for (int i = 0; i < 4; i++)
	{
		threads.push_back(std::make_shared<Thread>(std::bind(SendMsg, i)));
		threads[i]->Start();
	}

	for (auto p : g_io_processor)
	{
		g_stopread_sem->wait();
		g_stopwrite_sem->wait();
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