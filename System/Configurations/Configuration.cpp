///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Configurations/Configuration.h"
#include "System/Kafka/ConfigOption.h"
namespace System
{
	namespace Configurations
	{
		Configuration::Configuration()
		{
		}
		Configuration::Configuration(const std::string & filename)
		{
			bool rslt = Open(filename);
			m_open = rslt;
		}
		Configuration::~Configuration()
		{
		}
		bool Configuration::Open(const std::string &filename)
		{
			m_config_file = std::make_shared<CSimpleIniA>();
			m_config_file->SetUnicode();
			SI_Error rc = m_config_file->LoadFile(filename.data());
			return rc == SI_OK;
		}
		std::string Configuration::GetValue(const std::string & section, const std::string & key, const std::string & dft_value)
		{
			if (!m_open) return dft_value;
			const char* v = m_config_file->GetValue(section.data(), key.data(), "");
			if (v == "")
			{
				return dft_value;
			}
			return std::string(v);
		}
		int Configuration::GetValue(const std::string & section, const std::string & key, int dft_value)
		{
			if (!m_open) return dft_value;
			const char* v = m_config_file->GetValue(section.data(), key.data(), "");
			if (v == "")
			{
				return dft_value;
			}
			return std::atoi(v);
		}
		int64_t Configuration::GetValue(const std::string & section, const std::string & key, int64_t dft_value)
		{
			if (!m_open) return dft_value;
			const char* v = m_config_file->GetValue(section.data(), key.data(), "");
			if (v == "")
			{
				return dft_value;
			}
			return std::atoll(v);
		}
		double Configuration::GetValue(const std::string & section, const std::string & key, double dft_value)
		{
			if (!m_open) return dft_value;
			return m_config_file->GetDoubleValue(section.data(), key.data(), dft_value);
		}
		std::vector<ConfigOption> Configuration::GetAllKeyValues(const std::string & section)
		{
			std::vector<ConfigOption> key_vals;
			if (!m_open) return key_vals;
			CSimpleIniA::TNamesDepend keys;
			m_config_file->GetAllKeys(section.data(), keys);
			for (auto itr : keys)
			{
				std::string key = itr.pItem;
				std::string value = GetValue(section, key, "");
				key_vals.push_back({key, value});
			}
			return std::move(key_vals);
		}
	}
}