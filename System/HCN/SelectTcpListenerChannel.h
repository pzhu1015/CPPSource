///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_SELECTTCPLISTENERCHANNEL_H
#define SYSTEM_HCN_SELECTTCPLISTENERCHANNEL_H
#include "System/Base/DllExport.h"
#include "System/HCN/TcpListenerChannel.h"

namespace System
{
	namespace HCN
	{
		class SYSTEM_API SelectTcpListenerChannel final : public TcpListenerChannel
		{
		public:
			SelectTcpListenerChannel();
			virtual ~SelectTcpListenerChannel();
		protected:
			virtual IOProcessPtr GetIOProcess();
			virtual void AcceptHandle(SOCKET sock);
		};
	}
}
#endif // !SYSTEM_HCN_SELECTTCPLISTENERCHANNEL_H
