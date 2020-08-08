///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_TCPSENDEVENTARGS_H
#define SYSTEM_HCN_TCPSENDEVENTARGS_H
#include "System/EventArgs.h"

namespace System
{
	namespace HCN
	{
		class SYSTEM_API TcpSendEventArgs final : public EventArgs
		{
		public:
			TcpSendEventArgs() {}
			virtual ~TcpSendEventArgs() {}
		};
	}
}
#endif // !SIMPLETCPLISTENER_TCPSENDEVENTARGS_H
