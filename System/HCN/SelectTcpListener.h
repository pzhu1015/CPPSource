///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HNC_SELECTTCPLISTENER_H
#define SYSTEM_HNC_SELECTTCPLISTENER_H
#include "System/HCN/Events.h"
#include "System/HCN/Ptrs.h"
#include "System/Threading/Ptrs.h"
#include "System/Net/Ptrs.h"
#include <vector>

using namespace System::Net;
using namespace System::Threading;
namespace System
{
	namespace HCN
	{
		class SelectTcpListener
		{
		public:
			SelectTcpListener();
			~SelectTcpListener();

			bool Start(int port, int threads);
			bool Stop();

		protected:
			virtual void OnStart(TcpStartEventArgs& e);
			virtual void OnStop(TcpStopEventArgs& e);
			virtual void OnAccept(TcpAcceptEventArgs& e);
			virtual void OnSelectError(TcpSelectErrorEventArgs& e);

		private:
			void AsyncStart(int port, int threads);
			void AsyncAccept(const TcpClientPtr &client);
			void OnClientProcessStart(ClientProcessStartEventArgs& e);
			void OnClientProcessStop(ClientProcessStopEventArgs& e);

		public:
			TcpStartEventHandler Started;
			TcpSTopEventHandler Stoped;
			TcpAccetpEventHandler Accepted;
			TcpReceiveEventHandler Receive;
			TcpSendEventHandler Send;
			TcpSelectErrorEventHandler SelectError;
			TcpOnLineEventHandler OnLine;
			TcpOffLineEventHandler OffLine;

		private:
			bool m_is_start = false;
			TcpListenerPtr m_server = nullptr;
			std::vector<ClientProcessPtr> m_clients;
			ThreadPoolPtr m_threadpool = nullptr;
			ThreadPtr m_thread = nullptr;
			SemaphorePtr m_start_sem = nullptr;
			SemaphorePtr m_stop_sem = nullptr;
		};
	}
}
#endif // !SYSTEM_HNC_SELECTTCPLISTENER_H
