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
			
		}

		FileStream::FileStream(const std::string & filename, FileMode mode, FileAccess access)
		{
			
		}

		FileStream::~FileStream()
		{
		}

		bool FileStream::GetCanRead() const
		{
			if (m_access == FileAccess::Read || m_access == FileAccess::ReadWrite)
			{
				return true;
			}
			return false;
		}

		bool FileStream::GetCanSeek() const
		{
			return true;
		}

		bool FileStream::GetCanWrite() const
		{
			if (m_access == FileAccess::Write || m_access == FileAccess::ReadWrite)
			{
				return true;
			}
			return false;
		}

		int64_t FileStream::GetLength() const
		{
			return int64_t();
		}

		int64_t FileStream::GetPosition() const
		{
			return -1;
		}

		void FileStream::Flush()
		{
		}

		void FileStream::Flush(bool flushToDisk)
		{
		}

		int FileStream::Read(char * buffer, int offset, int count)
		{
			if (GetCanRead())
			{
				m_istream->seekg(offset);
				m_istream->read(buffer, count);
				return (int)m_istream->gcount();
			}
			return -1;
		}

		int FileStream::ReadByte()
		{
			if (GetCanRead())
			{
				return m_istream->get();
			}
			return -1;
		}

		int64_t FileStream::Seek(int64_t offset, SeekOrigin origin)
		{
			return -1;
		}

		void FileStream::SetLength(int64_t value)
		{
		}

		void FileStream::Write(char * buffer, int offset, int count)
		{
			if (GetCanWrite())
			{
				m_ostream->seekp(offset);
				m_ostream->write(buffer, count);
			}
		}

		void FileStream::WriteByte(char value)
		{
			if (GetCanWrite())
			{
				m_ostream->put(value);
			}
		}

		void FileStream::Dispose()
		{
		}

		void FileStream::Dispose(bool disposing)
		{
		}

		void FileStream::Lock(int64_t position, int64_t length)
		{
		}

		void FileStream::UnLock(int64_t position, int64_t length)
		{
		}
	}
}