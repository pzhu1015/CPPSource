///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/FileSystemInfo.h"

namespace System
{
	namespace IO
	{
		FileSystemInfo::FileSystemInfo()
		{
		}
		DateTimePtr FileSystemInfo::GetCreationTime()
		{
			return nullptr;
		}
		DateTimePtr FileSystemInfo::GetLastAccessTime()
		{
			return nullptr;
		}
		DateTimePtr FileSystemInfo::GetLastWriteTime()
		{
			return nullptr;
		}
		std::string FileSystemInfo::GetExtension()
		{
			return std::string();
		}
		void FileSystemInfo::Refresh()
		{
		}
	}
}