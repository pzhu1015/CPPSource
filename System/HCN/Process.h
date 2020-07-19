///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_HNC_CLIENTPROCESS_H
#define SYSTEM_HNC_CLIENTPROCESS_H
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
		class ClientWrapper
		{
		public:
			ClientWrapper(const TcpClientPtr &client);
			~ClientWrapper();
			BufferedStreamPtr m_stream;
			TcpClientPtr m_client;
		};
		class Process
		{
		public:
			Process();
			~Process();

			void Start();

			size_t GetClients() const;

			void AddClient(const TcpClientPtr &client);
		protected:
			virtual void OnStart(ProcessStartEventArgs* e);
			virtual void OnOnLine(OnLineEventArgs* e);
			virtual void OnOffLine(OffLineEventArgs* e);
			virtual void OnSelectError(TcpSelectErrorEventArgs* e);

		private:
			void AsyncStart();

		public:
			ProcessStartEventHandler ProcessStart;
			OnLineEventHandler OnLine;
			OffLineEventHandler OffLine;
			TcpSelectErrorEventHandler SelectError;
		private:
			bool m_is_start = false;
			std::mutex m_mutex;
			std::condition_variable m_cond;
			ThreadPtr m_thread;
			std::vector<TcpClientPtr> m_tcpclients;
			std::unordered_map<SOCKET, ClientWrapperPtr> m_clients;
		};
	}
}

#endif // !SYSTEM_HNC_CLIENTPROCESS_H
