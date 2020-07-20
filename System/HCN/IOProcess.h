///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HNC_IOPROCESS_H
#define SYSTEM_HNC_IOPROCESS_H
#include "System/DllExport.h"
#include "System/HCN/Events.h"
#include "System/HCN/Ptrs.h"
#include "System/Net/Sockets/SocketInclude.h"
#include "System/Threading/Ptrs.h"
#include "System/Net/Ptrs.h"
#include "System/IO/Ptrs.h"
#include <unordered_map>
#include <vector>
#include <mutex>
#include <condition_variable>

using namespace System::IO;
using namespace System::Net;
using namespace System::Threading;
namespace System
{
	namespace HCN
	{
		class SYSTEM_API IOProcess
		{
		public:
			IOProcess();
			~IOProcess();

			void Start();

			size_t GetClients() const;

			void AddClient(const TcpClientPtr &client);

			void Stop();
		protected:
			virtual void OnStart(const IOProcessStartEventArgs& e);
			virtual void OnStop(const IOProcessStopEventArgs& e);
			virtual void OnOnLine(const TcpOnLineEventArgs& e);
			virtual void OnOffLine(const TcpOffLineEventArgs& e);
			virtual void OnSelectError(const TcpSelectErrorEventArgs& e);

		private:
			void AsyncStart();

		public:
			IOProcessStartEventHandler IOProcessStart;
			IOProcessStopEventHandler IOProcessStop;
			TcpOnLineEventHandler OnLine;
			TcpOffLineEventHandler OffLine;
			TcpReceiveEventHandler Receive;
			TcpSendEventHandler Send;
			TcpSelectErrorEventHandler SelectError;
		private:
			bool m_is_start = false;
			std::mutex m_mutex;
			std::condition_variable m_cond;
			ThreadPtr m_thread;
			std::vector<TcpClientPtr> m_tcpclients;
			std::unordered_map<SOCKET, SelectTcpClientPtr> m_clients;
		};
	}
}

#endif // !SYSTEM_HNC_IOPROCESS_H
