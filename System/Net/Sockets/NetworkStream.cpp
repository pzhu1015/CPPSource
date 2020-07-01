///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Net/Sockets/NetworkStream.h"

namespace System
{
	namespace Net
	{
		namespace Sockets
		{
			NetworkStream::NetworkStream()
			{
			}
			NetworkStream::~NetworkStream()
			{
			}
			bool NetworkStream::GetCanRead() const
			{
				return false;
			}
			bool NetworkStream::GetCanSeek() const
			{
				return false;
			}
			bool NetworkStream::GetCanWrite() const
			{
				return false;
			}
			int64_t NetworkStream::GetLength() const
			{
				return int64_t();
			}
			int64_t NetworkStream::GetPosition() const
			{
				return int64_t();
			}
			void NetworkStream::Flush()
			{
			}
			int NetworkStream::Read(char * buffer, int offset, int count)
			{
				return 0;
			}
			int64_t NetworkStream::Seek(int64_t offset, SeekOrigin origin)
			{
				return int64_t();
			}
			void NetworkStream::SetLength(int64_t value)
			{
			}
			void NetworkStream::Write(char * buffer, int offset, int count)
			{
			}
		}
	}
}
