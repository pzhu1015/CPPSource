///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SIMPLETCPLISTENER_SELECTTCPLISTENER_H
#define SIMPLETCPLISTENER_SELECTTCPLISTENER_H
#include "SimpleTcpListener/Events.h"
#include <vector>
namespace System
{
	namespace Net
	{
		class TcpListener;
		class TcpClient;
	}
	namespace Threading
	{
		class ThreadPool;
		class Thread;
	}
}
using namespace System::Net;
using namespace System::Threading;
class Process;

class SelectTcpListener
{
public:
	SelectTcpListener();
	~SelectTcpListener();

	bool Start(int port, int threads);
	bool Stop();

protected:
	virtual void OnStart(TcpStartEventArgs* e);
	virtual void OnStop(TcpStopEventArgs* e);
	virtual void OnAccept(TcpAcceptEventArgs* e);
	virtual void OnReceive(TcpReceiveEventArgs* e);
	virtual void OnSend(TcpSendEventArgs* e);
	virtual void OnSelectError(TcpSelectErrorEventArgs* e);

private:
	void AsyncStart(int port, int threads);
	void AsyncAccept(System::Net::TcpClient* client);

	void ProcessStart(ProcessStartEventArgs* e);
	void OnLine(OnLineEventArgs* e);
	void OffLine(OffLineEventArgs* e);

public:
	TcpStartEventHandler Started;
	TcpSTopEventHandler Stoped;
	TcpAccetpEventHandler Accepted;
	TcpReceiveEventHandler Received;
	TcpSendEventHandler Send;
	TcpSelectErrorEventHandler SelectError;

	ProcessStartEventHandler TcpProcessStart;
	OnLineEventHandler TcpClientOnLine;
	OffLineEventHandler TcpClientOffLine;

private:
	bool m_is_start = false;
	TcpListener* m_server = nullptr;
	std::vector<Process*> m_clients;
	ThreadPool* m_threadpool = nullptr;
	Thread* m_thread = nullptr;
};

#endif // !SIMPLETCPLISTENER_SELECTTCPLISTENER_H
