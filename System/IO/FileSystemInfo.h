///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_IO_FILESYSTEMINFO_H
#define SYSTEM_IO_FILESYSTEMINFO_H
#include "System/DllExport.h"
#include "System/DateTimes/Ptrs.h"
#include <string>

using namespace System::DateTimes;
namespace System
{
	namespace IO
	{
		class SYSTEM_API FileSystemInfo
		{
		protected:
			FileSystemInfo();
		public:
			DateTimePtr GetCreationTime();
			DateTimePtr GetLastAccessTime();
			DateTimePtr GetLastWriteTime();

			std::string GetExtension();
			void Refresh();
			virtual bool GetExists() const = 0;
			virtual std::string GetName() const = 0;
			virtual void Delete() const = 0;
		protected:
			std::string m_fullpath;
			std::string m_originalpath;
			std::string m_name;
			bool m_exists = false;
#ifdef _WIN32
			struct _stat m_stat;
#else
			struct stat m_stat;
#endif
		};
	}
}

#endif // !SYSTEM_IO_FILESYSTEMINFO_H
