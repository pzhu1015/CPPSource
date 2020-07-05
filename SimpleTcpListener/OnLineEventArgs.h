///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SIMPLETCPLISTENER_ONLINEEVENTARGS_H
#define SIMPLETCPLISTENER_ONLINEEVENTARGS_H
#include "System/EventArgs.h"

namespace System
{
	namespace Net
	{
		class TcpClient;
	}
}

class OnLineEventArgs : public System::EventArgs
{
public:
	OnLineEventArgs(System::Net::TcpClient* client);
	~OnLineEventArgs();

	System::Net::TcpClient* GetClient() const;
private:
	System::Net::TcpClient* m_client;
};
#endif // !SIMPLETCPLISTENER_ONLINEEVENTARGS_H
