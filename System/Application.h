///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_APPLICATION_H
#define SYSTEM_APPLICATION_H

#include "System/DllExport.h"
#include <string>

namespace System
{
	class SYSTEM_API Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		static std::string GetCompanyName();
		static std::string GetProductName();
		static std::string GetProductVersion();
		static std::string GetStartupPath();
		static std::string GetExecutablePath();
		static std::string GetAbsolutePath(const std::string &path);
		static void Exit();
		static void ExitThread();
	private:
		static std::string sm_company_name;
		static std::string sm_product_name;
		static std::string sm_product_version;

		static std::string sm_startup_path;
		static std::string sm_executable_path;
	};
}

#endif // !SYSTEM_APPLICATION_H
