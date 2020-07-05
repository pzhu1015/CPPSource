///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_IO_FILEINFO_H
#define SYSTEM_IO_FILEINFO_H

#include "System/DllExport.h"
#include "System/IO/FileSystemInfo.h"

#include <string>

namespace System
{
	namespace IO
	{
		class FileStream;
		class DirectoryInfo;
		class SYSTEM_API FileInfo : public FileSystemInfo
		{
		public:
			FileInfo(const std::string &filename);
			virtual ~FileInfo();

			DirectoryInfo* GetDirectory() const;
			std::string GetDirectoryName() const;
			
			int64_t GetLength() const;
			
			FileInfo* CopyTo(const std::string &dest);
			FileInfo* CopyTo(const std::string &dest, bool overwrite);
			FileStream* Create();
			
			void MoveTo(const std::string &dest);

			virtual std::string GetName() const override;
			virtual bool GetExists() const override;
			virtual void Delete() const override;
		private:
			std::string m_dirname;
			int64_t m_length;
		};
	}
}

#endif //!SYSTEM_IO_FILEINFO_H
