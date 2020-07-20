///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_SELECTTCPCLIENT_H
#define SYSTEM_HCN_SELECTTCPCLIENT_H
#include "System/DllExport.h"
#include "System/Net/Ptrs.h"
#include "System/HCN/Events.h"
using namespace System::Net;
namespace System
{
	namespace HCN
	{
		
		class SYSTEM_API SelectTcpClient
		{
		public:
			SelectTcpClient(const TcpClientPtr& client);
			~SelectTcpClient();

			bool Read();

			TcpClientPtr GetClient() const;
		protected:
			virtual void OnReceive(TcpReceiveEventArgs& e);
			virtual void OnSend(TcpSendEventArgs& e);
		public:
			TcpReceiveEventHandler Receive;
			TcpSendEventHandler Send;
		private:
			static const int BUFF_SIZE = 10240 * 5;
			TcpClientPtr m_client = nullptr;
			char* m_buff = new char[BUFF_SIZE];
			int m_read_pos = 0;
		};
	}
}
#endif // !SYSTEM_HCN_SELECTTCPCLIENT_H
