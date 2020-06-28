///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Directory.h"

namespace System
{
	namespace IO
	{
		Directory::Directory(const std::string & path)
		{
		}
		void Directory::CreateDirectory(const std::string & path)
		{
		}
		void Directory::Delete(const std::string & path, bool recurse)
		{
		}
		bool Directory::Exists(const std::string & path)
		{
			return false;
		}
		void Directory::Move(const std::string & src_path, const std::string & dest_path)
		{
		}
		std::vector<std::string> Directory::GetFiles(const std::string & path)
		{
			return std::vector<std::string>();
		}
		std::vector<std::string> Directory::GetDirectories(const std::string & path)
		{
			return std::vector<std::string>();
		}
	}
}
