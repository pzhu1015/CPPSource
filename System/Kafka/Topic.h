///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_TOPIC_H
#define SYSTEM_KAFKA_TOPIC_H
#include "System/Base/DllExport.h"
#include <string>
#include <memory>
//#include <boost/optional.hpp>
#include <librdkafka/rdkafka.h>
namespace System
{
	namespace Kafka
	{
		/**
		* \brief Represents a rdkafka topic
		*
		* This is a simple wrapper over a rd_kafka_topic_t*
		*/
		class SYSTEM_API Topic {
		public:
			/**
			* \brief Creates a Topic object that doesn't take ownership of the handle
			*
			* \param handle The handle to be used
			*/
			static Topic make_non_owning(rd_kafka_topic_t* handle);

			/**
			* \brief Constructs an empty topic
			*
			* Note that using any methods except Topic::get_handle on an empty topic is undefined
			* behavior
			*/
			Topic();

			/**
			* \brief Constructs a topic using a handle
			*
			* This will take ownership of the handle
			*
			* \param handle The handle to be used
			*/
			Topic(rd_kafka_topic_t* handle);

			/**
			* Returns the topic name
			*/
			std::string get_name() const;

			/**
			* \brief Check if the partition is available
			*
			* This translates into a call to rd_kafka_topic_partition_available
			*
			* \param partition The partition to check
			*/
			bool is_partition_available(int partition) const;

			/**
			* Indicates whether this topic is valid (not null)
			*/
			explicit operator bool() const {
				return handle_ != nullptr;
			}

			/**
			* Returns the rdkakfa handle
			*/
			rd_kafka_topic_t* get_handle() const;
		private:
			using HandlePtr = std::unique_ptr<rd_kafka_topic_t, decltype(&rd_kafka_topic_destroy)>;

			struct NonOwningTag { };

			Topic(rd_kafka_topic_t* handle, NonOwningTag);

			HandlePtr handle_;
		};
	}
}
#endif // !SYSTEM_KAFKA_TOPIC_H
