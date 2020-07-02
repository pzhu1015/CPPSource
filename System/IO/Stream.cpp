///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/Stream.h"

namespace System
{
	namespace IO
	{
		Stream::Stream()
		{
		}

		bool Stream::GetCanRead() const
		{
			return false;
		}

		bool Stream::GetCanSeek() const
		{
			return false;
		}

		bool Stream::GetCanTimeout()
		{
			return false;
		}

		bool Stream::GetCanWrite() const
		{
			return false;
		}

		int64_t Stream::GetLength() const
		{
			return int64_t();
		}

		int64_t Stream::GetPosition() const
		{
			return int64_t();
		}

		int Stream::GetReadTimeout()
		{
			return 0;
		}

		void Stream::SetReadTimeout(int timeout)
		{
		}

		int Stream::GetWriteTimeout()
		{
			return 0;
		}

		void Stream::SetWriteTimeout(int timeout)
		{
		}

		void Stream::Close()
		{
		}

		void Stream::CopyTo(Stream * dest)
		{
		}

		void Stream::CopyTo(Stream * dest, int buffersize)
		{
		}

		void Stream::Flush()
		{
		}

		int Stream::Read(char * buffer, int offset, int count)
		{
			return 0;
		}

		int Stream::ReadByte()
		{
			return 0;
		}

		int64_t Stream::Seek(int64_t offset, SeekOrigin origin)
		{
			return int64_t();
		}

		void Stream::SetLength(int64_t value)
		{
		}

		void Stream::Write(char * buffer, int offset, int count)
		{
		}

		void Stream::WriteByte(char value)
		{
		}
		void Stream::Dispose()
		{
		}
	}
}