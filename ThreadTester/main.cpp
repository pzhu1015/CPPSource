///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Threading/Thread.h"
#include "System/Threading/Runnable.h"
#include "System/Logger/CLogger.h"
#include <iostream>
#include <sstream>

using namespace System;
using namespace System::Logger;
using namespace System::Threading;

class ThreadTester : public Thread
{
public:
	ThreadTester() = default;
	virtual void Run() override
	{
		Threading::Sleep(1);
		CLOG_CONSOLE_INFO("ThreadTester Run thread_id: %s", Threading::CurrentThreadStrId().data());
	}
};

class RunableTester : public Runnable
{
public:
	RunableTester() = default;
	virtual void Run()
	{
		Threading::Sleep(2);
		CLOG_CONSOLE_INFO("RunableTester Run thread_id: %s", Threading::CurrentThreadStrId().data());
	}
};

class FunctionTester
{
public:
	void Run()
	{
		Threading::Sleep(3);
		CLOG_CONSOLE_INFO("FunctionTester Run no args thread_id: %s", Threading::CurrentThreadStrId().data());
	}
	
	void Run(const char* data)
	{
		Threading::Sleep(4);
		CLOG_CONSOLE_INFO("FunctionTester with args: %s thread_id: %s", data, Threading::CurrentThreadStrId().data());
	}

	void RunArgs(const char* data)
	{
		Threading::Sleep(4);
		CLOG_CONSOLE_INFO("FunctionTester with args: %s thread_id: %s", data, Threading::CurrentThreadStrId().data());

		std::shared_ptr<Thread> t7 = std::make_shared<Thread>([]()
		{
			Threading::Sleep(3);
			CLOG_CONSOLE_INFO("Anonymous lamda expression thread start thread thread_id: %s", Threading::CurrentThreadStrId().data());
		});
		t7->Start();
	}
};

void test_thread_start()
{
	printf("thread started\n");
}

int main(int args, char** argv)
{
	//CLogger::Init();
	{
		//继承Thread
		Thread* t1 = new ThreadTester();
		t1->Start();
		CLOG_CONSOLE_INFO("main thread run here t1...");

		//实现Runnable接口
		Runnable* runnable = new RunableTester();
		std::shared_ptr<Thread> t2 = std::make_shared<Thread>(runnable);
		t2->Start();
		CLOG_CONSOLE_INFO("main thread run here t2...");

		//传递对象方法无参
		FunctionTester func;
		void(FunctionTester::*run)() = &FunctionTester::Run;
		std::shared_ptr<Thread> t3 = std::make_shared<Thread>(std::bind(run, &func));
		t3->Start();
		CLOG_CONSOLE_INFO("main thread run here t3...");

		//传递对象方法重载带参，如果是重载函数要强制转换成指定的函数签名
		void(FunctionTester::*run_with_args)(const char*) = &FunctionTester::Run;
		std::shared_ptr<Thread> t31 = std::make_shared<Thread>(std::bind(run_with_args, &func, "overload function with args"));
		t31->Start();
		CLOG_CONSOLE_INFO("main thread run here t3.1...");

		//传递对象方法有参
		std::shared_ptr<Thread> t4 = std::make_shared<Thread>(std::bind(&FunctionTester::RunArgs, &func, "Hello Args"));
		t4->Start();
		CLOG_CONSOLE_INFO("main thread run here t4...");

		//传递无参的lamda表达式
		auto fn = []()
		{
			Threading::Sleep(5);
			CLOG_CONSOLE_INFO("lamda expression thread_id: %s", Threading::CurrentThreadStrId().data());
		};
		std::shared_ptr<Thread> t5 = std::make_shared<Thread>(fn);
		t5->Start();
		CLOG_CONSOLE_INFO("main thread run here t5...");

		//传递匿名lamda表达式
		std::shared_ptr<Thread> t6 = std::make_shared<Thread>([]()
		{
			Threading::Sleep(6);
			CLOG_CONSOLE_INFO("Anonymous lamda expression thread_id: %s", Threading::CurrentThreadStrId().data());
		});
		t6->Start();
		CLOG_CONSOLE_INFO("main thread run here t6...");

		auto t8 = std::make_shared<Thread>();
		t8->Start();
	}
	
	/*{
		std::thread t1;
		std::thread t2(test_thread_start);
		printf("move before\n");
		t1 = std::move(t2);
		printf("move after\n");
		printf("join before\n");
		t1.detach();
		printf("join after\n");
	}*/
	system("pause");
	return 0;
}