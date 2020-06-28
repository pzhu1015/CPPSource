///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_IO_DIRECTORYINFO_H
#define SYSTEM_IO_DIRECTORYINFO_H

#include "System/DllExport.h"
#include "System/FileInfo.h"
#include <string>
#include <vector>

namespace System
{
	namespace IO
	{
		class SYSTEM_API DirectoryInfo
		{
		public:
			DirectoryInfo(const std::string &dirname);
			~DirectoryInfo();
			bool Exists() const;
			std::string Name() const;
			std::string Parent() const;
			std::string Root() const;
			void Create();
			void Delete(bool recursive = false);
			std::vector<DirectoryInfo> GetDirectories();
			std::vector<FileInfo> GetFiles();
			void MoveTo(const std::string &dest);
			DirectoryInfo CreateSubDirectory(const std::string &path);
		};
	}
}

#endif //!SYSTEM_IO_DIRECTORYINFO_H
