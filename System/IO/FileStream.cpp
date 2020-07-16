///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/FileStream.h"
#include "System/IO/File.h"

namespace System
{
	namespace IO
	{
		FileStream::FileStream(const std::string & filename, FileMode mode)
		{
			m_mode = mode;
			int m = -1;
			if (mode == FileMode::Create)
			{
				//文件存在，覆盖
				m = std::ios::out | std::ios::binary;
				m_access = FileAccess::Write;
			}
			else if (mode == FileMode::CreateNew)
			{
				//文件存在，异常
				if (File::Exists(filename))
				{
					throw "create new a file, but file is exists";
				}
				m = std::ios::out | std::ios::binary;
				m_access = FileAccess::Write;
			}
			else if (mode == FileMode::Open)
			{
				//打开现有文件
				m = std::ios::in | std::ios::out | std::ios::binary;
				m_access = FileAccess::ReadWrite;
			}
			else if (mode == FileMode::OpenOrCreate)
			{
				//打开现有文件，如果文件不存在创建新文件
				if (!File::Exists(filename))
				{
					m = std::ios::in | std::ios::binary;
					m_access = FileAccess::Write;
				}
				else
				{
					m = std::ios::in | std::ios::out | std::ios::binary;
					m_access = FileAccess::ReadWrite;
				}
			}
			else if (mode == FileMode::Truncate)
			{
				//打开现有文件，并清空文件内容
				m = std::ios::in | std::ios::trunc | std::ios::binary;
				m_access = FileAccess::Write;
			}
			else if (mode == FileMode::Append)
			{
				//打开现有文件，并向文件末尾追加内容
				m = std::ios::in | std::ios::app | std::ios::binary;
				m_access = FileAccess::Write;
			}
			else
			{
				//nothing
			}
			m_iostream = new std::fstream(filename.c_str(), m);
		}

		FileStream::FileStream(const std::string & filename, FileMode mode, FileAccess access)
		{
			m_mode = mode;
			m_access = access;
			int m = -1;
			if (mode == FileMode::Create)
			{
				//文件存在，覆盖
				m = std::ios::out | std::ios::binary;
			}
			else if (mode == FileMode::CreateNew)
			{
				//文件存在，异常
				if (File::Exists(filename))
				{
					throw "create new a file, but file is exists";
				}
				m = std::ios::out | std::ios::binary;
			}
			else if (mode == FileMode::Open)
			{
				//打开现有文件
				m = std::ios::in | std::ios::out | std::ios::binary;
			}
			else if (mode == FileMode::OpenOrCreate)
			{
				//打开现有文件，如果文件不存在创建新文件
				if (!File::Exists(filename))
				{
					m = std::ios::in | std::ios::binary;
				}
				else
				{
					m = std::ios::in | std::ios::out | std::ios::binary;
				}
			}
			else if (mode == FileMode::Truncate)
			{
				//打开现有文件，并清空文件内容
				m = std::ios::in | std::ios::trunc | std::ios::binary;
			}
			else if (mode == FileMode::Append)
			{
				//打开现有文件，并向文件末尾追加内容
				m = std::ios::in | std::ios::app | std::ios::binary;
			}
			else
			{
				//nothing
			}
			m_iostream = new std::fstream(filename.c_str(), m);
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
			if (GetCanRead())
			{
				if (m_iostream != nullptr)
				{
					return m_iostream->tellg();
				}
				return -1;
			}
			else
			{
				if (m_iostream != nullptr)
				{
					return m_iostream->tellp();
				}
				return -1;
			}
		}

		void FileStream::SetPosition(int64_t pos)
		{
		}

		void FileStream::Flush()
		{
			if (m_iostream != nullptr)
			{
				m_iostream->flush();
			}
		}

		void FileStream::Flush(bool flushToDisk)
		{
			if (flushToDisk)
			{
				Flush();
			}
		}

		int FileStream::Read(char * buffer, int offset, int count)
		{
			if (GetCanRead() && m_iostream != nullptr)
			{
				m_iostream->seekg(offset);
				m_iostream->read(buffer, count);
				return (int)m_iostream->gcount();
			}
			return -1;
		}

		int FileStream::ReadByte()
		{
			if (GetCanRead() && m_iostream != nullptr)
			{
				return m_iostream->get();
			}
			return -1;
		}

		int64_t FileStream::Seek(int64_t offset, SeekOrigin origin)
		{
			if (GetCanRead())
			{
				if (m_iostream != nullptr)
				{
					m_iostream->seekg(offset, (int)origin);
					return m_iostream->tellg();
				}
				return -1;
			}
			else
			{
				if (m_iostream != nullptr)
				{
					m_iostream->seekp(offset, (int)origin);
					return m_iostream->tellp();
				}
				return -1;
			}
		}

		void FileStream::SetLength(int64_t value)
		{
		}

		void FileStream::Write(char * buffer, int offset, int count)
		{
			if (GetCanWrite() && m_iostream != nullptr)
			{
				m_iostream->seekp(offset);
				m_iostream->write(buffer, count);
			}
		}

		void FileStream::WriteByte(char value)
		{
			if (GetCanWrite() && m_iostream != nullptr)
			{
				m_iostream->put(value);
			}
		}

		void FileStream::Dispose(bool disposing)
		{
			if (disposing)
			{
				Stream::Dispose();
			}
		}

		void FileStream::Lock(int64_t position, int64_t length)
		{
		}

		void FileStream::UnLock(int64_t position, int64_t length)
		{
		}
	}
}