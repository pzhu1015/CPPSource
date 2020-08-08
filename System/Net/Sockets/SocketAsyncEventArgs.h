///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_NET_SOCKETASYNCEVENTARGS_H
#define SYSTEM_NET_SOCKETASYNCEVENTARGS_H
#include "System/DllExport.h"
#include "System/IDisposable.h"
#include "System/EventArgs.h"
#include "System/EventHandler.h"
#include "System/Net/EndPoint.h"
#include "System/Net/Sockets/Socket.h"

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			class Socket;
			class SYSTEM_API SocketAsyncEventArgs final : public EventArgs, public IDisposable
			{
			public:
				SocketAsyncEventArgs();

				virtual ~SocketAsyncEventArgs();

				Socket* GetAcceptSocket() const;

				Socket* GetConnectSocket() const;

				int GetCount() const;

				int GetOffset() const;

				void GetBuffer(char* buffer, int &length) const;

				void SetBuffer(int offset, int count);

				void SetBuffer(char* buffer, int offset, int count);

				EndPoint* GetRemoteEndPoint() const;

				void SetRemoteEndPoint(EndPoint* endpoint);

				virtual void Dispose();

			protected:
				virtual void OnCompleted(const SocketAsyncEventArgs& e);

			public:
				EventHandler Completed;
			private:
				EndPoint* m_remote_endpoint;
			};
		}
	}
}

#endif // !SYSTEM_NET_SOCKETASYNCEVENTARGS_H
