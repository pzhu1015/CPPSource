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

		void Stream::Dispose(bool disposing)
		{
		}

		bool Stream::GetCanRead() const
		{
			return false;
		}

		bool Stream::GetCanTimeout()
		{
			return false;
		}

		int Stream::GetReadTimeout() const
		{
			return 0;
		}

		void Stream::SetReadTimeout(int timeout)
		{
		}

		int Stream::GetWriteTimeout() const
		{
			return 0;
		}

		void Stream::SetWriteTimeout(int timeout)
		{
		}

		void Stream::Close()
		{
			Dispose(true);
		}

		void Stream::CopyTo(const StreamPtr &dest)
		{
		}

		void Stream::CopyTo(const StreamPtr &dest, int buffersize)
		{
		}

		int Stream::ReadByte()
		{
			char byte[1];
			int reads = Read(byte, 0, 1);
			if (reads == 0)
			{
				return -1;
			}
			return byte[0];
		}

		void Stream::WriteByte(char value)
		{
			char byte[1];
			byte[0] = value;
			Write(byte, 0, 1);
		}
		void Stream::Dispose()
		{
			Close();
		}
	}
}