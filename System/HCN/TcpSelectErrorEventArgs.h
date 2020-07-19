///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_SELECTERROREVENTARGS_H
#define SYSTEM_HCN_SELECTERROREVENTARGS_H
#include "System/EventArgs.h"

namespace System
{
	namespace HCN
	{
		class TcpSelectErrorEventArgs : public EventArgs
		{
		public:
			TcpSelectErrorEventArgs();
			virtual ~TcpSelectErrorEventArgs();
		};
	}
}
#endif // !SYSTEM_HCN_SELECTERROREVENTARGS_H
