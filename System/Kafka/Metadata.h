///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_METADATA_H
#define SYSTEM_KAFKA_METADATA_H
#include "System/Base/DllExport.h"
#include <memory>
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_set>
#include <librdkafka/rdkafka.h>
namespace System
{
	namespace Kafka
	{
		class Error;

		/**
		* Represents the metadata for a partition
		*/
		class SYSTEM_API PartitionMetadata {
		public:
			PartitionMetadata(const rd_kafka_metadata_partition& partition);

			/**
			* Gets the partition id
			*/
			uint32_t get_id() const;

			/**
			* Gets the partition error as reported by the broker
			*/
			Error get_error() const;

			/**
			* Gets the leader broker id
			*/
			int32_t get_leader() const;

			/**
			* Gets the replica brokers
			*/
			const std::vector<int32_t>& get_replicas() const;

			/**
			* Gets the In Sync Replica Brokers
			*/
			const std::vector<int32_t>& get_in_sync_replica_brokers() const;
		private:
			int32_t id_;
			rd_kafka_resp_err_t error_;
			int32_t leader_;
			std::vector<int32_t> replicas_;
			std::vector<int32_t> isrs_;
		};

		/**
		* Represents the metadata for a topic
		*/
		class SYSTEM_API TopicMetadata {
		public:
			TopicMetadata(const rd_kafka_metadata_topic& topic);

			/**
			* Gets the topic name
			*/
			const std::string& get_name() const;

			/**
			* Gets the topic error
			*/
			Error get_error() const;

			/**
			* Gets the partitions' metadata
			*/
			const std::vector<PartitionMetadata>& get_partitions() const;
		private:
			std::string name_;
			rd_kafka_resp_err_t error_;
			std::vector<PartitionMetadata> partitions_;
		};

		/**
		* Represents a broker's metadata
		*/
		class SYSTEM_API BrokerMetadata {
		public:
			BrokerMetadata(const rd_kafka_metadata_broker_t& broker);

			/**
			* Gets the host this broker can be found at
			*/
			const std::string& get_host() const;

			/**
			* Gets the broker's id
			*/
			int32_t get_id() const;

			/**
			* Gets the broker's port
			*/
			uint16_t get_port() const;
		private:
			const std::string host_;
			int32_t id_;
			uint16_t port_;
		};

		/**
		* Represents metadata for brokers, topics and partitions
		*/
		class SYSTEM_API Metadata {
		public:
			/**
			* \brief Creates a Metadata object that doesn't take ownership of the handle
			*
			* \param handle The handle to be used
			*/
			static Metadata make_non_owning(const rd_kafka_metadata_t* handle);

			/**
			* \brief Constructs an empty metadata object
			*
			* \remark Using any methods except Metadata::get_handle on an empty metadata is undefined behavior
			*/
			Metadata();

			/**
			* Constructor
			*/
			Metadata(const rd_kafka_metadata_t* handle);

			/**
			* Gets the brokers' metadata
			*/
			std::vector<BrokerMetadata> get_brokers() const;

			/**
			* Gets the topics' metadata
			*/
			std::vector<TopicMetadata> get_topics() const;

			/**
			* Gets metadata for the topics that can be found on the given set
			*
			* \param topics The topic names to be looked up
			*/
			std::vector<TopicMetadata> get_topics(const std::unordered_set<std::string>& topics) const;

			/**
			* Gets metadata for topics that start with the given prefix
			*
			* \param prefix The prefix to be looked up
			*/
			std::vector<TopicMetadata> get_topics_prefixed(const std::string& prefix) const;

			/**
			* Indicates whether this metadata is valid (not null)
			*/
			explicit operator bool() const;

			/**
			* Returns the rdkakfa handle
			*/
			const rd_kafka_metadata_t* get_handle() const;
		private:
			using HandlePtr = std::unique_ptr<const rd_kafka_metadata_t, decltype(&rd_kafka_metadata_destroy)>;

			struct NonOwningTag { };

			Metadata(const rd_kafka_metadata_t* handle, NonOwningTag);

			HandlePtr handle_;
		};

	}
}
#endif // !SYSTEM_KAFKA_METADATA_H
