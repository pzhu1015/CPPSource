///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_ONLINEEVENTARGS_H
#define SYSTEM_HCN_ONLINEEVENTARGS_H
#include "System/EventArgs.h"
#include "System/Net/Ptrs.h"

using namespace System::Net;
namespace System
{
	namespace HCN
	{
		class OnLineEventArgs : public EventArgs
		{
		public:
			OnLineEventArgs(const TcpClientPtr &client);
			virtual ~OnLineEventArgs();

			TcpClientPtr GetClient() const;
		private:
			TcpClientPtr m_client;
		};
	}
}
#endif // !SYSTEM_HCN_ONLINEEVENTARGS_H