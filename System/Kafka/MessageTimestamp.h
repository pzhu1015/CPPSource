///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_MESSAGETIMESTAMP_H
#define SYSTEM_KAFKA_MESSAGETIMESTAMP_H
#include "System/Base/DllExport.h"
#include <chrono>
//#include <boost/optional.hpp>
#include <librdkafka/rdkafka.h>
namespace System
{
	namespace Kafka
	{
		/**
		* Represents a message's timestamp
		*/
		class SYSTEM_API MessageTimestamp {
			friend class Message;
		public:
			/**
			* The timestamp type
			*/
			enum TimestampType {
				CREATE_TIME = RD_KAFKA_TIMESTAMP_CREATE_TIME,
				LOG_APPEND_TIME = RD_KAFKA_TIMESTAMP_LOG_APPEND_TIME
			};

			/**
			* Gets the timestamp value. If the timestamp was created with a 'time_point',
			* the duration represents the number of milliseconds since epoch.
			*/
			std::chrono::milliseconds get_timestamp() const;

			/**
			* Gets the timestamp type
			*/
			TimestampType get_type() const;
		private:
			MessageTimestamp(std::chrono::milliseconds timestamp, TimestampType type);

			std::chrono::milliseconds timestamp_;
			TimestampType type_;
		};

	}
}
#endif // !SYSTEM_KAFKA_MESSAGETIMESTAMP_H
