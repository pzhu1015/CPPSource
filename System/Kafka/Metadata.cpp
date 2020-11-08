///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#include "System/Kafka/Metadata.h"
#include "System/Kafka/Error.h"
#include <assert.h>

using std::string;
using std::vector;
using std::unordered_set;
namespace System
{
	namespace Kafka
	{
		PartitionMetadata::PartitionMetadata(const rd_kafka_metadata_partition& partition)
			: id_(partition.id), error_(partition.err), leader_(partition.leader) {
			for (int i = 0; i < partition.replica_cnt; ++i) {
				replicas_.push_back(partition.replicas[i]);
			}
			for (int i = 0; i < partition.isr_cnt; ++i) {
				isrs_.push_back(partition.isrs[i]);
			}
		}

		uint32_t PartitionMetadata::get_id() const {
			return id_;
		}

		Error PartitionMetadata::get_error() const {
			return error_;
		}

		int32_t PartitionMetadata::get_leader() const {
			return leader_;
		}

		const vector<int32_t>& PartitionMetadata::get_replicas() const {
			return replicas_;
		}

		const vector<int32_t>& PartitionMetadata::get_in_sync_replica_brokers() const {
			return isrs_;
		}

		// TopicMetadata 

		TopicMetadata::TopicMetadata(const rd_kafka_metadata_topic& topic)
			: name_(topic.topic), error_(topic.err) {
			for (int i = 0; i < topic.partition_cnt; ++i) {
				partitions_.emplace_back(topic.partitions[i]);
			}
		}

		const string& TopicMetadata::get_name() const {
			return name_;
		}

		Error TopicMetadata::get_error() const {
			return error_;
		}

		const vector<PartitionMetadata>& TopicMetadata::get_partitions() const {
			return partitions_;
		}

		// BrokerMetadata

		BrokerMetadata::BrokerMetadata(const rd_kafka_metadata_broker_t& broker)
			: host_(broker.host), id_(broker.id), port_(static_cast<uint16_t>(broker.port)) {

		}

		const string& BrokerMetadata::get_host() const {
			return host_;
		}

		int32_t BrokerMetadata::get_id() const {
			return id_;
		}

		uint16_t BrokerMetadata::get_port() const {
			return port_;
		}

		// Metadata

		void dummy_metadata_destroyer(const rd_kafka_metadata_t*) {

		}

		Metadata Metadata::make_non_owning(const rd_kafka_metadata_t* handle) {
			return Metadata(handle, NonOwningTag{});
		}

		Metadata::Metadata()
			: handle_(nullptr, nullptr) {

		}

		Metadata::Metadata(const rd_kafka_metadata_t* handle)
			: handle_(handle, &rd_kafka_metadata_destroy) {

		}

		Metadata::Metadata(const rd_kafka_metadata_t* handle, NonOwningTag)
			: handle_(handle, &dummy_metadata_destroyer) {

		}

		vector<BrokerMetadata> Metadata::get_brokers() const {
			assert(handle_);
			vector<BrokerMetadata> output;
			for (int i = 0; i < handle_->broker_cnt; ++i) {
				const rd_kafka_metadata_broker_t& broker = handle_->brokers[i];
				output.emplace_back(broker);
			}
			return output;
		}

		vector<TopicMetadata> Metadata::get_topics() const {
			assert(handle_);
			vector<TopicMetadata> output;
			for (int i = 0; i < handle_->topic_cnt; ++i) {
				const rd_kafka_metadata_topic_t& topic = handle_->topics[i];
				output.emplace_back(topic);
			}
			return output;
		}

		vector<TopicMetadata> Metadata::get_topics(const unordered_set<string>& topics) const {
			assert(handle_);
			vector<TopicMetadata> output;
			for (int i = 0; i < handle_->topic_cnt; ++i) {
				const rd_kafka_metadata_topic_t& topic = handle_->topics[i];
				if (topics.count(topic.topic)) {
					output.emplace_back(topic);
				}
			}
			return output;
		}

		vector<TopicMetadata> Metadata::get_topics_prefixed(const string& prefix) const {
			assert(handle_);
			vector<TopicMetadata> output;
			for (int i = 0; i < handle_->topic_cnt; ++i) {
				const rd_kafka_metadata_topic_t& topic = handle_->topics[i];
				string topic_name = topic.topic;
				if (topic_name.find(prefix) == 0) {
					output.emplace_back(topic);
				}
			}
			return output;
		}


		Metadata::operator bool() const {
			return handle_ != nullptr;
		}

		const rd_kafka_metadata_t* Metadata::get_handle() const {
			return handle_.get();
		}

	}
}