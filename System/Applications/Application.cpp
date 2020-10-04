///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Applications/Application.h"
#include "System/Configurations/Configuration.h"
#include "System/IO/FileInfo.h"
#include <direct.h>
using namespace System::IO;
namespace System
{
	bool Application::Start(const std::string & name)
	{
		if (m_startup_path.empty())
		{
			char buff[256];
			_getcwd(buff, sizeof(buff));
			m_startup_path = GetAbsolutePath(buff);
		}

		FileInfo info(m_startup_path);

		if (m_app_config == nullptr)
		{
			m_app_config = std::make_shared<Configuration>();
			std::string config_filename;
			config_filename.append(info.GetDirectoryName());
			config_filename.append("\\");
			config_filename.append(name);
			bool rslt = m_app_config->Open(config_filename);
			if (!rslt)
			{
				return false;
			}
		}

		if (m_product_version.empty())
		{
		}

		if (m_company_name.empty())
		{

		}

		if (m_product_name.empty())
		{

		}

		if (m_log_path.empty())
		{
			m_log_path = m_app_config->GetValue("Log", "LogDir", "Log");
			m_log_path = GetAbsolutePath(m_log_path);
		}

		return true;
	}

	bool Application::Stop()
	{
		return false;
	}

	const std::string& Application::GetCompanyName() const
	{
		assert(!m_company_name.empty());
		return m_company_name;
	}

	const std::string& Application::GetProductName() const
	{
		assert(!m_product_name.empty());
		return m_product_name;
	}

	const std::string& Application::GetProductVersion() const
	{
		assert(!m_product_version.empty());
		return m_product_version;
	}

	const std::string& Application::GetStartupPath() const
	{
		assert(!m_startup_path.empty());
		return m_startup_path;
	}

	const std::string& Application::GetExecutablePath() const
	{
		assert(!m_executable_path.empty());
		return m_executable_path;
	}

	const std::string & Application::GetLogPath() const
	{
		assert(!m_log_path.empty());
		return m_log_path;
	}

	const ConfigurationPtr Application::GetConfiguration() const
	{
		return m_app_config;
	}

	std::string Application::GetAbsolutePath(const std::string & path)
	{
#ifdef _WIN32
#define MAX_PATH 4096
		char resolved_path[MAX_PATH] = { 0 };
		_fullpath(resolved_path, path.c_str(), MAX_PATH);
#else
#define max_path 40960
		char resolved_path[max_path] = { 0 };
		realpath(path.c_str(), resolved_path);
#endif
		return std::string(resolved_path);
	}

	void Application::Exit()
	{
		exit(0);
	}

	void Application::ExitThread()
	{
	}
}
