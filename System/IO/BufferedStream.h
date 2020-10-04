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
#include "System/Base/DllExport.h"
#include "System/IO/Stream.h"
#include "System/IO/Ptrs.h"
namespace System
{
	namespace IO
	{
		class SYSTEM_API BufferedStream final : public Stream
		{
		public:
			BufferedStream(const StreamPtr &stream);
			BufferedStream(const StreamPtr &stream, int size);
			virtual ~BufferedStream();
			virtual bool GetCanRead() const override;
			virtual bool GetCanSeek() const override;
			virtual bool GetCanWrite() const override;
			virtual int64_t GetLength() const override;
			virtual int64_t GetPosition() const override;
			virtual void SetPosition(int64_t pos) override;
			virtual int Read(char* buffer, int offset, int count) override;
			virtual int64_t Seek(int64_t offset, SeekOrigin origin) override;
			virtual void Write(char* buffer, int offset, int count) override;
			virtual void SetLength(int64_t value) override;
			virtual void Flush() override;
			virtual int ReadByte() override;
			virtual void WriteByte(char value) override;
		private:
			void FlushWrite();
			void FlushRead();
			void ClearReadBufferBeforeWrite();
			void WriteToBuffer(char* buffer, int &offset, int &count);
			int ReadFromBuffer(char* buffer, int offset, int count);
		private:
			static const int DEFAULT_BUFFER_SIZE = 4096;
			static const int MAX_SHADOW_BUFFER_SIZE = 81920;
			int m_buffersize = DEFAULT_BUFFER_SIZE;
			int m_read_pos = 0;
			int m_write_pos = 0;
			int m_read_length = 0;
			StreamPtr m_stream = nullptr;
			char* m_buffer = nullptr;
		};
	}
}

#endif // !SYSTEM_IO_BUFFEREDSTREAM_H
