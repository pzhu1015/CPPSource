///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/DirectoryInfo.h"

namespace System
{
	namespace IO
	{
		DirectoryInfo::DirectoryInfo(const std::string & dirname)
		{
		}
		DirectoryInfo::~DirectoryInfo()
		{
		}
		bool DirectoryInfo::Exists() const
		{
			return false;
		}
		std::string DirectoryInfo::Name() const
		{
			return std::string();
		}
		std::string DirectoryInfo::Parent() const
		{
			return std::string();
		}
		std::string DirectoryInfo::Root() const
		{
			return std::string();
		}
		void DirectoryInfo::Create()
		{
		}
		void DirectoryInfo::Delete(bool recursive)
		{
		}
		std::vector<DirectoryInfo> DirectoryInfo::GetDirectories()
		{
			return std::vector<DirectoryInfo>();
		}
		std::vector<FileInfo> DirectoryInfo::GetFiles()
		{
			return std::vector<FileInfo>();
		}
		void DirectoryInfo::MoveTo(const std::string & dest)
		{
		}
		DirectoryInfo DirectoryInfo::CreateSubDirectory(const std::string & path)
		{
			return DirectoryInfo(path);
		}
	}
}