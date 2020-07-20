///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_TCPRECEIVEEVENTARGS_H
#define SYSTEM_HCN_TCPRECEIVEEVENTARGS_H
#include "System/EventArgs.h"
#include "System/Net/Ptrs.h"
#include "System/HCN/Msg.h"
using namespace System::Net;
namespace System
{
	namespace HCN
	{
		class SYSTEM_API TcpReceiveEventArgs : public EventArgs
		{
		public:
			TcpReceiveEventArgs(const TcpClientPtr &client, Msg* msg);
			virtual ~TcpReceiveEventArgs();
		private:
			TcpClientPtr m_client = nullptr;
			Msg* m_msg = nullptr;
		};
	}
}
#endif // !SYSTEM_HCN_TCPRECEIVEEVENTARGS_H
