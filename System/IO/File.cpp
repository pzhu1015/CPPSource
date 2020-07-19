///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/File.h"
#include "System/DateTimes/DateTime.h"
#include "System/IO/FileStream.h"
#include "System/IO/Encoding.h"
#include <fstream>
#include <ostream>
#include <stdio.h>
#ifdef _WIN32
#include <io.h>
#include <sys/stat.h>
#else
#include <unistd.h>
#endif

namespace System
{
	namespace IO
	{
		std::string File::ReadAllText(const std::string & path)
		{
			std::fstream ifs(path);

			if (!ifs.is_open())
			{
				return "";
			}

			std::string contents;
			std::istreambuf_iterator<char>beg(ifs), end;
			contents.assign(beg, end);
			ifs.close();

			return contents;
		}

		std::string File::ReadAllText(const std::string & path, const EncodingPtr &encoding)
		{
			//TODO
			return std::string();
		}

		bool File::WriteAllLines(const std::string & path, const std::vector<std::string>& lines)
		{
			std::ofstream ofs(path);
			if (!ofs.is_open())
			{
				return false;
			}
			for (auto line : lines)
			{
				ofs << line << std::endl;
			}
			ofs.close();
			return true;
		}

		bool File::WriteAllLines(const std::string & path, const std::vector<std::string>& lines, const EncodingPtr &encoding)
		{
			return false;
		}

		bool File::WriteAllText(const std::string & path, const std::string & contents)
		{
			std::ofstream ofs(path);

			if (!ofs.is_open())
			{
				return false;
			}

			ofs << contents;
			ofs.close();

			return true;
		}

		bool File::WriteAllText(const std::string & path, const std::string & contents, const EncodingPtr &encoding)
		{
			return false;
		}

		bool File::ReadAllBytes(const std::string & path, char * bytes, size_t & length)
		{
			std::ifstream ifs(path);

			if (!ifs.is_open())
			{
				return false;
			}

			ifs.read(bytes, length);
			ifs.close();

			return true;
		}

		bool File::WriteAllBytes(const std::string & path, const char * bytes, const size_t &length)
		{
			std::ofstream ofs(path);

			if (!ofs.is_open())
			{
				return false;
			}

			ofs.write(bytes, length);
			ofs.close();

			return true;
		}

		std::vector<std::string> File::ReadAllLines(const std::string & path)
		{
			std::ifstream ifs(path);

			if (!ifs.is_open())
			{
				return std::vector<std::string>();
			}

			std::vector<std::string> lines;
			std::string str = ("");
			while (!ifs.eof())
			{
				std::getline(ifs, str);
				lines.push_back(str);
			}
			ifs.close();

			return lines;
		}

		std::vector<std::string> File::ReadAllLines(const std::string & path, const EncodingPtr &encoding)
		{
			return std::vector<std::string>();
		}

		DateTimePtr File::GetCreationTime(const std::string & path)
		{
#ifdef _WIN32
			struct _stat st;
			_stat(path.c_str(), &st);
#else
			struct stat st;
			stat(path.c_str(), &st);
#endif
			DateTimePtr dt = std::make_shared<DateTime>(st.st_ctime);
			return dt;
		}

		DateTimePtr File::GetLastAccessTime(const std::string & path)
		{
#ifdef _WIN32
			struct _stat info;
			_stat(path.c_str(), &info);
#else
			struct stat info;
			stat(path.c_str(), &info);
#endif
			DateTimePtr dt = std::make_shared<DateTime>(info.st_atime);
			return dt;
		}

		DateTimePtr File::GetLastWriteTime(const std::string & path)
		{
#ifdef _WIN32
			struct _stat info;
			_stat(path.c_str(), &info);
#else
			struct stat info;
			stat(path.c_str(), &info);
#endif
			DateTimePtr dt = std::make_shared<DateTime>(info.st_mtime);
			return dt;
		}

		bool File::AppendAllLines(const std::string & path, std::vector<std::string>& lines)
		{
			std::ofstream ofs(path, std::ios::app);
			if (!ofs.is_open())
			{
				return false;
			}
			for (auto line : lines)
			{
				ofs << line << std::endl;
			}
			ofs.close();
			return false;
		}

		bool File::AppendAllLines(const std::string & path, std::vector<std::string>& lines, const EncodingPtr &encoding)
		{
			return false;
		}

		bool File::AppendAllText(const std::string & path, std::string & contents)
		{
			std::ofstream ofs(path, std::ios::app);
			if (!ofs.is_open())
			{
				return false;
			}
			ofs << contents;
			ofs.close();
			return true;
		}

		bool File::AppendAllText(const std::string & path, std::string & contents, const EncodingPtr &encoding)
		{
			//TODO
			return false;
		}

		bool File::Copy(const std::string & src, const std::string & dest)
		{
			std::ifstream ifs(src.c_str(), std::ios::in | std::ios::binary);
			if (!ifs)
			{
				return false;
			}
			std::ofstream ofs(dest.c_str(), std::ios::out | std::ios::binary);
			if (!ofs)
			{
				return false;
			}
			ofs << ifs.rdbuf();
			ifs.close();
			ofs.close();
			return true;
		}

		bool File::Copy(const std::string & src, const std::string & dest, const bool overwrite)
		{
			if (overwrite)
			{
				return File::Copy(src, dest);
			}
			else
			{
				if (File::Exists(dest))
				{
					return false;
				}
				else
				{
					return File::Copy(src, dest);
				}
			}
			return false;
		}

		bool File::Delete(const std::string & path)
		{
			if (File::Exists(path))
			{
				if (remove(path.c_str()) == 0)
				{
					return false;
				}
			}
			return true;
		}

		bool File::Exists(const std::string & path)
		{
			return (access(path.c_str(), 0) == 0);
		}

		bool File::Move(const std::string & src, const std::string & dest)
		{
			if (!File::Exists(src))
			{
				return false;
			}
			if (rename(src.c_str(), dest.c_str()) == 0)
			{
				return false;
			}
			return true;
		}

		FileStreamPtr File::Open(const std::string & path, FileMode mode)
		{
			return std::make_shared<FileStream>(path, mode);
		}

		FileStreamPtr File::Open(const std::string & path, FileMode mode, FileAccess access)
		{
			return std::make_shared<FileStream>(path, mode, access);
		}
	}
}