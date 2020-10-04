///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_TCPSTARTEVENTARGS_H
#define SYSTEM_HCN_TCPSTARTEVENTARGS_H
#include "System/Base/EventArgs.h"

namespace System
{
	namespace HCN
	{
		class SYSTEM_API TcpStartEventArgs final : public EventArgs
		{
		public:
			TcpStartEventArgs(int port, int threads);
			virtual ~TcpStartEventArgs();

			int GetPort() const;
			int GetThreads() const;
		private:
			int m_port;
			int m_threads;
		};
	}
}
#endif // !SYSTEM_HCN_TCPSTARTEVENTARGS_H
