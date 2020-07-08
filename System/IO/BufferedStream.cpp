///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/BufferedStream.h"

namespace System
{
	namespace IO
	{
		BufferedStream::BufferedStream(Stream * stream)
		{
			m_stream = stream;
			m_buffersize = 4096;
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
		}

		bool BufferedStream::GetCanRead() const
		{
			if (m_stream != nullptr)
			{
				return m_stream->GetCanRead();
			}
			return false;
		}

		bool BufferedStream::GetCanSeek() const
		{
			if (m_stream != nullptr)
			{
				return m_stream->GetCanSeek();
			}
			return false;
		}

		bool BufferedStream::GetCanWrite() const
		{
			if (m_stream != nullptr)
			{
				return m_stream->GetCanWrite();
			}
			return false;
		}

		int64_t BufferedStream::GetLength() const
		{
			if (m_stream != nullptr)
			{
				return m_stream->GetLength();
			}
			return -1;
		}

		int64_t BufferedStream::GetPosition() const
		{
			if (m_stream != nullptr)
			{
				return m_stream->GetPosition();
			}
			return -1;
		}

		int BufferedStream::Read(char * buffer, int offset, int count)
		{
			return 0;
		}

		int64_t BufferedStream::Seek(int64_t offset, SeekOrigin origin)
		{
			if (m_stream != nullptr)
			{
				return m_stream->Seek(offset, origin);
			}
			return -1;
		}

		void BufferedStream::Write(char * buffer, int offset, int count)
		{
			if (m_stream != nullptr && m_buffer != nullptr)
			{
				if (count >= m_buffersize)
				{
					if (m_pos > 0)
					{
						m_stream->Write(m_buffer, 0, m_pos);
						m_pos = 0;
					}
					m_stream->Write(buffer, offset, count);
					return;
				}
				if (count < m_buffersize - m_pos)
				{
					if (m_pos > 0)
					{
						m_stream->Write(m_buffer, 0, m_pos);
						m_pos = 0;
					}
				}
				memcpy(m_buffer + m_pos, buffer + offset, count);
				m_pos += count;
			}
		}

		void BufferedStream::SetLength(int64_t value)
		{
		}

		void BufferedStream::Flush()
		{
			if (m_stream != nullptr)
			{
				if (m_pos > 0)
				{
					m_stream->Write(m_buffer, 0, m_pos);
				}
				m_stream->Flush();
			}
		}
	}
}