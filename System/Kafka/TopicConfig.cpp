///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/TopicConfig.h"
#include "System/Kafka/Exceptions.h"
#include "System/Kafka/Topic.h"
#include "System/Kafka/Buffer.h"
#include "System/Kafka/CallbackInvoker.h"
#include <vector>
#include <librdkafka/rdkafka.h>

using std::string;
using std::map;
using std::vector;
using std::initializer_list;
namespace System
{
	namespace Kafka
	{
		int32_t partitioner_callback_proxy(const rd_kafka_topic_t* handle, const void *key_ptr,
			size_t key_size, int32_t partition_count,
			void* topic_opaque, void* message_opaque) {
			const TopicConfig* config = static_cast<TopicConfig*>(topic_opaque);
			const auto& callback = config->get_partitioner_callback();
			if (callback) {
				Topic topic = Topic::make_non_owning(const_cast<rd_kafka_topic_t*>(handle));
				Buffer key(static_cast<const char*>(key_ptr), key_size);
				return CallbackInvoker<TopicConfig::PartitionerCallback>("topic partitioner", callback, nullptr)
					(topic, key, partition_count);
			}
			else {
				return rd_kafka_msg_partitioner_consistent_random(handle, key_ptr, key_size,
					partition_count, topic_opaque,
					message_opaque);
			}
		}

		TopicConfig::TopicConfig()
			: handle_(make_handle(rd_kafka_topic_conf_new())) {

		}

		TopicConfig::TopicConfig(const vector<ConfigOption>& options)
			: TopicConfig() {
			set(options);
		}

		TopicConfig::TopicConfig(const initializer_list<ConfigOption>& options)
			: TopicConfig() {
			set(options);
		}

		TopicConfig::TopicConfig(rd_kafka_topic_conf_t* ptr)
			: handle_(make_handle(ptr)) {

		}

		TopicConfig& TopicConfig::set(const string& name, const string& value) {
			char error_buffer[512];
			rd_kafka_conf_res_t result;
			result = rd_kafka_topic_conf_set(handle_.get(), name.data(), value.data(), error_buffer,
				sizeof(error_buffer));
			if (result != RD_KAFKA_CONF_OK) {
				throw ConfigException(name, error_buffer);
			}
			return *this;
		}

		TopicConfig& TopicConfig::set_partitioner_callback(PartitionerCallback callback) {
			partitioner_callback_ = move(callback);
			rd_kafka_topic_conf_set_partitioner_cb(handle_.get(), &partitioner_callback_proxy);
			return *this;
		}

		TopicConfig& TopicConfig::set_as_opaque() {
			rd_kafka_topic_conf_set_opaque(handle_.get(), this);
			return *this;
		}

		const TopicConfig::PartitionerCallback&
			TopicConfig::get_partitioner_callback() const {
			return partitioner_callback_;
		}

		bool TopicConfig::has_property(const string& name) const {
			size_t size = 0;
			return rd_kafka_topic_conf_get(handle_.get(), name.data(), nullptr, &size) == RD_KAFKA_CONF_OK;
		}

		string TopicConfig::get(const string& name) const {
			size_t size = 0;
			auto result = rd_kafka_topic_conf_get(handle_.get(), name.data(), nullptr, &size);
			if (result != RD_KAFKA_CONF_OK) {
				throw ConfigOptionNotFound(name);
			}
			vector<char> buffer(size);
			rd_kafka_topic_conf_get(handle_.get(), name.data(), buffer.data(), &size);
			return string(buffer.data());
		}

		map<string, string> TopicConfig::get_all() const {
			size_t count = 0;
			const char** all = rd_kafka_topic_conf_dump(handle_.get(), &count);
			map<string, string> output = parse_dump(all, count);
			rd_kafka_conf_dump_free(all, count);
			return output;
		}

		rd_kafka_topic_conf_t* TopicConfig::get_handle() const {
			return handle_.get();
		}

		TopicConfig::HandlePtr TopicConfig::make_handle(rd_kafka_topic_conf_t* ptr) {
			return HandlePtr(ptr, &rd_kafka_topic_conf_destroy, &rd_kafka_topic_conf_dup);
		}
	}
}