///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_TOPICCONFIG_H
#define SYSTEM_KAFKA_TOPICCONFIG_H
#include "System/Kafka/ConfigBase.h"
#include "System/Kafka/ConfigOption.h"
#include "System/Kafka/ClonablePtr.h"
#include <string>
#include <functional>
#include <initializer_list>
#include <librdkafka/rdkafka.h>

namespace System
{
	namespace Kafka
	{
		class Topic;
		class Buffer;

		/**
		* \brief Represents the topic configuration
		*
		* ConfigurationBase provides some extra overloads for set
		*/
		class SYSTEM_API TopicConfig : public ConfigBase<TopicConfig> {
		public:
			/**
			* \brief Partitioner callback
			*
			* This has the same requirements as rdkafka's partitioner calback:
			*   - *Must not* call any rd_kafka_*() functions except:
			*       rd_kafka_topic_partition_available(). This is done via Topic::is_partition_available
			*   - *Must not* block or execute for prolonged periods of time.
			*   - *Must* return a value between 0 and partition_count-1, or the
			*     special RD_KAFKA_PARTITION_UA value if partitioning
			*     could not be performed.
			*/
			using PartitionerCallback = std::function<int32_t(const Topic&, const Buffer& key,
				int32_t partition_count)>;

			using ConfigBase<TopicConfig>::set;
			using ConfigBase<TopicConfig>::get;

			/**
			* Default constructs a topic configuration object
			*/
			TopicConfig();

			/**
			* Constructs a TopicConfiguration object using a list of options
			*/
			TopicConfig(const std::vector<ConfigOption>& options);

			/**
			* Constructs a TopicConfiguration object using a list of options
			*/
			TopicConfig(const std::initializer_list<ConfigOption>& options);

			/**
			* Sets an option
			*
			* \param name The name of the option
			* \param value The value of the option
			*/
			TopicConfig& set(const std::string& name, const std::string& value);

			/**
			* \brief Sets the partitioner callback
			*
			* This translates into a call to rd_kafka_topic_conf_set_partitioner_cb
			*/
			TopicConfig& set_partitioner_callback(PartitionerCallback callback);

			/**
			* \brief Sets the "this" pointer as the opaque pointer for this handle
			*
			* This method will be called by consumers/producers when the topic configuration object
			* has been put in a persistent memory location. Users of cppkafka do not need to use this.
			*/
			TopicConfig& set_as_opaque();

			/**
			* Gets the partitioner callback
			*/
			const PartitionerCallback& get_partitioner_callback() const;

			/**
			* Returns true iff the given property name has been set
			*/
			bool has_property(const std::string& name) const;

			/**
			* Gets an option's value
			*
			* \param name The option's name
			*/
			std::string get(const std::string& name) const;

			/**
			* Gets all options, including default values which are set by rdkafka
			*/
			std::map<std::string, std::string> get_all() const;

			/**
			* Gets the rdkafka handle
			*/
			rd_kafka_topic_conf_t* get_handle() const;
		private:
			using HandlePtr = ClonablePtr<rd_kafka_topic_conf_t,
				decltype(&rd_kafka_topic_conf_destroy),
				decltype(&rd_kafka_topic_conf_dup)>;

			TopicConfig(rd_kafka_topic_conf_t* ptr);
			static HandlePtr make_handle(rd_kafka_topic_conf_t* ptr);

			HandlePtr handle_;
			PartitionerCallback partitioner_callback_;
		};
	}
}
#endif // !SYSTEM_KAFKA_TOPICCONFIG_H
