///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_KAFKA_TOPICPARTITIONLIST_H
#define SYSTEM_KAFKA_TOPICPARTITIONLIST_H
#include "System/Base/DllExport.h"
#include <memory>
#include <iosfwd>
#include <algorithm>
#include <vector>
#include <set>
#include <librdkafka/rdkafka.h>
namespace System
{
	namespace Kafka
	{
		class TopicPartition;
		class PartitionMetadata;

		using TopicPartitionsListPtr = std::unique_ptr<rd_kafka_topic_partition_list_t,
			decltype(&rd_kafka_topic_partition_list_destroy)>;
		/**
		* A topic partition list
		*/
		using TopicPartitionList = std::vector<TopicPartition>;

		// Conversions between rdkafka handles and TopicPartitionList
		SYSTEM_API TopicPartitionsListPtr convert(const TopicPartitionList& topic_partitions);
		SYSTEM_API TopicPartitionList convert(const TopicPartitionsListPtr& topic_partitions);
		SYSTEM_API TopicPartitionList convert(rd_kafka_topic_partition_list_t* topic_partitions);
		SYSTEM_API TopicPartitionList convert(const std::string& topic,
			const std::vector<PartitionMetadata>& partition_metadata);
		SYSTEM_API TopicPartitionsListPtr make_handle(rd_kafka_topic_partition_list_t* handle);

		// Extracts a partition list subset belonging to the provided topics (case-insensitive)
		SYSTEM_API TopicPartitionList find_matches(const TopicPartitionList& partitions,
			const std::set<std::string>& topics);

		// Extracts a partition list subset belonging to the provided partition ids
		// Note: this assumes that all topic partitions in the original list belong to the same topic
		//       otherwise the partition ids may not be unique
		SYSTEM_API TopicPartitionList find_matches(const TopicPartitionList& partitions,
			const std::set<int>& ids);

		SYSTEM_API std::ostream& operator<<(std::ostream& output, const TopicPartitionList& rhs);

	}
}
#endif // !SYSTEM_KAFKA_TOPICPARTITIONLIST_H
