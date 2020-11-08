///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/ConfigOption.h"
namespace System
{
	namespace Kafka
	{
		ConfigOption::ConfigOption(const std::string& key, const std::string& value)
			: key_(key), value_(value) {

		}

		ConfigOption::ConfigOption(const std::string& key, const char* value)
			: key_(key), value_(value) {

		}

		ConfigOption::ConfigOption(const std::string& key, bool value)
			: key_(key), value_(value ? "true" : "false") {

		}

		const std::string& ConfigOption::get_key() const {
			return key_;
		}

		const std::string& ConfigOption::get_value() const {
			return value_;
		}
	}
}