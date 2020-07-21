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
#include "System/Net/TcpClient.h"
#include "System/Net/Sockets/Socket.h"
#include "System/Logger/CLogger.h"
#include "System/Threading/Thread.h"
#include "System/HCN/Ptrs.h"
#include <vector>
using namespace System::HCN;
using namespace System::Logger;
using namespace System::Threading;
std::vector<SelectTcpClientPtr> g_clients;

void Connect(const TcpConnectEventArgs& e)
{
	CLOG_CONSOLE_INFO("connect to <socket:%d>", e.GetClient()->GetClient()->GetHandle());
}

int main(int args, char** argv)
{
	for (size_t i = 0; i < 1000; i++)
	{
		g_clients.push_back(std::make_shared<SelectTcpClient>());
		g_clients[i]->Connect = std::bind(Connect, std::placeholders::_1);
		g_clients[i]->ConnectTo("127.0.0.1", 8888);
	}
	while (true)
	{
		Thread::Sleep(1);
	}
	return 0;
}