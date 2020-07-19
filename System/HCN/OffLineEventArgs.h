///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_OFFLINEEVENTARGS_H
#define SYSTEM_HCN_OFFLINEEVENTARGS_H
#include "System/EventArgs.h"

namespace System
{
	namespace Net
	{
		class TcpClient;
	}
	using namespace System::Net;
	namespace HCN
	{
		class OffLineEventArgs : public EventArgs
		{
		public:
			OffLineEventArgs(TcpClient* client);
			virtual ~OffLineEventArgs();

			TcpClient* GetClient() const;
		private:
			TcpClient* m_client;
		};
	}
}

#endif // !SYSTEM_HNC_OFFLINEEVENTARGS_H
