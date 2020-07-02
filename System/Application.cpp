///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Application.h"
#include <direct.h>

namespace System
{
	std::string Application::sm_company_name = "";
	std::string Application::sm_product_name = "";
	std::string Application::sm_product_version = "";
	std::string Application::sm_startup_path = "";
	std::string Application::sm_executable_path = "";

	std::string Application::GetCompanyName()
	{
		return std::string();
	}
	std::string Application::GetProductName()
	{
		return std::string();
	}
	std::string Application::GetProductVersion()
	{
		return std::string();
	}
	std::string Application::GetStartupPath()
	{
		if (sm_startup_path.empty())
		{
			char buff[256];
			_getcwd(buff, sizeof(buff));
			sm_startup_path = buff;
		}
		return sm_startup_path;
	}
	std::string Application::GetExecutablePath()
	{
		return std::string();
	}
	void Application::Exit()
	{
		exit(0);
	}
	void Application::ExitThread()
	{
	}
}
