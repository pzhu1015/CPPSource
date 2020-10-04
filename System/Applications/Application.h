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
#include "System/Base/DllExport.h"
#include "System/Configurations/Ptrs.h"
#include <string>
using namespace System::Configurations;
namespace System
{
	class SYSTEM_API Application final
	{
	public:
		static Application& GetInstance()
		{
			static Application instance;
			return instance;
		}
		bool Start(const std::string &name);
		bool Stop();
		const std::string& GetCompanyName() const;
		const std::string& GetProductName() const;
		const std::string& GetProductVersion() const;
		const std::string& GetStartupPath() const;
		const std::string& GetExecutablePath() const;
		const std::string& GetLogPath() const;
		const ConfigurationPtr GetConfiguration() const;
		void Exit();
		void ExitThread();
		static std::string GetAbsolutePath(const std::string &path);
	private:
		Application() = default;
		ConfigurationPtr m_app_config;
		std::string m_company_name;
		std::string m_product_name;
		std::string m_product_version;
		std::string m_startup_path;
		std::string m_executable_path;
		std::string m_log_path;
	};
}

#endif // !SYSTEM_APPLICATION_H
