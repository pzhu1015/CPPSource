///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SIMPLETCPLISTENER_CLIENTPROCESS_H
#define SIMPLETCPLISTENER_CLIENTPROCESS_H
#include "SimpleTcpListener/Events.h"
#include "System/Net/Sockets/SocketInclude.h"
#include <unordered_map>
#include <vector>
#include <mutex>
#include <condition_variable>

namespace System
{
	namespace Threading
	{
		class Thread;
	}
	namespace Net
	{
		class TcpClient;
	}
}
using namespace System::Net;
class Process
{
public:
	Process();
	~Process();

	void Start();

	size_t GetClients() const;

	void AddClient(TcpClient* client);
protected:
	virtual void OnStart(ProcessStartEventArgs* e);
	virtual void OnOnLine(OnLineEventArgs* e);
	virtual void OnOffLine(OffLineEventArgs* e);
	virtual void OnSelectError(TcpSelectErrorEventArgs* e);

private:
	void AsyncStart();

public:
	ProcessStartEventHandler ProcessStart;
	OnLineEventHandler OnLine;
	OffLineEventHandler OffLine;
	TcpSelectErrorEventHandler SelectError;
private:
	bool m_is_start = false;
	std::mutex m_mutex;
	std::condition_variable m_cond;
	System::Threading::Thread* m_thread;
	std::vector<TcpClient*> m_tcpclients;
	std::unordered_map<SOCKET, TcpClient*> m_clients;
};

#endif // !SIMPLETCPLISTENER_CLIENTPROCESS_H
