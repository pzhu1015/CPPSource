///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_TCPACCEPTEVENTARGS_H
#define SYSTEM_HCN_TCPACCEPTEVENTARGS_H
#include "System/EventArgs.h"
#include "System/Net/Ptrs.h"

using namespace System::Net;
namespace System
{
	namespace HCN
	{
		class TcpAcceptEventArgs : public EventArgs
		{
		public:
			TcpAcceptEventArgs(const TcpClientPtr &client);
			virtual ~TcpAcceptEventArgs();

			TcpClientPtr GetClient() const;
		private:
			TcpClientPtr m_client;
		};
	}
}

#endif // !SIMPLETCPLISTENER_TCPACCEPTEVENTARGS_H
