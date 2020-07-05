///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_IO_FILE_H
#define SYSTEM_IO_FILE_H

#include "System/DllExport.h"
#include "System/IO/FileMode.h"
#include "System/IO/FileAccess.h"
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
		class FileStream;
		class Encoding;
		class SYSTEM_API File
		{
		public:
			static bool AppendAllLines(const std::string &path, std::vector<std::string> &lines);
			static bool AppendAllLines(const std::string &path, std::vector<std::string> &lines, Encoding* encoding);
			static bool AppendAllText(const std::string &path, std::string &contents);
			static bool AppendAllText(const std::string &path, std::string &contents, Encoding* encoding);
			static bool Copy(const std::string &src, const std::string &dest);
			static bool Copy(const std::string &src, const std::string &dest, const bool overwrite);
			static bool Delete(const std::string &path);
			static bool Exists(const std::string &path);
			static bool Move(const std::string &str, const std::string &dest);
			static FileStream* Open(const std::string &path, FileMode mode);
			static FileStream* Open(const std::string &path, FileMode mode, FileAccess access);
			static std::string ReadAllText(const std::string &path);
			static std::string ReadAllText(const std::string &path, Encoding* encoding);
			static bool WriteAllLines(const std::string &path, const std::vector<std::string> &lines);
			static bool WriteAllLines(const std::string &path, const std::vector<std::string> &lines, Encoding* encoding);
			static bool WriteAllText(const std::string &path, const std::string &contents);
			static bool WriteAllText(const std::string &path, const std::string &contents, Encoding* encoding);
			static bool ReadAllBytes(const std::string &path, char* bytes, size_t &length);
			static bool WriteAllBytes(const std::string &path, const char* bytes, const size_t &length);

			static std::vector<std::string> ReadAllLines(const std::string &path);
			static std::vector<std::string> ReadAllLines(const std::string &path, Encoding* encoding);

			static DateTimes::DateTime* GetCreationTime(const std::string &path);
			static DateTimes::DateTime* GetLastAccessTime(const std::string &path);
			static DateTimes::DateTime* GetLastWriteTime(const std::string &path);
		};
	}
}

#endif //!SYSTEM_IO_FILE_H