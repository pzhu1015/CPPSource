///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFAK_EXCEPTIONS_H
#define SYSTEM_KAFAK_EXCEPTIONS_H
#include "System/Exceptions/Exception.h"
#include "System/Kafka/Error.h"
using namespace System::Exceptions;
namespace System
{
	namespace Kafka
	{
		/**
		* A configuration related error
		*/
		class SYSTEM_API ConfigException : public Exception {
		public:
			ConfigException(const std::string& config_name, const std::string& error)
				:
				Exception("Failed to set " + config_name + ": " + error, TYPE_NAME)
			{

			}
		};

		/**
		* Indicates a configuration option was not set
		*/
		class SYSTEM_API ConfigOptionNotFound : public Exception {
		public:
			ConfigOptionNotFound(const std::string& config_name)
				:
				Exception(config_name + " not found", TYPE_NAME)
			{

			}
		};

		/**
		* Indicates a configuration option value could not be converted to a specified type
		*/
		class SYSTEM_API InvalidConfigOptionType : public Exception {
		public:
			InvalidConfigOptionType(const std::string& config_name, const std::string& type)
				:
				Exception(config_name + " could not be converted to " + type, TYPE_NAME)
			{

			}
		};

		/**
		* Indicates something that was being looked up failed to be found
		*/
		class SYSTEM_API ElementNotFound : public Exception {
		public:
			ElementNotFound(const std::string& element_type, const std::string& name)
				:
				Exception("Could not find " + element_type + " for " + name, TYPE_NAME)
			{

			}
		};

		/**
		* Indicates something that was incorrectly parsed
		*/
		class SYSTEM_API ParseException : public Exception {
		public:
			ParseException(const std::string& message)
				:
				Exception(message, TYPE_NAME)
			{

			}
		};

		/**
		* Indicates something had an unexpected versiom
		*/
		class SYSTEM_API UnexpectedVersion : public Exception {
		public:
			UnexpectedVersion(uint32_t version)
				:
				Exception("Unexpected version " + std::to_string(version), TYPE_NAME)
			{

			}
		};

		/**
		* A generic rdkafka handle error
		*/
		class SYSTEM_API HandleException : public Exception {
		public:
			HandleException(Error error)
				:
				Exception(error.to_string(), TYPE_NAME),
				error_(error)
			{

			}

			Error get_error() const
			{
				return error_;
			}
		private:
			Error error_;
		};

		/**
		* Consumer exception
		*/
		class SYSTEM_API ConsumerException : public Exception {
		public:
			ConsumerException(Error error)
				:
				Exception(error.to_string(), TYPE_NAME),
				error_(error)
			{

			}

			Error get_error() const
			{
				return error_;
			}
		private:
			Error error_;
		};

		/**
		* Queue exception for rd_kafka_queue_t errors
		*/
		class SYSTEM_API QueueException : public Exception {
		public:
			QueueException(Error error)
				:
				Exception(error.to_string(), TYPE_NAME),
				error_(error)
			{

			}

			Error get_error() const
			{
				return error_;
			}
		private:
			Error error_;
		};

		/**
		* Backoff performer has no more retries left for a specific action.
		*/
		class SYSTEM_API ActionTerminatedException : public Exception {
		public:
			ActionTerminatedException(const std::string& error)
				:
				Exception(error, TYPE_NAME)
			{

			}
		};

	}
}
#endif // !SYSTEM_KAFAK_EXCEPTIONS_H
