///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/IO/DirectoryInfo.h"
#include "System/IO/FileInfo.h"
#include "System/IO/File.h"
#include "System/IO/Directory.h"
#include "System/Applications/Application.h"

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include<unistd.h>
#endif


namespace System
{
	namespace IO
	{
		DirectoryInfo::DirectoryInfo(const std::string & dirname)
		{
			m_originalpath = dirname;
			m_fullpath = Application::GetAbsolutePath(dirname);
#ifdef _WIN32
			_stat(m_fullpath.c_str(), &m_stat);
			m_name = m_fullpath.substr(m_fullpath.find_last_of('\\') + 1);
#else
			struct stat st;
			stat(m_fullpath.c_str(), &m_stat);
			m_name = m_fullpath.substr(m_fullpath.find_last_of('/') + 1);
#endif
			m_exists = File::Exists(m_fullpath);
		}

		DirectoryInfo::~DirectoryInfo()
		{
		}

		bool DirectoryInfo::GetExists() const
		{
			return m_exists;
		}

		void DirectoryInfo::Delete() const
		{
			Directory::Delete(m_fullpath);
		}

		std::string DirectoryInfo::GetName() const
		{
			return m_name;
		}

		DirectoryInfo DirectoryInfo::Parent() const
		{
			return Directory::GetParent(m_fullpath);
		}

		DirectoryInfo DirectoryInfo::Root() const
		{
			return DirectoryInfo(Directory::GetDirectoryRoot(m_fullpath));
		}

		void DirectoryInfo::Create()
		{
			Directory::CreateDirectory(m_fullpath);
		}

		void DirectoryInfo::Delete(bool recursive)
		{
			Directory::Delete(m_fullpath, recursive);
		}

		std::vector<DirectoryInfo> DirectoryInfo::GetDirectories()
		{
			auto dirnames = Directory::GetDirectories(m_fullpath);
			std::vector<DirectoryInfo> dirinfos;
			for (auto dirname : dirnames)
			{
				dirinfos.push_back(DirectoryInfo(dirname));
			}
			return dirinfos;
		}

		std::vector<FileInfo> DirectoryInfo::GetFiles()
		{
			auto filenames = Directory::GetFiles(m_fullpath);
			std::vector<FileInfo> fileinfos;
			for (auto filename : filenames)
			{
				fileinfos.push_back(FileInfo(filename));
			}
			return fileinfos;
		}

		void DirectoryInfo::MoveTo(const std::string & dest)
		{
			Directory::Move(m_fullpath, dest);
		}

		DirectoryInfo DirectoryInfo::CreateSubDirectory(const std::string & path)
		{
			std::string fullpath = m_fullpath;
#ifdef _WIN32
			fullpath.append("\\");
#else
			fullpath.append("/");
#endif
			fullpath.append(fullpath);
			Directory::CreateDirectory(fullpath);
			return DirectoryInfo(fullpath);
		}
	}
}