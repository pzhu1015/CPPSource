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
#include "System/IO/FileSystemInfo.h"
#include "System/IO/Ptrs.h"
#include <string>
#include <vector>

namespace System
{
	namespace IO
	{
		class SYSTEM_API DirectoryInfo : public FileSystemInfo
		{
		public:
			DirectoryInfo(const std::string &dirname);
			virtual ~DirectoryInfo();
			
			DirectoryInfoPtr Parent() const;
			DirectoryInfoPtr Root() const;
			void Create();
			std::vector<DirectoryInfoPtr> GetDirectories();
			std::vector<FileInfoPtr> GetFiles();
			void MoveTo(const std::string &dest);
			DirectoryInfoPtr CreateSubDirectory(const std::string &path);

			virtual std::string GetName() const override;
			virtual bool GetExists() const override;
			virtual void Delete() const override;
			void Delete(bool recursive);
		};
	}
}

#endif //!SYSTEM_IO_DIRECTORYINFO_H
