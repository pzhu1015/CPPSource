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
#include "System/Logger/CLogger.h"
#include "System/HCN/TcpStartEventArgs.h"
#include "System/HCN/TcpOffLineEventArgs.h"

using namespace System::HCN;
using namespace System::Logger;

void Accept(const TcpAcceptEventArgs& e)
{
	CLOG_CONSOLE_INFO("accept");
}

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
	CLOG_CONSOLE_INFO("online");
}

void OffLine(const TcpOffLineEventArgs& e)
{
	CLOG_CONSOLE_INFO("offline <socket: %d>", e.GetClient()->GetClient()->GetHandle());
}

void SelectError(const TcpSelectErrorEventArgs& e)
{
	CLOG_CONSOLE_INFO("select error");
}

void Receive(const TcpReceiveEventArgs& e)
{
	CLOG_CONSOLE_INFO("receive");
}

void Send(const TcpSendEventArgs& e)
{
	CLOG_CONSOLE_INFO("send");
}

int main(int argc, char** argv)
{
	SelectTcpListenerPtr server = std::make_shared<SelectTcpListener>();
	server->Accepted = std::bind(Accept, std::placeholders::_1);
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
		System::Threading::Thread::Sleep(1);
	}
	return 0;
}