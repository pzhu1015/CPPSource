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
		DateTimes::DateTime * FileSystemInfo::GetCreationTime()
		{
			return nullptr;
		}
		DateTimes::DateTime * FileSystemInfo::GetLastAccessTime()
		{
			return nullptr;
		}
		DateTimes::DateTime * FileSystemInfo::GetLastWriteTime()
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