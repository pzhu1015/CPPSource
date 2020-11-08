///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_CONFIGBASE_H
#define SYSTEM_KAFKA_CONFIGBASE_H
#include "System/Base/DllExport.h"
#include "System/Kafka/ConfigOption.h"
#include <string>
#include <map>
#include <vector>
namespace System
{
	namespace Kafka
	{
		template <typename Concrete>
		class ConfigBase {
		private:
			template <typename T>
			struct Type2Type { };
		public:
			/**
			* Sets a bool value
			*/
			Concrete& set(const std::string& name, bool value) {
				return proxy_set(name, value ? "true" : "false");
			}

			/**
			* Sets a value of any integral value
			*/
			template <typename T,
				typename = typename std::enable_if<std::is_integral<T>::value>::type>
				Concrete& set(const std::string& name, T value) {
				return proxy_set(name, std::to_string(value));
			}

			/**
			* Sets a cstring value
			*/
			Concrete& set(const std::string& name, const char* value) {
				return proxy_set(name, value);
			}

			/**
			* Sets a list of options
			*/
			Concrete& set(const std::vector<ConfigOption>& options) {
				for (const auto& option : options) {
					proxy_set(option.get_key(), option.get_value());
				}
				return static_cast<Concrete&>(*this);
			}

			/**
			* \brief Gets a value, converting it to the given type.
			*
			* If the configuration option is not found, then ConfigOptionNotFound is thrown.
			*
			* If the configuration value can't be converted to the given type, then
			* InvalidConfigOptionType is thrown.
			*
			* Valid conversion types:
			* * std::string
			* * bool
			* * int
			*/
			template <typename T>
			T get(const std::string& name) const {
				std::string value = static_cast<const Concrete&>(*this).get(name);
				return convert(value, Type2Type<T>());
			}
		protected:
			static std::map<std::string, std::string> parse_dump(const char** values, size_t count) {
				std::map<std::string, std::string> output;
				for (size_t i = 0; i < count; i += 2) {
					output[values[i]] = values[i + 1];
				}
				return output;
			}
		private:
			Concrete& proxy_set(const std::string& name, const std::string& value) {
				return static_cast<Concrete&>(*this).set(name, value);
			}

			static std::string convert(const std::string& value, Type2Type<std::string>) {
				return value;
			}

			static bool convert(const std::string& value, Type2Type<bool>) {
				if (value == "true") {
					return true;
				}
				else if (value == "false") {
					return false;
				}
				else {
					throw InvalidConfigOptionType(value, "bool");
				}
			}

			static int convert(const std::string& value, Type2Type<int>) {
				try {
					return std::stoi(value);
				}
				catch (std::exception&) {
					throw InvalidConfigOptionType(value, "int");
				}
			}
		};
	}
}
#endif // !SYSTEM_KAFKA_CONFIGBASE_H
