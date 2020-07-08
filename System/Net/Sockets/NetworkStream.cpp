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

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			NetworkStream::NetworkStream(Socket * socket)
			{
				m_socket = socket;
				m_ownsocket = false;
				m_access = FileAccess::ReadWrite;
			}

			NetworkStream::NetworkStream(Socket * socket, bool ownsSocket)
			{
				m_socket = socket;
				m_ownsocket = ownsSocket;
				m_access = FileAccess::ReadWrite;
			}

			NetworkStream::NetworkStream(Socket * socket, FileAccess access)
			{
				m_socket = socket;
				m_ownsocket = false;
				m_access = access;
			}

			NetworkStream::NetworkStream(Socket * socket, FileAccess access, bool ownsSocket)
			{
				m_socket = socket;
				m_access = access;
				m_ownsocket = ownsSocket;
			}

			NetworkStream::~NetworkStream()
			{
				if (m_ownsocket)
				{
					if (m_socket != nullptr)
					{
						m_socket->Close();
						m_socket->Dispose();
					}
				}
			}

			bool NetworkStream::GetCanRead() const
			{
				return (m_access == FileAccess::Read) || (m_access == FileAccess::ReadWrite);
			}

			bool NetworkStream::GetCanWrite() const
			{
				return (m_access == FileAccess::Write) || (m_access == FileAccess::ReadWrite);
			}

			bool NetworkStream::GetDataAvailable() const
			{
				return false;
			}

			int NetworkStream::GetReadTimeout() const
			{
				if (m_socket != nullptr)
				{
					return m_socket->GetReceiveTimeout();
				}
				return -1;
			}

			void NetworkStream::SetReadTimeout(int timeout)
			{
				if (m_socket != nullptr)
				{
					m_socket->SetReceiveTimeout(timeout);
				}
			}

			int NetworkStream::GetWriteTimeout() const
			{
				if (m_socket != nullptr)
				{
					return m_socket->GetSendTimeout();
				}
				return -1;
			}

			void NetworkStream::SetWriteTimeout(int timeout)
			{
				if (m_socket != nullptr)
				{
					m_socket->SetSendTimeout(timeout);
				}
			}

			void NetworkStream::Close(int timeout)
			{
				if (m_socket != nullptr)
				{
					m_socket->Close(timeout);
				}
			}

			int NetworkStream::Read(char * buffer, int offset, int count)
			{
				if (m_socket != nullptr)
				{
					return m_socket->Receive(buffer + offset, count);
				}
				return -1;
			}

			void NetworkStream::Write(char * buffer, int offset, int count)
			{
				if (m_socket)
				{
					m_socket->Send(buffer + offset, count);
				}
			}

			bool NetworkStream::GetWriteable() const
			{
				return false;
			}

			void NetworkStream::SetWriteable(bool writeable)
			{
			}

			bool NetworkStream::GetReadable() const
			{
				return false;
			}

			void NetworkStream::SetReadable(bool readable)
			{
			}

			Socket * NetworkStream::GetSocket() const
			{
				return m_socket;
			}

			int64_t NetworkStream::GetLength() const
			{
				//Not Support
				return -1;
			}

			int64_t NetworkStream::GetPosition() const
			{
				//Not Support
				return -1;
			}

			bool NetworkStream::GetCanSeek() const
			{
				//Not Support
				return false;
			}

			void NetworkStream::Flush()
			{
				//Not Support
			}

			int64_t NetworkStream::Seek(int64_t offset, SeekOrigin origin)
			{
				//Not Support
				return -1;
			}

			void NetworkStream::SetLength(int64_t value)
			{
				//Not Support
			}

			void NetworkStream::Dispose(bool disposing)
			{
				if (disposing)
				{
					Stream::Dispose();
				}
			}
		}
	}
}
