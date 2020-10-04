///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_CONFIGURATIONS_CONFIGURATION_H
#define SYSTEM_CONFIGURATIONS_CONFIGURATION_H
#include "System/Base/DllExport.h"
#include "System/Configurations/SimpleIni.h"
#include <memory>
namespace System
{
	namespace Configurations
	{
		class SYSTEM_API Configuration
		{
		public:
			Configuration();
			Configuration(const std::string &filename);
			~Configuration();
			bool Open(const std::string &filename);
			std::string GetValue(const std::string &section, const std::string &key, const std::string &dft_value);
			int GetValue(const std::string &section, const std::string &key, int dft_value);
			int64_t GetValue(const std::string &section, const std::string &key, int64_t dft_value);
			double GetValue(const std::string &section, const std::string &key, double dft_value);
		private:
			bool m_open = false;
			std::shared_ptr<CSimpleIniA> m_config_file;
		};
	}
}
#endif // !SYSTEM_CONFIGURATIONS_CONFIGURATION_H
