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
		class Msg;
		class SYSTEM_API SelectTcpClient
		{
		public:
			//for client
			SelectTcpClient();
			//for server
			SelectTcpClient(const TcpClientPtr& client);
			~SelectTcpClient();

			bool Read();
			void Write(char* data, int length);
			void Connect(const std::string &ip, int port);

			TcpClientPtr GetClient() const;
		protected:
			virtual void OnReceive(const TcpReceiveEventArgs& e);
			virtual void OnSend(const TcpSendEventArgs& e);
			virtual void OnConnect(const TcpConnectEventArgs& e);
		public:
			TcpReceiveEventHandler Receive;
			TcpSendEventHandler Send;
			TcpConnectEventHandler Connected;
		private:
			static const int BUFF_SIZE = 10240 * 5;
			TcpClientPtr m_client = nullptr;
			char* m_buff = new char[BUFF_SIZE];
			int m_read_pos = 0;
		};
	}
}
#endif // !SYSTEM_HCN_SELECTTCPCLIENT_H
