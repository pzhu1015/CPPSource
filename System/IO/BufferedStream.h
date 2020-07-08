///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_IO_BUFFEREDSTREAM_H
#define SYSTEM_IO_BUFFEREDSTREAM_H
#include "System/DllExport.h"
#include "System/IO/Stream.h"
namespace System
{
	namespace IO
	{
		class SYSTEM_API BufferedStream : public Stream
		{
		public:
			BufferedStream(Stream* stream);
			BufferedStream(Stream* stream, int size);
			virtual ~BufferedStream();
			virtual bool GetCanRead() const override;
			virtual bool GetCanSeek() const override;
			virtual bool GetCanWrite() const override;
			virtual int64_t GetLength() const override;
			virtual int64_t GetPosition() const override;
			virtual int Read(char* buffer, int offset, int count) override;
			virtual int64_t Seek(int64_t offset, SeekOrigin origin) override;
			virtual void Write(char* buffer, int offset, int count) override;
			virtual void SetLength(int64_t value) override;
			virtual void Flush() override;
		private:
			int m_buffersize = 4096;
			int m_pos = 0;
			Stream* m_stream = nullptr;
			char* m_buffer = nullptr;
		};
	}
}

#endif // !SYSTEM_IO_BUFFEREDSTREAM_H
