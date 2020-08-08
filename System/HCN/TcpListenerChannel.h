///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HNC_TCPLISTENERCHANNEL_H
#define SYSTEM_HNC_TCPLISTENERCHANNEL_H
#include "System/DllExport.h"
#include "System/HCN/Events.h"
#include "System/HCN/Ptrs.h"
#include "System/Threading/Ptrs.h"
#include "System/Net/Sockets/SocketInclude.h"
#include "System/Net/Ptrs.h"
#include <vector>

using namespace System::Net;
using namespace System::Threading;
namespace System
{
	namespace HCN
	{
		class SYSTEM_API TcpListenerChannel
		{
		public:
			TcpListenerChannel();
			~TcpListenerChannel();

			bool Start(int port, int threads);
			bool Stop();

			virtual void OnIOProcessStart(const IOProcessStartEventArgs& e);
			virtual void OnIOProcessStop(const IOProcessStopEventArgs& e);
			void AsyncAccept(const TcpClientPtr &client, size_t idx);
		protected:
			virtual void OnStart(const TcpStartEventArgs& e);
			virtual void OnStop(const TcpStopEventArgs& e);
			virtual void OnSelectError(const TcpSelectErrorEventArgs& e);


			virtual IOProcessPtr GetIOProcess() = 0;
			virtual void AcceptHandle(SOCKET sock) = 0;
		private:
			void AsyncStart(int port, int threads);

		public:
			TcpStartEventHandler Started;
			TcpSTopEventHandler Stoped;
			TcpReceiveEventHandler Receive;
			TcpSendEventHandler Send;
			TcpSelectErrorEventHandler SelectError;
			TcpOnLineEventHandler OnLine;
			TcpOffLineEventHandler OffLine;

		protected:
			bool m_is_start = false;
			TcpListenerPtr m_server = nullptr;
			std::vector<IOProcessPtr> m_io_processor;
			ThreadPoolPtr m_threadpool = nullptr;
			ThreadPtr m_thread = nullptr;
			SemaphorePtr m_start_sem = nullptr;
			SemaphorePtr m_stop_sem = nullptr;
		};
	}
}
#endif // !SYSTEM_HNC_TCPLISTENERCHANNEL_H
