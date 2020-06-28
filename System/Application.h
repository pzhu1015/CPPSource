///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef System_Application_h
#define System_Application_h

#include "System/DllExport.h"
#include "System/Object.h"
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
	private:
		static std::string sm_company_name;
		static std::string sm_product_name;
		static std::string sm_product_version;

		static std::string sm_startup_path;
		static std::string sm_executable_path;
	};
}

#endif // !System_Application_h
