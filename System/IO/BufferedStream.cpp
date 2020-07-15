///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/BufferedStream.h"
#include <assert.h>

namespace System
{
	namespace IO
	{
		BufferedStream::BufferedStream(Stream * stream)
		{
			m_stream = stream;
			m_buffersize = DEFAULT_BUFFER_SIZE;
			m_buffer = new char[m_buffersize];
		}

		BufferedStream::BufferedStream(Stream * stream, int size)
		{
			m_stream = stream;
			m_buffersize = size;
			m_buffer = new char[m_buffersize];
		}

		BufferedStream::~BufferedStream()
		{
			delete[] m_buffer;
			delete m_stream;
		}

		bool BufferedStream::GetCanRead() const
		{
			assert(m_stream != nullptr);
			return m_stream->GetCanRead();
		}

		bool BufferedStream::GetCanSeek() const
		{
			assert(m_stream != nullptr);
			return m_stream->GetCanSeek();
		}

		bool BufferedStream::GetCanWrite() const
		{
			assert(m_stream != nullptr);
			return m_stream->GetCanWrite();
		}

		int64_t BufferedStream::GetLength() const
		{
			assert(m_stream != nullptr);
			if (m_write_pos > 0)
			{
				const_cast<BufferedStream*>(this)->FlushWrite();
			}
			return m_stream->GetLength();
		}

		int64_t BufferedStream::GetPosition() const
		{
			assert(m_stream != nullptr);
			assert(m_write_pos > 0 && m_read_pos != m_read_length);
			return m_stream->GetPosition() + (m_read_pos - m_read_length + m_write_pos);
		}
		int BufferedStream::Read(char * buffer, int offset, int count)
		{
			return 0;
		}

		int64_t BufferedStream::Seek(int64_t offset, SeekOrigin origin)
		{
			assert(m_stream != nullptr);
			if (m_write_pos > 0)
			{
				FlushWrite();
				return m_stream->Seek(offset, origin);
			}
			if (m_read_length - m_read_length && origin == SeekOrigin::Current)
			{
				offset -= (m_read_length - m_read_pos);
			}
			int64_t old_pos = GetPosition();
			assert(old_pos == m_stream->GetPosition() + (m_read_pos - m_read_length));
			int64_t new_pos = m_stream->Seek(offset, origin);
			m_read_pos = (int)(new_pos - (old_pos - m_read_pos));
			if (0 <= m_read_pos && m_read_pos < m_read_length)
			{
				m_stream->Seek(m_read_length - m_read_pos, SeekOrigin::Current);
			}
			else
			{
				m_read_pos = m_read_length = 0;
			}
			assert(new_pos == GetPosition());
			return new_pos;
		}

		void BufferedStream::Write(char * buffer, int offset, int count)
		{
			assert(m_stream != nullptr && m_buffer != nullptr);
			if (count >= m_buffersize)
			{
				if (m_write_pos > 0)
				{
					m_stream->Write(m_buffer, 0, m_write_pos);
					m_write_pos = 0;
				}
				m_stream->Write(buffer, offset, count);
				return;
			}
			if (count < m_buffersize - m_write_pos)
			{
				if (m_write_pos > 0)
				{
					m_stream->Write(m_buffer, 0, m_write_pos);
					m_write_pos = 0;
				}
			}
			memcpy(m_buffer + m_write_pos, buffer + offset, count);
			m_write_pos += count;
		}

		void BufferedStream::SetLength(int64_t value)
		{
			assert(m_stream != nullptr);
			if (value < 0)
			{
				return;
			}
			Flush();
			m_stream->SetLength(value);
		}

		void BufferedStream::Flush()
		{
			assert(m_stream != nullptr);
			if (m_write_pos > 0)
			{
				FlushWrite();
			}
		}

		void BufferedStream::FlushWrite()
		{
			assert(m_stream != nullptr);
			m_stream->Write(m_buffer, 0, m_write_pos);
			m_write_pos = 0;
			m_stream->Flush();
		}

		void BufferedStream::FlushRead()
		{
			assert(m_stream != nullptr);
			if (m_read_pos - m_read_length != 0)
			{
				m_stream->Seek(m_read_pos - m_read_length, SeekOrigin::Current);
			}
			m_read_pos = 0;
			m_read_length = 0;
		}
	}
}