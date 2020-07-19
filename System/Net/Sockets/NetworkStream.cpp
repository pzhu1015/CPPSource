///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Net/Sockets/NetworkStream.h"
#include "System/Net/Sockets/Socket.h"
#include "System/NotSupportedException.h"
#include "System/ArgumentNullException.h"
#include "System/ArgumentOutOfRangeException.h"
#include "System/InvalidOperationException.h"
#include "System/IOException.h"
#include <assert.h>

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			NetworkStream::NetworkStream(const SocketPtr &socket)
			{
				if (socket == nullptr)
				{
					throw ArgumentNullException("socket");
				}
				assert(socket != nullptr);
				InitNetworkStream(socket, FileAccess::ReadWrite);
			}

			NetworkStream::NetworkStream(const SocketPtr &socket, bool ownsSocket)
			{
				if (socket == nullptr)
				{
					throw ArgumentNullException("socket");
				}
				assert(socket != nullptr);
				InitNetworkStream(socket, FileAccess::ReadWrite);
			}

			NetworkStream::NetworkStream(const SocketPtr &socket, FileAccess access)
			{
				if (socket == nullptr)
				{
					throw ArgumentNullException("socket");
				}
				assert(socket != nullptr);
				InitNetworkStream(socket, access);
			}

			NetworkStream::NetworkStream(const SocketPtr &socket, FileAccess access, bool ownsSocket)
			{
				if (socket == nullptr)
				{
					throw ArgumentNullException("socket");
				}
				assert(socket != nullptr);
				InitNetworkStream(socket, access);
			}

			NetworkStream::~NetworkStream()
			{
				Dispose(false);
			}

			bool NetworkStream::GetCanRead() const
			{
				return m_readable;
			}

			bool NetworkStream::GetCanWrite() const
			{
				return m_writeable;
			}

			bool NetworkStream::GetDataAvailable() const
			{
				assert(m_socket != nullptr);
				return m_socket->GetAvailable() != 0;
			}

			int NetworkStream::GetReadTimeout() const
			{
				assert(m_socket != nullptr);
				return m_socket->GetReceiveTimeout();
			}

			void NetworkStream::SetReadTimeout(int timeout)
			{
				if (timeout < 0)
				{
					throw ArgumentOutOfRangeException("timeout");
				}
				assert(m_socket != nullptr);
				m_socket->SetReceiveTimeout(timeout);
			}

			int NetworkStream::GetWriteTimeout() const
			{
				assert(m_socket != nullptr);
				return m_socket->GetSendTimeout();
			}

			void NetworkStream::SetWriteTimeout(int timeout)
			{
				if (timeout < 0)
				{
					throw ArgumentOutOfRangeException("timeout");
				}
				assert(m_socket != nullptr);
				m_socket->SetSendTimeout(timeout);
			}

			void NetworkStream::Close(int timeout)
			{
				if (timeout < 0)
				{
					throw ArgumentOutOfRangeException("timeout");
				}
				m_close_timeout = timeout;
				Stream::Close();
			}

			int NetworkStream::Read(char * buffer, int offset, int count)
			{
				if (buffer == nullptr)
				{
					throw ArgumentNullException("buffer");
				}
				if (offset < 0)
				{
					throw ArgumentOutOfRangeException("offset");
				}
				if (count < 0)
				{
					throw ArgumentOutOfRangeException("count");
				}
				if (!GetCanRead())
				{
					throw InvalidOperationException("CanRead");
				}
				assert(m_socket != nullptr);
				return m_socket->Receive(buffer + offset, count);
			}

			void NetworkStream::Write(char * buffer, int offset, int count)
			{
				if (buffer == nullptr)
				{
					throw ArgumentNullException("buffer");
				}
				if (offset < 0)
				{
					throw ArgumentOutOfRangeException("offset");
				}
				if (count < 0)
				{
					throw ArgumentOutOfRangeException("count");
				}
				if (!GetCanWrite())
				{
					throw InvalidOperationException("CanWrite");
				}
				assert(m_socket != nullptr);
				m_socket->Send(buffer + offset, count);
			}

			bool NetworkStream::GetWriteable() const
			{
				return m_writeable;
			}

			void NetworkStream::SetWriteable(bool writeable)
			{
				m_writeable = writeable;
			}

			bool NetworkStream::GetReadable() const
			{
				return m_readable;
			}

			void NetworkStream::SetReadable(bool readable)
			{
				m_readable = readable;
			}

			SocketPtr NetworkStream::GetSocket() const
			{
				return m_socket;
			}

			int64_t NetworkStream::GetLength() const
			{
				throw NotSupportedException(__func__);
			}

			int64_t NetworkStream::GetPosition() const
			{
				throw NotSupportedException(__func__);
			}

			void NetworkStream::SetPosition(int64_t pos)
			{
				throw NotSupportedException(__func__);
			}

			bool NetworkStream::GetCanSeek() const
			{
				return false;
			}

			void NetworkStream::Flush()
			{
				throw NotSupportedException(__func__);
			}

			int64_t NetworkStream::Seek(int64_t offset, SeekOrigin origin)
			{
				throw NotSupportedException(__func__);
			}

			void NetworkStream::SetLength(int64_t value)
			{
				throw NotSupportedException(__func__);
			}

			void NetworkStream::Dispose(bool disposing)
			{
				if (disposing)
				{
					if (m_socket != nullptr)
					{
						m_readable = false;
						m_writeable = false;
						if (m_ownsocket)
						{
							m_socket->Close(m_close_timeout);
						}
					}
				}
				Stream::Dispose(disposing);
			}
			void NetworkStream::InitNetworkStream(const SocketPtr &socket, FileAccess access)
			{
				if (!socket->GetBlocking())
				{
					throw IOException("socket not blocking");
				}
				if (!socket->GetConnected())
				{
					throw IOException("socket not connected");
				}
				if (socket->GetSocketType() != SocketType::Stream)
				{
					throw IOException("socket not stream");
				}
				m_socket = socket;
				switch (access)
				{
				case FileAccess::Read:
					m_readable = true;
					break;
				case FileAccess::Write:
					m_writeable = true;
					break;
				case FileAccess::ReadWrite:
					m_readable = true;
					m_writeable = true;
					break;
				}
			}
		}
	}
}
