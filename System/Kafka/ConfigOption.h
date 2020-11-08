///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_CONFIGOPTION_H
#define SYSTEM_KAFKA_CONFIGOPTION_H
#include "System/Base/DllExport.h"
#include <string>
#include <type_traits>
namespace System
{
	namespace Kafka
	{
		class SYSTEM_API ConfigOption
		{
		public:
			/**
			* Construct using a std::string value
			*/
			ConfigOption(const std::string& key, const std::string& value);

			/**
			* Construct using a const char* value
			*/
			ConfigOption(const std::string& key, const char* value);

			/**
			* Construct using a bool value
			*/
			ConfigOption(const std::string& key, bool value);

			/**
			* Construct using any integral value
			*/
			template <typename T,
				typename = typename std::enable_if<std::is_integral<T>::value>::type>
				ConfigOption(const std::string& key, T value)
				: ConfigOption(key, std::to_string(value)) {

			}

			/**
			* Gets the key
			*/
			const std::string& get_key() const;

			/**
			* Gets the value
			*/
			const std::string& get_value() const;
		private:
			std::string key_;
			std::string value_;
		};
	}
}
#endif // !SYSTEM_KAFKA_CONFIGOPTION_H
