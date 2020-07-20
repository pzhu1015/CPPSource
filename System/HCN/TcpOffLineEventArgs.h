///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_TCPOFFLINEEVENTARGS_H
#define SYSTEM_HCN_TCPOFFLINEEVENTARGS_H
#include "System/EventArgs.h"
#include "System/Net/Ptrs.h"

using namespace System::Net;
namespace System
{

	namespace HCN
	{
		class SYSTEM_API TcpOffLineEventArgs : public EventArgs
		{
		public:
			TcpOffLineEventArgs(const TcpClientPtr& client);
			virtual ~TcpOffLineEventArgs();

			TcpClientPtr GetClient() const;
		private:
			TcpClientPtr m_client;
		};
	}
}

#endif // !SYSTEM_HCN_TCPOFFLINEEVENTARGS_H
