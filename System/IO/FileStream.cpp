///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/FileStream.h"

//p is write
//g is read

namespace System
{
	namespace IO
	{
		FileStream::FileStream(const std::string & filename, FileMode mode)
		{
			m_mode = mode;
			m_stream = new std::fstream();
			m_stream->open(filename, (int)mode);
		}
		FileStream::FileStream(const std::string & filename, FileMode mode, FileAccess access)
		{
			m_mode = mode;
			m_access = access;
			m_stream = new std::fstream();
			m_stream->open(filename, (int)mode, (int)access);
		}
		FileStream::~FileStream()
		{
		}
		bool FileStream::GetCanRead() const
		{
			return false;
		}
		bool FileStream::GetCanSeek() const
		{
			return false;
		}
		bool FileStream::GetCanWrite() const
		{
			return false;
		}
		int64_t FileStream::GetLength() const
		{
			return int64_t();
		}
		int64_t FileStream::GetPosition() const
		{
			if (m_stream == nullptr)
			{
				return -1;
			}
			if (m_access == FileAccess::Read)
			{
				return m_stream->tellg();
			}
			else if (m_access == FileAccess::Write)
			{
				return m_stream->tellp();
			}
			else
			{
				//TODO
			}
			return -1;
		}

		void FileStream::Flush()
		{
			if (m_stream != nullptr)
			{
				m_stream->flush();
			}
		}

		int FileStream::Read(char * buffer, int offset, int count)
		{
			if (m_stream != nullptr)
			{
				m_stream->seekg(offset);
				m_stream->read(buffer, count);
				return 1;
			}
			return -1;
		}

		int64_t FileStream::Seek(int64_t offset, SeekOrigin origin)
		{
			if (m_stream == nullptr)
			{
				return -1;
			}
			if (m_access == FileAccess::Read)
			{
				//return m_stream->seekg(offset, (int)origin);
			}
			else if (m_access == FileAccess::Write)
			{
				//return m_stream->seekp(offset, (int)origin);
			}
			else
			{
				//TODO
			}
			return -1;
		}

		void FileStream::SetLength(int64_t value)
		{
		}

		void FileStream::Write(char * buffer, int offset, int count)
		{
			m_stream->seekp(offset);
			m_stream->write(buffer, count);
		}

		void FileStream::Dispose()
		{
			if (m_stream != nullptr)
			{
				m_stream->close();
			}
		}
	}
}