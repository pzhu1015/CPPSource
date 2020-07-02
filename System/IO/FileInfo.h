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
#include "System/IO/Directory.h"
#include "System/IO/FileStream.h"
#include <string>

namespace System
{
	namespace IO
	{
		class SYSTEM_API FileInfo
		{
		public:
			FileInfo() = default;
			FileInfo(const std::string &filename);
			~FileInfo();

			Directory Directory();
			std::string DirectoryName();
			bool Exists();
			bool IsReadOnly();
			int64_t Length();
			std::string Name();
			FileInfo CopyTo(const std::string &dest, bool overwrite = false);
			FileStream* Create();
			void Delete();
			void MoveTo(const std::string &dest);
		private:
			int64_t m_length;
			std::string m_name;
			std::string m_dir_name;
			bool m_is_readonly;
			bool m_exists;
		};
	}
}

#endif //!SYSTEM_IO_FILEINFO_H
