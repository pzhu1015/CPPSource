///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Redis/RedisMgr.h"
#include "System/Applications/Application.h"
#include "System/Configurations/Configuration.h"
#include "System/Redis/RedisConnection.h"
#include "System/DateTimes/DateTime.h"
#include "System/IO/File.h"
#include "System/Threading/Thread.h"
#include "System/Threading/Semaphore.h"
#include <assert.h>
#include <iostream>
using namespace System;
using namespace System::Redis;
using namespace System::IO;
using namespace System::DateTimes;
int main(int argc, char** argv)
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	Application::GetInstance().Start("config.ini");
	auto config = Application::GetInstance().GetConfiguration();
	auto host = config->GetValue("redis", "host", "127.0.0.1");
	auto port = config->GetValue("redis", "port", 6379);
	auto database = config->GetValue("redis", "database", 0);
	auto password = config->GetValue("redis", "password", "12345");

	auto sem = std::make_shared<Semaphore>();
	std::vector<RedisConnectionPtr> connections;
	for (int i=0; i < 4; i++)
	{
		auto connection = std::make_shared<RedisConnection>(host, port, password, database);
		connection->Open();
		connections.push_back(connection);
	}
	auto mobiles = File::ReadAllLines("E:\\mobiles.txt");
	__int64 t1 = GetTimestamp();
	for (int i=0; i < connections.size(); i++)
	{
		auto thread = std::make_shared<Thread>([&]() 
		{
			for (auto mobile : mobiles)
			{
				bool exist = connections[i]->SIsMember("mobiles", mobile);
				assert(exist);
			}
			sem->signal();
		});
		thread->Start();
	}
	for (int i = 0; i < connections.size(); i++)
	{
		sem->wait();
	}
	__int64 t2 = GetTimestamp();
	double cost = (t2 - t1) / 1000.0;
	double speed = mobiles.size() * connections.size() / (cost / 1000.0);
	std::cout << "cost: " << cost << "ms, speed: " << speed << "Ìõ/s" << std::endl;
	while (true)
	{
		bool connected = connections[0]->Ping();
		std::cout << (connected ? "connected" : "disconnected") << std::endl;
		Thread::Sleep(1);
	}
	WSACleanup();
	return 1;
}