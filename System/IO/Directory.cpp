///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/Directory.h"
#include "System/IO/DirectoryInfo.h"
#include "System/DateTimes/DateTime.h"

#ifdef _WIN32
#include <io.h>
#include <sys/stat.h>
#include <direct.h>
#else
#include <unistd.h>
#endif

using namespace System::DateTimes;

namespace System
{
	namespace IO
	{
		void Directory::CreateDirectory(const std::string & path)
		{
			if (!Directory::Exists(path))
			{
				mkdir(path.c_str());
			}
		}

		void Directory::Delete(const std::string & path)
		{
			if (Directory::Exists(path))
			{
				rmdir(path.c_str());
			}
		}

		void Directory::Delete(const std::string & path, bool recurse)
		{
		}

		bool Directory::Exists(const std::string & path)
		{
			return (access(path.c_str(), 0) == 0);
		}

		void Directory::Move(const std::string & src_path, const std::string & dest_path)
		{
		}

		std::vector<std::string> Directory::GetFiles(const std::string & path)
		{
#ifdef _WIN32
			std::vector<std::string> files;
			int64_t hFile = 0;
			struct _finddata_t fileinfo;
			std::string p;
			if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
			{
				do 
				{
					if ((fileinfo.attrib & _A_NORMAL))
					{
						files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					}

				} while (_findnext(hFile, &fileinfo) == 0);
				_findclose(hFile);
			}
			return files;
#else

#endif
		}

		std::vector<std::string> Directory::GetDirectories(const std::string & path)
		{
#ifdef _WIN32
			std::vector<std::string> dirs;
			int64_t hFile = 0;
			struct _finddata_t fileinfo;
			std::string p;
			if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
			{
				do
				{
					if ((fileinfo.attrib & _A_SUBDIR))
					{
						dirs.push_back(p.assign(path).append("\\").append(fileinfo.name));
					}

				} while (_findnext(hFile, &fileinfo) == 0);
				_findclose(hFile);
			}
			return dirs;
#else

#endif
		}

		DateTimes::DateTime * Directory::GetCreationTime(const std::string & path)
		{
#ifdef _WIN32
			struct _stat st;
			_stat(path.c_str(), &st);
#else
			struct stat st;
			stat(path.c_str(), &st);
#endif
			DateTime* dt = new DateTime(st.st_ctime);
			return dt;
		}

		DateTimes::DateTime * Directory::GetLastAccessTime(const std::string & path)
		{
#ifdef _WIN32
			struct _stat st;
			_stat(path.c_str(), &st);
#else
			struct stat st;
			stat(path.c_str(), &st);
#endif
			DateTime* dt = new DateTime(st.st_atime);
			return dt;
		}

		DateTimes::DateTime * Directory::GetLastWriteTime(const std::string & path)
		{
#ifdef _WIN32
			struct _stat st;
			_stat(path.c_str(), &st);
#else
			struct stat st;
			stat(path.c_str(), &st);
#endif
			DateTime* dt = new DateTime(st.st_mtime);
			return dt;
		}

		DirectoryInfo * Directory::GetParent(const std::string & path)
		{
			std::string parent_path = path.substr(0, path.find_last_of('\\'));
			return new DirectoryInfo(parent_path);
		}

		std::string Directory::GetDirectoryRoot(const std::string & path)
		{
			return std::string();
		}
	}
}
