///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/FileSystemInfo.h"
#include "System/DateTimes/DateTime.h"

namespace System
{
	namespace IO
	{
		FileSystemInfo::FileSystemInfo()
		{
		}
		DateTime FileSystemInfo::GetCreationTime()
		{
			return DateTime(0);
		}
		DateTime FileSystemInfo::GetLastAccessTime()
		{
			return DateTime(0);
		}
		DateTime FileSystemInfo::GetLastWriteTime()
		{
			return DateTime(0);
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