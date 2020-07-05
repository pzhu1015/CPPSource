///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SIMPLETCPLISTENER_TCPSTARTEVENTARGS_H
#define SIMPLETCPLISTENER_TCPSTARTEVENTARGS_H

#include "System/EventArgs.h"

using namespace System;

class TcpStartEventArgs : public EventArgs
{
public:
	TcpStartEventArgs(int port, int threads);
	~TcpStartEventArgs();

	int GetPort() const;
	int GetThreads() const;
private:
	int m_port;
	int m_threads;
};

#endif // !SIMPLETCPLISTENER_TCPSTARTEVENTARGS_H
