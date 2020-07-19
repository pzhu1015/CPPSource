///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/BufferedStream.h"
#include "System/ArgumentNullException.h"
#include "System/ArgumentOutOfRangeException.h"
#include "System/NotSupportedException.h"
#include <algorithm>
#include <assert.h>

namespace System
{
	namespace IO
	{
		BufferedStream::BufferedStream(const StreamPtr &stream)
		{
			m_stream = stream;
			m_buffersize = DEFAULT_BUFFER_SIZE;
			m_buffer = new char[m_buffersize];
		}

		BufferedStream::BufferedStream(const StreamPtr &stream, int size)
		{
			m_stream = stream;
			m_buffersize = size;
			m_buffer = new char[m_buffersize];
		}

		BufferedStream::~BufferedStream()
		{
			delete[] m_buffer;
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

		void BufferedStream::SetPosition(int64_t pos)
		{
			if (pos < 0)
			{
				throw ArgumentOutOfRangeException("pos");
			}
			assert(m_stream != nullptr);
			assert(GetCanSeek());
			if (m_write_pos > 0)
			{
				FlushWrite();
			}
			m_read_pos = 0;
			m_read_length = 0;
			m_stream->Seek(pos, SeekOrigin::Begin);
		}

		int BufferedStream::Read(char * buffer, int offset, int count)
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
			assert(m_stream != nullptr && buffer != nullptr);
			assert(GetCanRead());
			int bytes_from_buffer = ReadFromBuffer(buffer, offset, count);
			if (bytes_from_buffer == count)
			{
				return bytes_from_buffer;
			}
			int already_satisfied = bytes_from_buffer;
			if (bytes_from_buffer > 0)
			{
				count -= bytes_from_buffer;
				offset += bytes_from_buffer;
			}
			assert(m_read_length == m_read_pos);
			m_read_pos = m_read_length = 0;
			if (count >= m_buffersize)
			{
				return m_stream->Read(buffer, offset, count) + already_satisfied;
			}
			m_read_length = m_stream->Read(m_buffer, 0, m_buffersize);
			bytes_from_buffer = ReadFromBuffer(buffer, offset, count);
			return bytes_from_buffer + already_satisfied;
			return 0;
		}

		int64_t BufferedStream::Seek(int64_t offset, SeekOrigin origin)
		{
			assert(m_stream != nullptr);
			assert(GetCanSeek());
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
			assert(m_stream != nullptr && m_buffer != nullptr);
			assert(GetCanWrite());
			if (m_write_pos == 0)
			{
				ClearReadBufferBeforeWrite();
			}
			assert(m_write_pos < m_buffersize);
			int total_user_bytes = m_write_pos + count;
			bool use_buffer = (total_user_bytes + count < (m_buffersize + m_buffersize));
			if (use_buffer)
			{
				WriteToBuffer(buffer, offset, count);
				if (m_write_pos < m_buffersize)
				{
					assert(count == 0);
					return;
				}
				assert(count >= 0);
				assert(m_write_pos == m_buffersize);
				assert(m_buffer != nullptr);
				m_stream->Write(buffer, 0, m_write_pos);
				m_write_pos = 0;
				WriteToBuffer(buffer, offset, count);
				assert(count == 0);
				assert(m_write_pos < m_buffersize);
			}
			else
			{
				if (m_write_pos > 0)
				{
					assert(m_buffer != nullptr);
					assert(total_user_bytes >= m_buffersize);
					if (total_user_bytes <= (m_buffersize + m_buffersize) && total_user_bytes <= MAX_SHADOW_BUFFER_SIZE)
					{
						memcpy(m_buffer + m_write_pos, buffer + offset, count);
						m_stream->Write(m_buffer, 0, total_user_bytes);
						m_write_pos = 0;
						return;
					}
					m_stream->Write(m_buffer, 0, m_write_pos);
					m_write_pos = 0;
				}
				m_stream->Write(buffer, offset, count);
			}
			
		}

		void BufferedStream::SetLength(int64_t value)
		{
			if (value < 0)
			{
				throw ArgumentOutOfRangeException("value");
			}
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
				assert(m_write_pos == 0 && m_read_pos == 0 && m_read_length == 0);
				return;
			}

			if (m_read_pos < m_read_length)
			{
				if (!m_stream->GetCanSeek())
				{
					return;
				}
				FlushRead();
				if (m_stream->GetCanWrite())
				{
					m_stream->Flush();
				}
				assert(m_write_pos == 0 && m_read_pos == 0 && m_read_length == 0);
				return;
			}

			if (m_stream->GetCanWrite())
			{
				m_stream->Flush();
			}
			m_write_pos = m_read_pos = m_read_length = 0;
		}

		int BufferedStream::ReadByte()
		{
			assert(m_stream != nullptr);
			assert(GetCanRead());
			if (m_read_pos == m_read_length)
			{
				if (m_write_pos > 0)
				{
					FlushWrite();
				}
				m_read_length = m_stream->Read(m_buffer, 0, m_buffersize);
				m_read_pos = 0;
			}
			if (m_read_pos == m_read_length)
			{
				return -1;
			}

			int b = m_buffer[m_read_pos++];
			return b;
		}

		void BufferedStream::WriteByte(char value)
		{
			assert(m_stream != nullptr);
			if (m_write_pos == 0)
			{
				assert(GetCanWrite());
				ClearReadBufferBeforeWrite();
			}
			if (m_write_pos >= m_buffersize - 1)
			{
				FlushWrite();
			}
			m_buffer[m_write_pos++] = value;
			assert(m_write_pos < m_buffersize);
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

		void BufferedStream::ClearReadBufferBeforeWrite()
		{
			assert(m_read_pos <= m_read_length);
			if (m_read_pos == m_read_length)
			{
				m_read_pos = m_read_length = 0;
				return;
			}
			assert(m_read_pos < m_read_length);
			if (!m_stream->GetCanSeek())
			{
				throw NotSupportedException();
			}
			FlushRead();
		}

		void BufferedStream::WriteToBuffer(char * buffer, int & offset, int & count)
		{
			int bytes_to_write = std::min<int>(m_buffersize - m_write_pos, count);
			if (bytes_to_write <= 0)
			{
				return;
			}
			memcpy(m_buffer + m_write_pos, buffer + offset, bytes_to_write);
			m_write_pos += bytes_to_write;
			count -= bytes_to_write;
			offset += bytes_to_write;
		}

		int BufferedStream::ReadFromBuffer(char * buffer, int offset, int count)
		{
			int read_bytes = m_read_length - m_read_pos;
			assert(read_bytes >= 0);
			if (read_bytes == 0)
			{
				return 0;
			}
			assert(read_bytes > 0);
			if (read_bytes > count)
			{
				read_bytes = count;
			}
			memcpy(m_buffer + m_read_pos, buffer + offset, read_bytes);
			m_read_pos += read_bytes;
			return read_bytes;
		}
	}
}