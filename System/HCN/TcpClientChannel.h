///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HCN_TCPCLIENTCHANNEL_H
#define SYSTEM_HCN_TCPCLIENTCHANNEL_H
#include "System/DllExport.h"
#include "System/Net/Ptrs.h"
#include "System/HCN/Events.h"
#include "System/HCN/Ptrs.h"

#include <vector>
#include <mutex>
using namespace System::Net;
namespace System
{
	namespace Memory
	{
		template<typename T>
		class ObjectPool;
	}
	using namespace System::Memory;
	namespace HCN
	{
		class Msg;
		class SYSTEM_API TcpClientChannel final
		{
		public:
			//for client
			TcpClientChannel();
			//for server
			TcpClientChannel(const TcpClientPtr& client);
			~TcpClientChannel();

			bool ProduceRead();
			bool ConsumeRead();
			
			void ProduceWrite(Msg* msg);
			bool ConsumeWrite();

			void Connect(const std::string &ip, int port);

			TcpClientPtr GetClient() const;

			void SetSendEventPool(ObjectPool<TcpSendEventArgs>* pool);
			void SetRecvEventPool(ObjectPool<TcpReceiveEventArgs>* pool);
		protected:
			virtual void OnReceive(const TcpReceiveEventArgs& e);
			virtual void OnSend(const TcpSendEventArgs& e);
			virtual void OnConnect(const TcpConnectEventArgs& e);
		public:
			TcpReceiveEventHandler Receive;
			TcpSendEventHandler Send;
			TcpConnectEventHandler Connected;
		private:
			static const int RECV_BUFF_SIZE = 10240 * 5;
			static const int SEND_BUFF_SIZE = 10240 * 5;
			std::mutex m_send_mutex;
			std::mutex m_recv_mutex;
			std::vector<Msg*> m_recv_msgs;
			std::vector<Msg*> m_send_msgs;
			ObjectPool<TcpReceiveEventArgs>* m_recv_event_pool = nullptr;
			ObjectPool<TcpSendEventArgs>* m_send_event_pool = nullptr;
			TcpClientPtr m_client = nullptr;
			char* m_recv_buff = new char[RECV_BUFF_SIZE];
			char* m_send_buff = new char[SEND_BUFF_SIZE];
			int m_read_pos = 0;
			int m_write_pos = 0;
		};
	}
}
#endif // !SYSTEM_HCN_TCPCLIENTCHANNEL_H
