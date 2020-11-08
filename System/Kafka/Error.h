///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_ERROR_H
#define SYSTEM_KAFKA_ERROR_H
#include "System/Base/DllExport.h"
#include <string>
#include <iosfwd>
#include <librdkafka/rdkafka.h>
namespace System
{
	namespace Kafka
	{
		/**
		* Abstraction for an rdkafka error
		*/
		class SYSTEM_API Error {
		public:
			/**
			* @brief Constructs an error object with RD_KAFKA_RESP_ERR_NO_ERROR
			*/
			Error() = default;
			/**
			* Constructs an error object
			*/
			Error(rd_kafka_resp_err_t error);

			/**
			* Gets the error value
			*/
			rd_kafka_resp_err_t get_error() const;

			/**
			* Gets the error string
			*/
			std::string to_string() const;

			/**
			* Checks whether this error contains an actual error (and not RD_KAFKA_RESP_ERR_NO_ERROR)
			*/
			explicit operator bool() const;

			/**
			* Compares this error for equality
			*/
			bool operator==(const Error& rhs) const;

			/**
			* Compares this error for inequality
			*/
			bool operator!=(const Error& rhs) const;

			/**
			* Writes this error's string representation into a stream
			*/
			SYSTEM_API friend std::ostream& operator<<(std::ostream& output, const Error& rhs);
		private:
			rd_kafka_resp_err_t error_{ RD_KAFKA_RESP_ERR_NO_ERROR };
		};
	}
}
#endif // !SYSTEM_KAFKA_ERROR_H
