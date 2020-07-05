///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SIMPLETCPLISTENER_OFFLINEEVENTARGS_H
#define SIMPLETCPLISTENER_OFFLINEEVENTARGS_H
#include "System/EventArgs.h"

namespace System
{
	namespace Net
	{
		class TcpClient;
	}
}

class OffLineEventArgs : public System::EventArgs
{
public:
	OffLineEventArgs(System::Net::TcpClient* client);
	~OffLineEventArgs();

	System::Net::TcpClient* GetClient() const;
private:
	System::Net::TcpClient* m_client;
};

#endif // !SIMPLETCPLISTENER_OFFLINEEVENTARGS_H
