///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_IO_STREAM_H
#define SYSTEM_IO_STREAM_H

#include "System/DllExport.h"
#include "System/IO/SeekOrigin.h"
#include <stdint.h>

namespace System
{
	namespace IO
	{
		class SYSTEM_API Stream
		{
		public:
			Stream();
			virtual bool GetCanRead() const = 0;
			virtual bool GetCanSeek() const = 0;
			virtual bool GetCanTimeout();
			virtual bool GetCanWrite() const = 0;
			virtual int64_t GetLength() const = 0;
			virtual int64_t GetPosition() const = 0;
			virtual int GetReadTimeout();
			virtual void SetReadTimeout(int timeout);
			virtual int GetWriteTimeout();
			virtual void SetWriteTimeout(int timeout);
			virtual void Close();
			virtual void CopyTo(Stream* dest);
			virtual void CopyTo(Stream* dest, int buffersize);
			virtual void Flush() = 0;
			virtual int Read(char* buffer, int offset, int count) = 0;
			virtual int ReadByte();
			virtual int64_t Seek(int64_t offset, SeekOrigin origin) = 0;
			virtual void SetLength(int64_t value) = 0;
			virtual void Write(char* buffer, int offset, int count) = 0;
			virtual void WriteByte();
		private:
			bool m_can_timeout = false;
			int m_read_timeout = 0;
			int m_write_timeout = 0;
		};
	}
}

#endif // !SYSTEM_IO_STREAM_H
