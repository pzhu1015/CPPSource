///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_TCPONLINEEVENTARGS_H
#define SYSTEM_HCN_TCPONLINEEVENTARGS_H
#include "System/EventArgs.h"
#include "System/Net/Ptrs.h"

using namespace System::Net;
namespace System
{
	namespace HCN
	{
		class SYSTEM_API TcpOnLineEventArgs final : public EventArgs
		{
		public:
			TcpOnLineEventArgs(const TcpClientPtr &client, size_t total_clients);
			virtual ~TcpOnLineEventArgs();

			TcpClientPtr GetClient() const;
			size_t GetTotalClients() const;
		private:
			TcpClientPtr m_client = nullptr;
			size_t m_total_clients = 0;
		};
	}
}
#endif // !SYSTEM_HCN_ONLINEEVENTARGS_H
