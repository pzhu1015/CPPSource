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
#include <WinSock2.h>
using namespace System;
using namespace System::Redis;
int main(int argc, char** argv)
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	Application::GetInstance().Start("config.ini");
	RedisMgr::GetInstance().Start();

	
	//testing map
	RedisMgr::GetInstance().HSet("map", "a", "1");
	RedisMgr::GetInstance().HSet("map", "b", "2");
	RedisMgr::GetInstance().HSet("map", "c", "3");
	RedisMgr::GetInstance().HSet("map", "d", "4");
	RedisMgr::GetInstance().HSet("map", "e", "5");
	std::string value = RedisMgr::GetInstance().HGet("map", "e");
	int64_t length = RedisMgr::GetInstance().HLength("map");
	auto keys = RedisMgr::GetInstance().HKeys("map");
	auto values = RedisMgr::GetInstance().HValues("map");
	auto map = RedisMgr::GetInstance().HGetAll("map");

	//testing bitset, 'a' => 01100001
	bool exist = RedisMgr::GetInstance().Exist("bitset");
	if (exist)
	{
		RedisMgr::GetInstance().Delete("bitset");
		RedisMgr::GetInstance().Delete("bitset");
	}
	exist = RedisMgr::GetInstance().Exist("bitset");
	if (!exist)
	{
		RedisMgr::GetInstance().Set("bitset", "a");
	}
	std::string v = RedisMgr::GetInstance().Get("bitset");
	int64_t bit_count = RedisMgr::GetInstance().BitCount("bitset");
	int bit_value0 = RedisMgr::GetInstance().GetBit("bitset", 0);
	int bit_value1 = RedisMgr::GetInstance().GetBit("bitset", 1);
	int bit_value2 = RedisMgr::GetInstance().GetBit("bitset", 2);
	int bit_value3 = RedisMgr::GetInstance().GetBit("bitset", 3);

	int old_value6 = RedisMgr::GetInstance().SetBit("bitset", 6, 1);
	int old_value7 = RedisMgr::GetInstance().SetBit("bitset", 7, 0);

	v = RedisMgr::GetInstance().Get("bitset");
	
	//testing increment
	RedisMgr::GetInstance().HSet("user_account", "james", "0");
	int64_t balance = std::atoll(RedisMgr::GetInstance().HGet("user_account", "james").data());
	RedisMgr::GetInstance().HIncrement("user_account", "james", 10);
	balance = std::atoll(RedisMgr::GetInstance().HGet("user_account", "james").data());
	RedisMgr::GetInstance().HIncrement("user_account", "james", -20);
	balance = std::atoll(RedisMgr::GetInstance().HGet("user_account", "james").data());
	getchar();
	WSACleanup();
	return 1;
}