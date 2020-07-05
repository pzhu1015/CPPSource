///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SIMPLETCPLISTENER_TCPACCEPTEVENTARGS_H
#define SIMPLETCPLISTENER_TCPACCEPTEVENTARGS_H
#include "System/EventArgs.h"

namespace System
{
	namespace Net
	{
		class TcpClient;
	}
}

class TcpAcceptEventArgs : public System::EventArgs
{
public:
	TcpAcceptEventArgs(System::Net::TcpClient* client);
	~TcpAcceptEventArgs();

	System::Net::TcpClient* GetClient() const;
private:
	System::Net::TcpClient* m_client;
};

#endif // !SIMPLETCPLISTENER_TCPACCEPTEVENTARGS_H
