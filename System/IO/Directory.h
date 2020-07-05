///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_IO_DIRECTORY_H
#define SYSTEM_IO_DIRECTORY_H

#include "System/DllExport.h"
#include <string>
#include <vector>

namespace System
{
	namespace DateTimes
	{
		class DateTime;
	}
	namespace IO
	{
		class DirectoryInfo;
		class SYSTEM_API Directory
		{
		public:
			static void CreateDirectory(const std::string &path);
			static void Delete(const std::string &path);
			static void Delete(const std::string &path, bool recurse);
			static bool Exists(const std::string &path);
			static void Move(const std::string &src_path, const std::string &dest_path);
			static std::vector<std::string> GetFiles(const std::string &path);
			static std::vector<std::string> GetDirectories(const std::string &path);
			static DateTimes::DateTime* GetCreationTime(const std::string &path);
			static DateTimes::DateTime* GetLastAccessTime(const std::string &path);
			static DateTimes::DateTime* GetLastWriteTime(const std::string &path);
			static DirectoryInfo* GetParent(const std::string &path);
			static std::string GetDirectoryRoot(const std::string &path);

		};
	}
}

#endif //!SYSTEM_IO_DIRECTORY_H
