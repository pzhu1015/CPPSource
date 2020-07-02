///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/File.h"
#include <fstream>
#include <ostream>

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

		std::string File::ReadAllText(const std::string & path, const Encoding & encoding)
		{
			return std::string();
		}

		bool File::WriteAllLines(const std::string & path, const std::vector<std::string>& lines)
		{
			return false;
		}

		bool File::WriteAllLines(const std::string & path, const std::vector<std::string>& lines, const Encoding & encoding)
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

		bool File::WriteAllText(const std::string & path, const std::string & contents, const Encoding & encoding)
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
		std::vector<std::string> File::ReadAllLines(const std::string & path, const Encoding & encoding)
		{
			return std::vector<std::string>();
		}
		bool File::AppendAllLines(const std::string & path, std::vector<std::string>& lines)
		{
			return false;
		}
		bool File::AppendAllLines(const std::string & path, std::vector<std::string>& lines, const Encoding & encoding)
		{
			return false;
		}
		bool File::AppendAllText(const std::string & path, std::string & contents)
		{
			return false;
		}
		bool File::AppendAllText(const std::string & path, std::string & contents, const Encoding & encoding)
		{
			return false;
		}
		bool File::Copy(const std::string & src, const std::string & dest)
		{
			return false;
		}
		bool File::Copy(const std::string & src, const std::string & dest, const bool overwrite)
		{
			return false;
		}
		bool File::Delete(const std::string & path)
		{
			return false;
		}
		bool File::Exists(const std::string & path)
		{
			return false;
		}
		bool File::Move(const std::string & str, const std::string & dest)
		{
			return false;
		}
		FileStream* File::Open(const std::string & path, const FileMode & mode)
		{
			return nullptr;
		}
		FileStream* File::Open(const std::string & path, const FileMode & mode, const FileAccess & access)
		{
			return nullptr;
		}
	}
}