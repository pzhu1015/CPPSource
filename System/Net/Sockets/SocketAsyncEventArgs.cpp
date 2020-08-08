///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Net/Sockets/SocketAsyncEventArgs.h"

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			SocketAsyncEventArgs::SocketAsyncEventArgs()
			{
			}

			SocketAsyncEventArgs::~SocketAsyncEventArgs()
			{
			}

			Socket * SocketAsyncEventArgs::GetAcceptSocket() const
			{
				return nullptr;
			}

			Socket * SocketAsyncEventArgs::GetConnectSocket() const
			{
				return nullptr;
			}

			int SocketAsyncEventArgs::GetCount() const
			{
				return 0;
			}

			int SocketAsyncEventArgs::GetOffset() const
			{
				return 0;
			}

			void SocketAsyncEventArgs::GetBuffer(char * buffer, int & length) const
			{
			}

			void SocketAsyncEventArgs::SetBuffer(int offset, int count)
			{
			}

			void SocketAsyncEventArgs::SetBuffer(char * buffer, int offset, int count)
			{
			}

			EndPoint * SocketAsyncEventArgs::GetRemoteEndPoint() const
			{
				return m_remote_endpoint;
			}

			void SocketAsyncEventArgs::SetRemoteEndPoint(EndPoint* endpoint)
			{
				m_remote_endpoint = endpoint;
			}

			void SocketAsyncEventArgs::Dispose()
			{
			}

			void SocketAsyncEventArgs::OnCompleted(const SocketAsyncEventArgs& e)
			{
				if (this->Completed != nullptr)
				{
					this->Completed(e);
				}
			}
		}
	}
}
