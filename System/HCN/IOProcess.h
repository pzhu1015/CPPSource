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
#include "System/Base/DllExport.h"
#include "System/HCN/Events.h"
#include "System/HCN/Ptrs.h"
#include "System/Net/Sockets/SocketInclude.h"
#include "System/Net/Ptrs.h"
#include "System/Threading/Ptrs.h"
#include "System/IO/Ptrs.h"
#include <unordered_map>
#include <vector>
#include <mutex>
#include <condition_variable>

using namespace System::Net;
using namespace System::Threading;
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
		static thread_local ObjectPool<TcpReceiveEventArgs>* t_recv_event_pool = nullptr;
		static thread_local ObjectPool<TcpSendEventArgs>* t_send_event_pool = nullptr;
		class SYSTEM_API IOProcess
		{
		public:
			IOProcess();
			~IOProcess();

			void Start();

			void Stop();
			size_t GetClients() const;

			void ConsumeRead();

			virtual void AddClient(const TcpClientChannelPtr& client) = 0;

		protected:
			virtual void OnReadStart(const IOProcessReadStartEventArgs& e);
			virtual void OnReadStop(const IOProcessReadStopEventArgs& e);
			virtual void OnWriteStart(const IOProcessWriteStartEventArgs& e);
			virtual void OnWriteStop(const IOProcessWriteStopEventArgs& e);
			virtual void OnOnLine(const TcpOnLineEventArgs& e);
			virtual void OnOffLine(const TcpOffLineEventArgs& e);
			virtual void OnSelectError(const TcpSelectErrorEventArgs& e);
			virtual void IOReadHandle() = 0;
			virtual void IOWriteHandle() = 0;
			
		private:
			void AsyncStartRead();
			void AsyncStartWrite();

		public:
			IOProcessReadStartEventHandler IOProcessReadStart;
			IOProcessReadStopEventHandler IOProcessReadStop;

			IOProcessWriteStartEventHandler IOProcessWriteStart;
			IOProcessWriteStopEventHandler IOProcessWriteStop;

			TcpOnLineEventHandler OnLine;
			TcpOffLineEventHandler OffLine;
			TcpReceiveEventHandler Receive;
			TcpSendEventHandler Send;
			TcpSelectErrorEventHandler SelectError;
		protected:
			bool m_is_start = false;
			bool m_change = false;
			std::mutex m_mutex;
			std::condition_variable m_cond;
			ThreadPtr m_read_thread;
			ThreadPtr m_write_thread;
			//std::vector<TcpClientPtr> m_tcpclients;
			std::unordered_map<SOCKET, TcpClientChannelPtr> m_clients;
			ObjectPool<TcpReceiveEventArgs>* m_recv_event_pool = nullptr;
			ObjectPool<TcpSendEventArgs>* m_send_event_pool = nullptr;
		};
	}
}

#endif // !SYSTEM_HNC_IOPROCESS_H
