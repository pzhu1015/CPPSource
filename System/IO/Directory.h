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
	namespace IO
	{
		class SYSTEM_API Directory
		{
		public:
			Directory() = default;
			Directory(const std::string &path);
			~Directory() = default;
			static void CreateDirectory(const std::string &path);
			static void Delete(const std::string &path, bool recurse = false);
			static bool Exists(const std::string &path);
			static void Move(const std::string &src_path, const std::string &dest_path);
			static std::vector<std::string> GetFiles(const std::string &path);
			static std::vector<std::string> GetDirectories(const std::string &path);
		};
	}
}

#endif //!SYSTEM_IO_DIRECTORY_H
