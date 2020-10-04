///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/FileInfo.h"
#include "System/IO/File.h"
#include "System/IO/DirectoryInfo.h"
#include "System/IO/FileStream.h"
#include "System/Applications/Application.h"
#include <sys/stat.h>

namespace System
{
	namespace IO
	{
		FileInfo::FileInfo(const std::string & filename)
		{
			m_originalpath = filename;
			m_fullpath = Application::GetAbsolutePath(filename);
#ifdef _WIN32
			_stat(m_fullpath.c_str(), &m_stat);
			m_name = m_fullpath.substr(m_fullpath.find_last_of('\\') + 1);
			m_dirname = m_fullpath.substr(0, m_fullpath.find_last_of('\\'));
			
#else
			struct stat st;
			stat(m_fullpath.c_str(), &m_stat);
			m_name = m_fullpath.substr(m_fullpath.find_last_of('/') + 1);
			m_dirname = m_fullpath.substr(0, m_fullpath.find_last_of('/'));
#endif
			m_length = m_stat.st_size;
			m_exists = File::Exists(m_fullpath);
		}
		FileInfo::~FileInfo()
		{
		}
		DirectoryInfo FileInfo::GetDirectory() const
		{
			return DirectoryInfo(m_dirname);
		}
		std::string FileInfo::GetDirectoryName() const
		{
			return m_dirname;
		}
		bool FileInfo::GetExists() const
		{
			return m_exists;
		}

		int64_t FileInfo::GetLength() const
		{
			return m_length;
		}
		std::string FileInfo::GetName() const
		{
			return m_name;
		}
		FileInfo FileInfo::CopyTo(const std::string & dest)
		{
			File::Copy(m_fullpath, dest);
			return FileInfo(dest);
		}
		FileInfo FileInfo::CopyTo(const std::string & dest, bool overwrite)
		{
			File::Copy(m_fullpath, dest, overwrite);
			return FileInfo(dest);
		}
		FileStreamPtr FileInfo::Create()
		{
			return std::make_shared<FileStream>(m_fullpath, FileMode::OpenOrCreate, FileAccess::ReadWrite);
		}
		void FileInfo::Delete() const
		{
			File::Delete(m_fullpath);
		}
		void FileInfo::MoveTo(const std::string & dest)
		{
			File::Move(m_fullpath, dest);
		}
	}

}