///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/FileInfo.h"
#include <sys/stat.h>

namespace System
{
	namespace IO
	{
		FileInfo::FileInfo(const std::string & filename)
		{
			struct _stat info;
			_stat(filename.c_str(), &info);
			m_length = info.st_size;
			size_t lsp = filename.find_last_of("\\") + 1;
			m_name = filename.substr(lsp, filename.length() - lsp);
			m_dir_name = filename.substr(0, lsp);
		}
		FileInfo::~FileInfo()
		{
		}
		Directory FileInfo::Directory()
		{
			System::IO::Directory dir;
			return dir;
		}
		std::string FileInfo::DirectoryName()
		{
			return m_dir_name;
		}
		bool FileInfo::Exists()
		{
			return m_exists;
		}
		bool FileInfo::IsReadOnly()
		{
			return m_is_readonly;
		}
		int64_t FileInfo::Length()
		{
			return m_length;
		}
		std::string FileInfo::Name()
		{
			return m_name;
		}
		FileInfo FileInfo::CopyTo(const std::string & dest, bool overwrite)
		{
			return FileInfo();
		}
		FileStream FileInfo::Create()
		{
			return FileStream();
		}
		void FileInfo::Delete()
		{
		}
		void FileInfo::MoveTo(const std::string & dest)
		{
		}
	}

}